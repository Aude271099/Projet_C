#define _DEFAULT_SOURCE
#include "define.h"
#include "affichage.h"
#include "mesure.h"
#include "fir.h"
#include "iir.h"
#include "lecture.h"
#include "fichiers.h"
#include "integration.h"

int main(){
    int etat=0;
    absorp myAbsorp;
    oxy myOxy;
    param_fir* myFIR = init_fir(); // init FIR
    param_iir* myIIR = init_iir(); // init IIR
    mymes* myMesure = init_mesure(); //init mesure

    int tab_periode[100]; //tableau de période de 200 entiers
	int j ; //déclaration de j pour les boucles
	for(j = 0; j < 100; j++){
		tab_periode[j] = 0; //on initialise toutes les valeurs du tableau à 0
	}

    FILE* myFile = initFichier("record1_bin.dat"); //ouverture du fichier record1_bin.dat
    do{
        myAbsorp = lecture(myFile,&etat); //lecture du fichier
        if(etat != EOF){ //si la lecture du fichier n'est pas terminée
            myAbsorp = fir(myAbsorp,*myFIR); //le signal d'entrée passe dans le filtre FIR
            myAbsorp = iir(myAbsorp,*myIIR); //le signal de sortie du FIR passe dans le filtre IIR
            myOxy = mesure(myAbsorp, tab_periode, myMesure); //On fait les calculs de spo2 et du BPM sur le signal de sortie du IIR
            affichage(myOxy); //On affiche les valeurs en écrivant dans le fichier "Data.txt"
        }
        usleep(2000); //attente de 2ms
    }while( etat != EOF ); //tant que la lecture du fichier n'est pas terminée
    free_fir(myFIR); //on libère la mémoire des pointeurs de FIR
    free_iir(myIIR); //on libère la mémoire des pointeurs de IIR

    //affichage final
    printf("\n\nSPO2 final : "); //affichage spo2
    printf("%d", myOxy.spo2);
    printf("    Pouls final : "); //affichage pouls
    printf("%d", myOxy.pouls);
    return 1;

}
