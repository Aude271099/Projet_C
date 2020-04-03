#include "define.h"

//on fait un struct pour les paramètres (on met les tableaux d'acr et d'acir dedans, ainsi qu'un tableau d'absorp contenant les signaux de sortie précédents)
typedef struct{
    float *tab_acr; //tableau d'acr
    float *tab_acir; //tableau d'acir
    absorp *tab_signal_sortie; //tableau des signaux de sortie

} param_iir;

//fonction test appelant la fonction iir prenant en paramètre le nom du fichier
absorp iirTest(char* filename);

//fonction du filtre iir prenant en paramètre le signal d'entrée et les paramètres d iir
absorp iir(absorp myAbsorp, param_iir myParam_iir);

//fonction d'initialisation des paramètres
param_iir* init_iir();

//fonction de libération de la mémoire des paramètres
void free_iir(param_iir* myParam_iir);


