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
	
	oxy myOxy;
	absorp myabsorp;
	int etat =0;
	int tab_periode[100];
	int j ;
	for(j = 0; j < 100; j++){
		tab_periode[j] = 0;
	}
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

	FILE *fp = initFichier(filename);

	while(etat != EOF){
		myabsorp = lireFichier(fp, &etat);
		if(etat != EOF){
			//printf("work");
			myOxy = mesure(myabsorp, i, periode, tab_periode, deb, max_acr, max_acir, min_acr, min_acir, debut);
		}
	}
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
	oxy myoxy;
	float ptp_acr;
	float ptp_acir;
	float rsir;
	float per = 0;
	float freq = 0;
	float freq_bpm = 0;
	
	

	//calcul des valeurs max et min de ACir et ACr
	if (*deb != 1){
		calcul(myabsorp, i, periode, tab_periode, deb, max_acr, max_acir, min_acr, min_acir, debut);
		//printf("%i	%i", *max_acr, *min_acr);
		//printf("	%i	%i\n", *max_acir, *min_acir);
		//printf("periode %i	\n", *periode);
	}else{
		//printf("%i\n", *periode);
		//Calcul des valeurs PTP
		calcul(myabsorp, i, periode, tab_periode, deb, max_acr, max_acir, min_acr, min_acir, debut);
		//printf("periode %i	\n", *periode);
		ptp_acr = ptp(max_acr, min_acr);
		ptp_acir = ptp(max_acir, min_acir);
		//printf("%f	%f	", ptp_acir, ptp_acr);
		//Calcul de RSIR
		//printf("%f	", myabsorp.dcr);
		//printf("%f	", myabsorp.dcir);
		rsir = (ptp_acr/myabsorp.dcr)/(ptp_acir/myabsorp.dcir);
		//printf("%f\n", rsir);

		//Calcul de SPO2
		myoxy.spo2 = spo2(rsir);
		//printf("%d\n", myoxy.spo2);


		//Calcul de la période : 1 valeur -> 2ms
		per = *periode * 0.002;
		
		//Calcul de la frequence en HZ
		freq = 1/per;

		//Calcul de la fréquence en BPM
		freq_bpm = freq*60;
		myoxy.pouls = freq_bpm;
		//printf("periode nb %i	periode (s) %f	ferquence (hz) %f	frequence BPM %f	\n", *periode, per, freq, freq_bpm);
		//printf("%i\n", myoxy.pouls);
	}




	return myoxy;
}

float ptp (int* max_ac, int* min_ac){
	//printf("%i	%i\n", *max_ac, *min_ac);
	float Ptp;
	Ptp = *max_ac - *min_ac;
	//printf("%f\n", Ptp);
	return Ptp;
}

int spo2 (float rsir){
	//printf("hello");
	float result;
	if (rsir>=0.4 && rsir<=1){
		result = -(10/0.4)*rsir + 110;
		return (int) result;
	} else if (rsir>1 && rsir<= 3.4){
		result = -(85/2.4)*rsir + 120;
		return (int) result;
	}else{
		//affiche erreur ??
		//break;
	}	
}

//Fonction pour le calcul des min et max pour ptp et calcul de la periode
void calcul(absorp myabsorp, int* i, int* periode, int tab_periode[], int* deb, int* max_acr, int* max_acir, int* min_acr, int* min_acir, int* debut){
	//période, "1 ligne" toutes les 2ms
	int max = 0;
	int min = 0;
	int per =0;
	int j ;
	//max acr et acir
	//printf("%f	", myabsorp.acr);
	//printf("%f	", myabsorp.acir);
	if(myabsorp.acr >= *max_acr) {
		*max_acr = myabsorp.acr;
	}
	if(myabsorp.acir >= *max_acir) {
		*max_acir = myabsorp.acir;
	}else if (myabsorp.acr < *max_acr && myabsorp.acir < *max_acir){
		max = 1;
	}
	
	//min acr et acir
	if (myabsorp.acr <= *min_acr) {
		*min_acr = myabsorp.acr;
	}
	if (myabsorp.acir <= *min_acir) {
		*min_acir = myabsorp.acir;
	}else if (myabsorp.acr > *min_acr && myabsorp.acir > *min_acir && *min_acr < 0){
		min = 1;
	}
	//printf("max :%i	min:%i	debut:%i	val:%f\n",max, min, *debut, myabsorp.acr);
	//calcul de la periode
	if (max == 1 && min == 1 && myabsorp.acr >= 0 && *debut<0){
		*deb = 1;
		//printf("periode\n");
		printf("i %i	", *i);
		for (j= 0; j <= *i; j++){
			per += tab_periode[j];
			printf("tab %i	%i\n", tab_periode[j], j);
			//printf("%i\n", periode);
		}
		printf("per %i	", per);
		*periode = per/(*i+1);
		printf("periode %i\n", *periode);
		*i += 1;
		//printf("i : %i\n", *i);
		*debut = myabsorp.acr;
	}else{
		//Calcul du nb de valeur dans une période
		tab_periode[*i] += 1;
		//printf("%i	 %i\n",*i, tab_periode[*i]);
	}
	*debut = myabsorp.acr;
}


//Calcul des valeurs PTP
	/*float ptp_acir = ptp(myabsorp.acir);
	float ptp_acr = ptp(myabsorp.acr);*/
	//printf("%f\n", ptp_acir);

	//Calcul de RSIR
	//float rsir;
	//rsir = (ptp_acr/myabsorp.dcr)/(ptp_acir/myabsorp.dcir);

	//Calcul de SPO2
	//printf("%f\n", rsir);
	//myoxy.spo2 = spo2(rsir);

	//calcul de la période
	//int per = ;
	//calcul de la frequence en BPM
	//myoxy.pouls = 1/per;