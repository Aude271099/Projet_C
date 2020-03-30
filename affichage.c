#include "affichage.h"

void affichage(oxy myOxy){
    FILE *fp;
    FILE *verrou;

    verrou = fopen(".verrouData", "w");//Création du verrou
    fp = fopen("Data.txt", "w"); //Ouverture du fichier en écriture

    if(fp == NULL){
        printf("Erreur lors de l'ouverture du fichier");
    }

    fprintf(fp, "%d", myOxy.spo2); //Ecriture du spo2
    fprintf(fp, "%d", myOxy.pouls); //Ecriture du pouls

    fclose(verrou); //On ferme le fichier verrou
    remove(".verrouData"); //On supprime le verrou
}

