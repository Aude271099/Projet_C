#include "define.h"
#include "affichage.h"
#include "mesure.h"
#include "fir.h"
#include "lecture.h"
#include "fichiers.h"

int main(){
    //int etat = 0;

    

    //FILE* fichier = initFichier("record1_irr.dat");
    //absorp myabsorp ;
    //absorp signal_FIR;
    myabsorp.acir = 0;
    myabsorp.acr = 0;
    myabsorp.dcir = 2030;
    myabsorp.dcr = 2030;
    oxy myOxy;
    myOxy.spo2 = 98;
    myOxy.pouls = 104;
   
    /* while (etat != EOF){
        //myabsorp = lecture(fichier, &etat);
        //myabsorp = fir(myabsorp, tab_acr, tab_acir);
        //myabsorp = irr(myabsorp, tab_acr, tab_acir, tab_signal_sortie);
        //myOxy = mesure(myabsorp, max_acr, max_acir, min_acr, min_acir, debut);
        //affichage(myOxy);
    }*/
    //printf("hello");
     myOxy = mesureTest("record1_iir.dat");
    //mesure(absorp myabsorp, int* max_acr, int* max_acir, int* min_acr, int* min_acir, int* debut);
    //signal_FIR = firTest("record1.dat");
    return 1;
}
