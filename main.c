#include "define.h"
#include "affichage.h"
#include "mesure.h"
#include "fir.h"
#include "iir.h"
#include "lecture.h"
#include "fichiers.h"
#include "integration.h"

int main(){
    int etat=0;
    absorp myAbsorp;
    oxy myOxy;
    param_fir* myFIR = init_fir(); // init FIR
    param_iir* myIIR = init_iir(); // init IIR
    mymes* myMesure = init_mesure(); //init mesure
    //Initialisation des pointeurs 
    int tab_periode[100];
	int j ;
	for(j = 0; j < 100; j++){
		tab_periode[j] = 0;
	}
	int* periode =malloc(sizeof(int));
	int* deb =malloc(sizeof(int));
	int* i =malloc(sizeof(int));
	int* debut = malloc(sizeof(int));
	int* max_acr = malloc(sizeof(int));
	int* max_acir = malloc(sizeof(int));
    int* min_acr = malloc(sizeof(int));
	int* min_acir = malloc(sizeof(int));
	*periode = 0;
	*deb = 0;
	*debut = 0;
	*i = 0;
	*max_acr = 0;
	*max_acir = 0;
	*min_acr = 0; 
	*min_acir = 0;


    FILE* myFile = initFichier("test2_c.dat");
    do{
        myAbsorp = lecture(myFile,&etat);
        myAbsorp = fir(myAbsorp,*myFIR);
        myAbsorp = iir(myAbsorp,*myIIR);
        myOxy = mesure(myAbsorp, tab_periode, myMesure);
        affichage(myOxy);
    }while( etat != EOF );
    free_fir(myFIR);
    free_iir(myIIR);

    printf("\n\nSPO2 final : ");
    printf("%d", myOxy.spo2);
    printf("    Pouls final : ");
    printf("%d", myOxy.pouls);
    return 1;
}
