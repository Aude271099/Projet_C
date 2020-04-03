#define _DEFAULT_SOURCE
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


    FILE* myFile = initFichier("Files/test1_c.dat");
    do{
        myAbsorp = lireFichier(myFile,&etat);
        if(etat != EOF){
            myAbsorp = fir(myAbsorp,*myFIR);
            myAbsorp = iir(myAbsorp,*myIIR);
            myOxy = mesure(myAbsorp, tab_periode, myMesure);
            affichage(myOxy);
        }
        // usleep(2000);
    }while( etat != EOF );
    free_fir(myFIR);
    free_iir(myIIR);

    printf("\n\nSPO2 final : ");
    printf("%d", myOxy.spo2);
    printf("    Pouls final : ");
    printf("%d", myOxy.pouls);
    return 1;

}
