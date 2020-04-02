#include "define.h"

typedef struct{
    int periode;
	int deb;
	int i;
	int debut;
	int max_acr;
	int max_acir;
    int min_acr;
	int min_acir;
} mymes;

mymes *init_mesure();
void free_mesure(mymes *myMesure);

oxy mesureTest(char* filename);

oxy mesure (absorp myabsorp, int tab_periode[],mymes *myMesure);	

float ptp (int max_ac, int min_ac);
int spo2 (float rsir);
void calcul(absorp myabsorp, int tab_periode[], mymes *myMesure);