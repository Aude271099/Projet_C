#include "define.h"

typedef struct{
    float *tab_acr;
    float *tab_acir;
    absorp *tab_signal_sortie;

} param_iir;

absorp iirTest(char* filename);

absorp iir(absorp myAbsorp, param_iir myParam_iir);

param_iir* init_iir();
void free_iir(param_iir* myParam_iir);


