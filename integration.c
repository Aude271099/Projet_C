/*BUT : -ouvre et lit les valeurs d'absorption contenu 
dans le fichier str des fct FIR, IRR, MESURE et AFFICHAGE
->Ensuite ces fct seront appelées itérativement 
jusqu'a la fin de la lecture du fichier
*/

#include "integration.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "affichage.h"
#include "fichiers.h"

//fonction integration qui va appeler tour à tour les fonctions lireFichier, fir, iir, mesure et affichage sur un fichier donné
void integrationTest(char* filename)
{
    int etat=0; //etat de lecture du fichier
    absorp myAbsorp;//signal d'entrée
    oxy myOxy;//spo2 et bpm à afficher
    param_fir* myFIR = init_fir(); // init FIR
    param_iir* myIIR = init_iir(); // init IIR
    mymes * myMesure = init_mesure(); //init mesure

    int tab_periode[200]; //tableau de période de 200 entiers
	int j ; //déclaration de j pour les boucles
	for(j = 0; j < 200; j++){
		tab_periode[j] = 0; //on initialise toutes les valeurs du tableau à 0
	}

    FILE* myFile = initFichier(filename); //ouverture  du fichier mit en paramètre de l'intégration

    do{
        myAbsorp = lireFichier(myFile,&etat); //lecture du fichier avec lireFichier
        if(etat != EOF){    //si la lecture du fichier n'est pas terminée
            myAbsorp = fir(myAbsorp,*myFIR); //le signal d'entrée passe dans le filtre FIR
            myAbsorp = iir(myAbsorp,*myIIR); //le signal de sortie du FIR passe dans le filtre IIR
            myOxy = mesure(myAbsorp, tab_periode, myMesure); //On fait les calculs de spo2 et du BPM sur le signal de sortie du IIR
            affichage(myOxy); //On affiche les valeurs en écrivant dans le fichier "Data.txt"
        }
    }while( etat != EOF ); //tant que la lecture du fichier n'est pas terminée

    free_fir(myFIR); //on libère la mémoire des pointeurs de FIR
    free_iir(myIIR); //on libère la mémoire des pointeurs de IIR

    //affichage pour les tests    
    // printf("\n\nSPO2 final : ");
    // printf("%d", myOxy.spo2);
    // printf("    Pouls final : ");
    // printf("%d", myOxy.pouls);
}

