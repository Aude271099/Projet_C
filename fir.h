#include "define.h"

//on fait un struct pour les paramètres (on met les tableaux d'acr et d'acir dedans)
typedef struct{
    float *tab_acr;
    float *tab_acir;

} param_fir;

absorp firTest(char* filename);
absorp fir(absorp myAbsorp, param_fir myParam_fir);

param_fir * init_fir();
void free_fir(param_fir* myParam_fir);
