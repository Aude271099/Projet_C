#include "fir.h"
#include "fichiers.h"
/*Fonction firTest
BUT : -Fonction de test de le fonction FIR

Fonction FIR
BUT : -Filtre FIR appliqué sur les composantes ACr et ACir
(pas nécessaire sur les composantes DCr et DCir)
utilisation d'un buffer ?
-retourne struct type absorp(.acr, .acir, .dcr et .dcir)
->tableau des coefficients utilisés pour le filtre à 
récupérer
->Fichier test d'entrée à utiliser : record1.dat*/

//tableau des coefficients du filtre FIR
float FIR_TAPS[51]={
    1.4774946e-019,
    1.6465231e-004,
    3.8503956e-004,
    7.0848037e-004,
    1.1840522e-003,
    1.8598621e-003,
    2.7802151e-003,
    3.9828263e-003,
    5.4962252e-003,
    7.3374938e-003,
    9.5104679e-003,
    1.2004510e-002,
    1.4793934e-002,
    1.7838135e-002,
    2.1082435e-002,
    2.4459630e-002,
    2.7892178e-002,
    3.1294938e-002,
    3.4578348e-002,
    3.7651889e-002,
    4.0427695e-002,
    4.2824111e-002,
    4.4769071e-002,
    4.6203098e-002,
    4.7081811e-002,
    4.7377805e-002,
    4.7081811e-002,
    4.6203098e-002,
    4.4769071e-002,
    4.2824111e-002,
    4.0427695e-002,
    3.7651889e-002,
    3.4578348e-002,
    3.1294938e-002,
    2.7892178e-002,
    2.4459630e-002,
    2.1082435e-002,
    1.7838135e-002,
    1.4793934e-002,
    1.2004510e-002,
    9.5104679e-003,
    7.3374938e-003,
    5.4962252e-003,
    3.9828263e-003,
    2.7802151e-003,
    1.8598621e-003,
    1.1840522e-003,
    7.0848037e-004,
    3.8503956e-004,
    1.6465231e-004,
    1.4774946e-019
};



absorp firTest(char* filename){
	absorp myAbsorp;
	absorp signal_FIR;
	int etat =0;
	int i;
    float *tab_acr = malloc(51*sizeof(float));
    float *tab_acir = malloc(51*sizeof(float));

	for(i = 0; i < 51; i++){
		tab_acr[i] = 0;
		tab_acir[i] = 0;
	}
	
	FILE *fp = initFichier(filename);
	
	while(etat != EOF){
		myAbsorp = lireFichier(fp, &etat);
		if(etat != EOF){
			signal_FIR = fir(myAbsorp, tab_acr, tab_acir);
		}
	}
	
    // printf("%f", signal_FIR.acr);
	finFichier(fp);

	return signal_FIR; //on retourne le nouveau struct avec les derniers signaux filtrés

}

absorp fir(absorp myAbsorp, float *tab_acr, float *tab_acir){
	float signal_sortie_acr = 0;
	float signal_sortie_acir = 0;
	absorp signalSortie;
	int i;

	for (i = 0; i < 50; i++){
		tab_acr[i] = tab_acr[i+1];
		tab_acir[i] = tab_acir[i+1];
	}
	tab_acr[50] = myAbsorp.acr;
	tab_acir[50] = myAbsorp.acir;

	for(i = 0; i < 51; i++){ 		//boucle for pour faire la somme de k = 0 à L-1			
									//(L = 51 car 51 coefficients dans le tableau FIR_TAPS)
		signal_sortie_acr += FIR_TAPS[i] * tab_acr[50 - i];
		signal_sortie_acir += FIR_TAPS[i] * tab_acir[50 - i];

	}
	signalSortie.acr = signal_sortie_acr;
	signalSortie.acir = signal_sortie_acir;
    signalSortie.dcr = myAbsorp.dcr;
    signalSortie.dcir = myAbsorp.dcir;


	return signalSortie;
}
//boucle 50 fois (k)