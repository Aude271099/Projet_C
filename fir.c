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

//fonction d'initialisations des paramètres
param_fir* init_fir(){
    param_fir* myParam_fir = malloc(sizeof(param_fir)); //allocation mémoire du struct
    int i;//déclaration du i pour les boucles
    //on alloue de la mémoire aux paramètres
    myParam_fir->tab_acr = malloc(51*sizeof(float)); //tableau de pointeurs dans lequel on mettra les valeurs des acr
    myParam_fir->tab_acir = malloc(51*sizeof(float)); //tableau de pointeurs dans lequel on mettra les valeurs des acir

    //on initialise toutes les valeurs des 2 tableaux à 0
    for(i = 0; i < 51; i++){
		myParam_fir->tab_acr[i] = 0;//valeurs du tableau acr à 0
		myParam_fir->tab_acir[i] = 0;//valeurs du tableau acir à 0
	}

    return myParam_fir; //on retourne les paramètres
}

//fonction test appelant la fonction fir et prenant en paramètre le nom du fichier
absorp firTest(char* filename){

    //initialisations des variables
    param_fir* myParam_fir = init_fir(); //appel de la fonction initialisation
	absorp myAbsorp;//signal d'entrée pour les fonctions
    absorp signal_FIR;//signal de sortie du filtre
	int etat = 0;//etat de lecture du fichier
	
    //ouverture du fichier
	FILE *fp = initFichier(filename);
	
    //lecture du fichier et appel de la fonction FIR pour chaque ligne du tableau
	while(etat != EOF){ //tant que la lecture du fichier n'est pas terminée
		myAbsorp = lireFichier(fp, &etat); //on met les valeurs de la ligne dans le struct de notre signal d'entrée
		if(etat != EOF){ //si on n'est pas à la fin du fichier
			signal_FIR = fir(myAbsorp, *myParam_fir); //appel de la fonction FIR
		}
	}
	
	finFichier(fp); //fermeture du fichier

	return signal_FIR; //on retourne le nouveau struct avec les derniers signaux filtrés

}

//filtre FIR prenant en paramètre le signal d'entrée et les paramètres FIR
absorp fir(absorp myAbsorp, param_fir myParam_fir){
	float signal_sortie_acr = 0;//parametre acr du signal de sortie
	float signal_sortie_acir = 0;//parametre acir du signal de sortie
	absorp signalSortie;//signal de sortie, c'est celui qu'on retourne à la fin de la fonction
	int i; //déclaration du i pour les boucles

    //décalage de toutes les valeurs des tableaux vers la gauche
	for (i = 0; i < 50; i++){
		myParam_fir.tab_acr[i] = myParam_fir.tab_acr[i+1];
		myParam_fir.tab_acir[i] = myParam_fir.tab_acir[i+1];
	}
    //on écrit les données de la ligne dans la dernière case de chaque tableau
	myParam_fir.tab_acr[50] = myAbsorp.acr;
	myParam_fir.tab_acir[50] = myAbsorp.acir;

	for(i = 0; i < 51; i++){ 		//boucle for pour faire la somme de k = 0 à L-1			
									//(L = 51 car 51 coefficients dans le tableau FIR_TAPS)
		signal_sortie_acr += FIR_TAPS[i] * myParam_fir.tab_acr[50 - i]; //calcul de la somme pour les acr du filtre FIR
		signal_sortie_acir += FIR_TAPS[i] * myParam_fir.tab_acir[50 - i];//calcul de la somme pour les acir du filtre FIR

	}
	signalSortie.acr = signal_sortie_acr; //acr du signal de sortie
	signalSortie.acir = signal_sortie_acir;//acir du signal de sortie
    signalSortie.dcr = myAbsorp.dcr; //on n'oublie pas le dcr du signal d'entrée
    signalSortie.dcir = myAbsorp.dcir;//on n'oublie pas le dcir du signal d'entrée


	return signalSortie; //on retourne le signal de sortie
}

//fonction qui libère la mémoire allouée aux pointeurs des paramètres
void free_fir(param_fir* myParam_fir){
    free(myParam_fir->tab_acr); //on libère la mémoire du tableau d'acr
    free(myParam_fir->tab_acir); //on libère la mémoire du tableau d'acir
}