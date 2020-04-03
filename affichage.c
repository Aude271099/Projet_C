#include "affichage.h"

/*BUT : -Affichage des valeurs SPO2 et rythme cardiaque
en BPM
-.verrouData empêche les accés en lecture et écriture

au même moment*/

void affichage(oxy myOxy){
    FILE *fp;
    FILE *verrou;

    verrou = fopen(".verrouData", "r");//Création du verrou
    if(verrou){  // Fichier verrou existe
        printf(".verrouData existe"); //on affiche que le verrou existe pour ne pas laisser la boucle vide
        fclose(verrou);

    }else{  // Fichier n'existe pas
        verrou = fopen(".verrouData", "w");//Création du verrou
        if(verrou){
            fclose(verrou); //On ferme le fichier verrou
        }
        fp = fopen("Data.txt", "w"); //Ouverture du fichier en écriture

        if(fp == NULL) {    //erreur si le fichier ne peut pas s'ouvrir
            perror("Error opening file");
            return;
        }

        if(fp != NULL){
            fprintf(fp, "%d", myOxy.spo2); //Ecriture du spo2
            fprintf(fp, "\n"); //Retour à la ligne
            fprintf(fp, "%d", myOxy.pouls); //Ecriture du pouls
            remove(".verrouData"); //On supprime le verrou
            fclose(fp); //fermeture du fichier
        }
    }

    // printf("\nSPO2 : ");
    // printf("%d", myOxy.spo2);
    // printf("   Pouls : ");
    // printf("%d", myOxy.pouls);

}
