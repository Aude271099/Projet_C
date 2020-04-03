#include "affichage.h"

/*BUT : -Affichage des valeurs SPO2 et rythme cardiaque
en BPM
-.verrouData empêche les accés en lecture et écriture

au même moment*/

//fonction d'affichage qui récupère un myOxy et écrit les valeurs de ce dernier dans un fichier Data.txt
void affichage(oxy myOxy){
    FILE *fp; //variable pour ouvrir le fichier Data.txt
    FILE *verrou; //variable pour ouvrir le fichier .verrouData

    verrou = fopen(".verrouData", "r");//lecture du verrou s'il existe
    if(verrou){  // Fichier verrou existe
        printf(".verrouData existe"); //on affiche que le verrou existe pour ne pas laisser la boucle vide
        fclose(verrou); //on ferme le verrou

    }else{  // Verrou n'existe pas
        verrou = fopen(".verrouData", "w");//Création du verrou
        if(verrou){
            fclose(verrou); //On ferme le fichier verrou directement
        }
        fp = fopen("Data.txt", "w"); //Ouverture du fichier Data.txt en écriture

        if(fp == NULL) {    //erreur si le fichier ne peut pas s'ouvrir
            perror("Error opening file"); //erreur d'ouverture
            return; //retourne void
        }

        if(fp != NULL){ //si le ficher s'ouvre
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

