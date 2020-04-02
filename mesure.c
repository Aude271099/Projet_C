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

oxy mesureTest(char* filename){
	//Initialisation des variables 
	oxy myOxy;
	absorp myabsorp;
	int etat =0;
	int tab_periode[100];
	int j ;
	for(j = 0; j < 100; j++){
		tab_periode[j] = 0;
	}

	//Initialisation des pointeurs 
	int* periode =malloc(sizeof(int));
	int* deb =malloc(sizeof(int));
	int* i =malloc(sizeof(int));
	int* debut = malloc(sizeof(int));
	int* max_acr = malloc(sizeof(int));
	int* max_acir = malloc(sizeof(int));
    int* min_acr = malloc(sizeof(int));
	int* min_acir = malloc(sizeof(int));
	*periode = 0;
	*deb = 0;
	*debut = 0;
	*i = 0;
	*max_acr = 0;
	*max_acir = 0;
	*min_acr = 0; 
	*min_acir = 0;

	//Ouverture du fichier
	FILE *fp = initFichier(filename);

	//Lecture du fichier 
	while(etat != EOF){
		myabsorp = lireFichier(fp, &etat);
		if(etat != EOF){
			myOxy = mesure(myabsorp, i, periode, tab_periode, deb, max_acr, max_acir, min_acr, min_acir, debut);
		}
	}

	//Liberation des pointeurs 
	free(deb);
	free(periode);
	free(debut);
	free(max_acr);
	free(max_acir);
	free(min_acr);
	free(min_acir);
	free(i);
	finFichier(fp);
	return myOxy;

}


oxy mesure (absorp myabsorp,int* i, int* periode, int tab_periode[], int* deb,  int* max_acr, int* max_acir, int* min_acr, int* min_acir, int* debut){
	//Initialisation des variables 
	oxy myoxy;
	float ptp_acr;
	float ptp_acir;
	float rsir;
	float per = 0;
	float freq = 0;
	float freq_bpm = 0;
	
	//Attente d'avoir des valeurs min, max et une periode pour calculer les éléments de myoxy
	if (*deb != 1){
		//Calcul des valeurs Max, Min de ACr et ACir et de la période
		calcul(myabsorp, i, periode, tab_periode, deb, max_acr, max_acir, min_acr, min_acir, debut);
	}else{
		//Calcul des valeurs Max, Min de ACr et ACir et de la période en continue
		calcul(myabsorp, i, periode, tab_periode, deb, max_acr, max_acir, min_acr, min_acir, debut);

		//Calcul des valeurs PTP d'ACr et d'ACir
		ptp_acr = ptp(max_acr, min_acr);
		ptp_acir = ptp(max_acir, min_acir);

		//Calcul de RSIR
		rsir = (ptp_acr/myabsorp.dcr)/(ptp_acir/myabsorp.dcir);

		//Calcul de SPO2
		myoxy.spo2 = spo2(rsir);
		//------------------------------------------------------------------------------------

		//Calcul de la période : 1 valeur -> 2ms
		per = *periode * 0.002;
		
		//Calcul de la frequence en HZ
		freq = 1/per;

		//Calcul de la fréquence en BPM
		freq_bpm = freq*60;
		myoxy.pouls = freq_bpm;
	}
	return myoxy;
}


//Fonction calculant les variables PTP d'ACr et d'ACir 
float ptp (int* max_ac, int* min_ac){
	float Ptp;
	Ptp = *max_ac - *min_ac;
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
}

//Fonction pour le calcul des valeurs Max, Min de ACr et ACir et de la période
void calcul(absorp myabsorp, int* i, int* periode, int tab_periode[], int* deb, int* max_acr, int* max_acir, int* min_acr, int* min_acir, int* debut){
	//Initialisation des variables
	int max = 0;
	int min = 0;
	int per =0;
	int j ;


	//Calcul de max ACr et ACir (max = 1 lorsque les deux ont été atteint)
	if(myabsorp.acr >= *max_acr) {
		*max_acr = myabsorp.acr;
	}
	if(myabsorp.acir >= *max_acir) {
		*max_acir = myabsorp.acir;
	}else if (myabsorp.acr < *max_acr && myabsorp.acir < *max_acir){
		max = 1;
	}
	
	//Calcul de min ACr et ACir (min = 1 lorsque les deux ont été atteint)
	if (myabsorp.acr <= *min_acr) {
		*min_acr = myabsorp.acr;
	}
	if (myabsorp.acir <= *min_acir) {
		*min_acir = myabsorp.acir;
	}else if (myabsorp.acr > *min_acr && myabsorp.acir > *min_acir && *min_acr < 0){
		min = 1;
	}

	//calcul de la periode
	if (max == 1 && min == 1 && myabsorp.acr >= 0 && *debut<0){ //Une periode entière est passé
		//Changement d'état dans la fct mesure, les valeurs myoxy peuvent commencer à étre calculer
		*deb = 1;

		//Calcul de la moyenne des périodes
		for (j= 0; j <= *i; j++){
			per += tab_periode[j];
		}
		*periode = per/(*i+1);

		//incrémentation du nb de période
		*i += 1;

		//debut prend la valeur de ACr
		*debut = myabsorp.acr;
	}else{//Calcul du nb de valeur dans une période
		tab_periode[*i] += 1;
	}
	//debut prend la valeur de ACr
	*debut = myabsorp.acr;
}