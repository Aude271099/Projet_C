#include "mesure.h"
#include "fichiers.h"
/*Fonction mesureTest
BUT : -Fonction de test de le fonction MESURE

Fonction MESURE
BUT : -Calcul de SPO2 (taux de saturation de 
l'oxygène dans le sang)
    -calcul des valeurs PTP de ACir et ACr
    -clacul de RSIR avec DCr, DCir et les valeurs PTP
    -calcul de SPO2 avec le rapport entre RSIR et SP02(%)
-Calcul du rythme cardiaque
    -calcul de la période des signaux ACr et ACir 
    (qui est presque identique)
    -calcul de la fréquence en BPM
-retourne struct type oxy(.SPO2 et .pouls)
->Fichier test d'entre à utiliser : record1_irr.dat*/


mymes *init_mesure(){
	//Initialisation des pointeurs 
	mymes *myMesure = malloc(sizeof(mymes));

	myMesure->periode = 0;
	myMesure->deb = 0;
	myMesure->debut = 0;
	myMesure->i = 0;
	myMesure->max_acr = 0;
	myMesure->max_acir = 0;
	myMesure->min_acr = 0; 
	myMesure->min_acir = 0;

	return myMesure;
}

oxy mesureTest(char* filename){
	//Initialisation des variables 
	oxy myOxy;
	absorp myabsorp;
	mymes *myMesure = init_mesure();
	int etat =0;
	int tab_periode[100];
	int j ;
	for(j = 0; j < 100; j++){
		tab_periode[j] = 0;
	}

	//Ouverture du fichier
	FILE *fp = initFichier(filename);

	//Lecture du fichier 
	while(etat != EOF){
		myabsorp = lireFichier(fp, &etat);
		if(etat != EOF){
			myOxy = mesure(myabsorp, tab_periode, myMesure);
		}
	}

	finFichier(fp);
	return myOxy;

}


oxy mesure (absorp myabsorp, int tab_periode[], mymes * myMesure){
	//Initialisation des variables 
	oxy myoxy;
	float ptp_acr;
	float ptp_acir;
	float rsir;
	float per = 0;
	float freq = 0;
	float freq_bpm = 0;
	
	//Attente d'avoir des valeurs min, max et une periode pour calculer les éléments de myoxy
	if (myMesure->deb != 1){
		//Calcul des valeurs Max, Min de ACr et ACir et de la période
		calcul(myabsorp, tab_periode, myMesure);
	}else{
		//Calcul des valeurs Max, Min de ACr et ACir et de la période en continue
		calcul(myabsorp, tab_periode, myMesure);

		//Calcul des valeurs PTP d'ACr et d'ACir
		ptp_acr = ptp(myMesure->max_acr, myMesure->min_acr);
		ptp_acir = ptp(myMesure->max_acir, myMesure->min_acir);

		//Calcul de RSIR
		rsir = (ptp_acr/myabsorp.dcr)/(ptp_acir/myabsorp.dcir);

		//Calcul de SPO2
		myoxy.spo2 = spo2(rsir);
		//------------------------------------------------------------------------------------

		//Calcul de la période : 1 valeur -> 2ms
		per = myMesure->periode * 0.002;
		
		//Calcul de la frequence en HZ
		freq = 1/per;

		//Calcul de la fréquence en BPM
		freq_bpm = freq*60;
		myoxy.pouls = freq_bpm;
	}
	return myoxy;
}


//Fonction calculant les variables PTP d'ACr et d'ACir 
float ptp (int max_ac, int min_ac){
	float Ptp;
	Ptp = max_ac - min_ac;
	return Ptp;
}

//Fonction calculant SPO2
int spo2 (float rsir){
	float result;
	if (rsir>=0.4 && rsir<=1){
		result = -(10/0.4)*rsir + 110;
		return (int) result;
	} else if (rsir>1 && rsir<= 3.4){
		result = -(85/2.4)*rsir + 120;
		return (int) result;
	}
	return 0;
}

//Fonction pour le calcul des valeurs Max, Min de ACr et ACir et de la période
void calcul(absorp myabsorp, int tab_periode[], mymes *myMesure){
	//Initialisation des variables
	int max = 0;
	int min = 0;
	int per =0;
	int j ;


	//Calcul de max ACr et ACir (max = 1 lorsque les deux ont été atteint)
	if(myabsorp.acr >= myMesure->max_acr) {
		myMesure->max_acr = myabsorp.acr;
	}
	if(myabsorp.acir >= myMesure->max_acir) {
		myMesure->max_acir = myabsorp.acir;
	}else if (myabsorp.acr < myMesure->max_acr && myabsorp.acir < myMesure->max_acir){
		max = 1;
	}
	
	//Calcul de min ACr et ACir (min = 1 lorsque les deux ont été atteint)
	if (myabsorp.acr <= myMesure->min_acr) {
		myMesure->min_acr = myabsorp.acr;
	}
	if (myabsorp.acir <= myMesure->min_acir) {
		myMesure->min_acir = myabsorp.acir;
	}else if (myabsorp.acr > myMesure->min_acr && myabsorp.acir > myMesure->min_acir && myMesure->min_acr < 0){
		min = 1;
	}

	//calcul de la periode
	if (max == 1 && min == 1 && myabsorp.acr >= 0 && myMesure->debut<0){ //Une periode entière est passé
		//Changement d'état dans la fct mesure, les valeurs myoxy peuvent commencer à étre calculer
		myMesure->deb = 1;

		//Calcul de la moyenne des périodes
		for (j= 0; j <= myMesure->i; j++){
			per += tab_periode[j];
		}
		myMesure->periode = per/(myMesure->i+1);

		//incrémentation du nb de période
		myMesure->i += 1;

		//debut prend la valeur de ACr
		myMesure->debut = myabsorp.acr;
	}else{//Calcul du nb de valeur dans une période
		tab_periode[myMesure->i] += 1;
	}
	//debut prend la valeur de ACr
	myMesure->debut = myabsorp.acr;
}

void free_mesure(mymes *myMesure){
	//Liberation des pointeurs
}