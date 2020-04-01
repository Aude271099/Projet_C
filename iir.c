#include "iir.h"
#include "fichiers.h"
/*Fonction iirTest
BUT : -Fonction de test de le fonction IIR

Fonction IRR
BUT : -Filtre IRR appliqué sur les composantes ACr et ACir
(sert à supprimer la composante continue)
-retourne struct type absorp(.acr, .acir, .dcr et .dcir)
->Fichier test d'entrée à utiliser : record1_fir.dat*/

absorp iirTest(char* filename){
	absorp	myAbsorp;
	absorp signal_IIR;
	int etat = 0;
	int i;
	float *tab_acr = malloc(2*sizeof(float));
    float *tab_acir = malloc(2*sizeof(float));
	absorp *tab_signal_sortie = malloc(2*sizeof(absorp));

	for(i = 0; i < 2; i++){
		tab_acr[i] = 0;
		tab_acir[i] = 0;
		tab_signal_sortie[i].acr = 0;
		tab_signal_sortie[i].acir = 0;
	}

	FILE *fp = initFichier(filename);
	
	while(etat != EOF){
		myAbsorp = lireFichier(fp, &etat);
		if(etat != EOF){
			signal_IIR = iir(myAbsorp, tab_acr, tab_acir, tab_signal_sortie);
		}
	}

	return signal_IIR;

}


absorp iir(absorp myAbsorp, float * tab_acr, float * tab_acir, absorp *tab_signal_sortie){
	absorp signalSortie;
	signalSortie.acr = 0;
	signalSortie.acir = 0;
	signalSortie.dcr = myAbsorp.dcr;
    signalSortie.dcir = myAbsorp.dcir; 
	int i;

	for (i = 0; i < 2; i++){
		tab_acr[i] = tab_acr[i+1];
		tab_acir[i] = tab_acir[i+1];
		tab_signal_sortie[i] = tab_signal_sortie[i+1];
	}

	tab_acr[1] = myAbsorp.acr;
	tab_acir[1] = myAbsorp.acir;

	signalSortie.acr = tab_acr[1] - tab_acr[0] + 0.992 * tab_signal_sortie[0].acr;
	signalSortie.acir = tab_acir[1] - tab_acir[0] + 0.992 * tab_signal_sortie[0].acir;

	tab_signal_sortie[1] = signalSortie;


	return signalSortie;
}
