#include "define.h"

oxy mesureTest(char* filename);

oxy mesure (absorp myabsorp, int* i, int* periode, int tab_periode[], int *deb,  int* max_acr, int* max_acir, int* min_acr, int* min_acir, int* debut);	

float ptp (int* max_ac, int* min_ac);
int spo2 (float rsir);
void calcul(absorp myabsorp,int* i, int* periode, int tab_periode[], int* deb, int* max_acr, int* max_acir, int* min_acr, int* min_acir, int* debut);