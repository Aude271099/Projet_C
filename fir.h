#include "define.h"

//on fait un struct pour les paramètres (on met les tableaux d'acr et d'acir dedans)
typedef struct{
    float *tab_acr;//tableau des valeurs de acr
    float *tab_acir;//tableau des valeurs de acir

} param_fir;

absorp firTest(char* filename);//fonction test qui appelle le la fonction fir
absorp fir(absorp myAbsorp, param_fir myParam_fir);//fonction du filtre fir

param_fir * init_fir();//fonction d'initialisation des paramètres
void free_fir(param_fir* myParam_fir);//fonction de libération de la mémoire
