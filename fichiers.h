#ifndef FICHIERS_H
#define FICHIERS_H
#include <stdio.h>
#include <stdlib.h>
#include "define.h"

//fonction d'initialisation du fichier
FILE* initFichier(char* nomFichier );

//fonction de lecture de fichier retournant un absorp correspondant au signal d'entrée
absorp lireFichier(FILE* pf, int* etat);

//fonction de fermeture du fichier
void finFichier(FILE* pf);
#endif

