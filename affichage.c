#include "affichage.h"

void affichage(oxy myOxy){
    FILE *fp;
    int verrou;

    verrou = mkstemp(".verrouData"); //Création du verrou
    fp = fopen("Data.txt", "w"); //Ouverture du fichier en écriture

    if(fp == NULL){
        printf("Erreur lors de l'ouverture du fichier");
    }

    fprintf(fp, myOxy.spo2); //Ecriture du spo2
    fprintf(fp, myOxy.pouls); //Ecriture du pouls

    remove(verrou); //On supprime le verrou
}

