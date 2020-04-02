#include "iir.h"
#include "fichiers.h"
/*Fonction iirTest
BUT : -Fonction de test de le fonction IIR

Fonction IRR
BUT : -Filtre IRR appliqué sur les composantes ACr et ACir
(sert à supprimer la composante continue)
-retourne struct type absorp(.acr, .acir, .dcr et .dcir)
->Fichier test d'entrée à utiliser : record1_fir.dat*/

//fonction d'initialisation des variables et des paramètres
param_iir *init_iir(){
	int i;
	//on alloue de la mémoire aux paramètres
	param_iir* myParam_iir = malloc(sizeof(param_iir));
	
	myParam_iir->tab_acr = malloc(2*sizeof(float)); //tableau de pointeurs dans lequel on mettra les valeurs des acr
	myParam_iir->tab_acir = malloc(2*sizeof(float)); //tableau de pointeurs dans lequel on mettra les valeurs des acir
	myParam_iir->tab_signal_sortie = malloc(2*sizeof(absorp)); //tableau de pointeurs dans lequel on mettra les valeurs des acr et acir des signaux de sortie

	//on initialise tous les tableaux à 0
	for(i = 0; i < 2; i++){
		myParam_iir->tab_acr[i] = 0;
		myParam_iir->tab_acir[i] = 0;
		myParam_iir->tab_signal_sortie[i].acr = 0;
		myParam_iir->tab_signal_sortie[i].acir = 0;
	}
	return myParam_iir; //on retourne le struct des paramètres
}

absorp iirTest(char* filename){
	//initialisation des variables et des paramètres
	param_iir* myParam_iir = init_iir(); //appel de la fonction init_iir
	absorp	myAbsorp; //signal d'entrée
	absorp signal_IIR; //signal de sortie du filtre, c'est ce que notre fonction va retourner
	int etat = 0; //etat de lecture du fichier

	FILE *fp = initFichier(filename); //ouverture du fichier
	
	 //lecture du fichier et appel de la fonction iir pour chaque ligne du tableau
	while(etat != EOF){
		myAbsorp = lireFichier(fp, &etat); //lecture du fichier
		if(etat != EOF){
			signal_IIR = iir(myAbsorp, *myParam_iir); //appel de la fonction iir
		}
	}
	finFichier(fp); //fermeture du fichier
	
	return signal_IIR; //on retourne le signal de sortie du filtre

}

//fonction du filtre iir
absorp iir(absorp myAbsorp, param_iir myParam_iir){
	//initialisation des variables propres à la fonction
	absorp signal_IIR; //signal de sortie, c'est celui que va retourner la fonction
	int i;

	//on initialise les valeurs acr et dcr du signal de sortie à 0
	signal_IIR.acr = 0;
	signal_IIR.acir = 0;
	//on oublie pas de donner les valeurs de dcr et dcir de notre signal d'entrée au signal de sortie
	signal_IIR.dcr = myAbsorp.dcr;
    signal_IIR.dcir = myAbsorp.dcir; 
	
	//décalage vers la gauche de toutes nos valeurs dans les tableaux acr, acir et signal de sortie
	for (i = 0; i < 2; i++){
		myParam_iir.tab_acr[i] = myParam_iir.tab_acr[i+1];
		myParam_iir.tab_acir[i] = myParam_iir.tab_acir[i+1];
		myParam_iir.tab_signal_sortie[i] = myParam_iir.tab_signal_sortie[i+1];
	}

	//on écrit les données de la ligne dans la dernière case de chaque tableau
	myParam_iir.tab_acr[1] = myAbsorp.acr;
	myParam_iir.tab_acir[1] = myAbsorp.acir;

	//calcul des valeurs acr et dcr du signal de sortie
	signal_IIR.acr = myParam_iir.tab_acr[1] - myParam_iir.tab_acr[0] + 0.992 * myParam_iir.tab_signal_sortie[0].acr;
	signal_IIR.acir = myParam_iir.tab_acir[1] - myParam_iir.tab_acir[0] + 0.992 * myParam_iir.tab_signal_sortie[0].acir;

	//on met le signal de sortie dans la dernière case du tableau de signal de sortie pour les prochains calculs
	myParam_iir.tab_signal_sortie[1] = signal_IIR;


	return signal_IIR; //on retourne le signal de sortie
}

void free_iir(param_iir* myParam_iir){
	free(myParam_iir->tab_acr);
	free(myParam_iir->tab_acir);
	free(myParam_iir->tab_signal_sortie);
}
