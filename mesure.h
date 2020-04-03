#include "define.h"

typedef struct{
    int periode;
	int deb;
	int i;
	float debut;
	float max_acr;
	float max_acir;
    float min_acr;
	float min_acir;
	oxy tab10oxy[10];
} mymes;

mymes *init_mesure();
void free_mesure(mymes *myMesure);

oxy mesureTest(char* filename);

oxy mesure (absorp myabsorp, int tab_periode[],mymes *myMesure);	

float ptp (int max_ac, int min_ac);
int spo2 (float rsir);
void calcul(absorp myabsorp, int tab_periode[], mymes *myMesure);