#include "affichage.h"
/*BUT : -Affichage des valeurs SPO2 et rythme cardiaque
en BPM
-.verrouData empêche les accés en lecture et écriture

au même moment*/
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

