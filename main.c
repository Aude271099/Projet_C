#include "define.h"
#include "affichage.h"
#include "mesure.h"
<<<<<<< HEAD
#include "fichiers.h"
#include "lecture.h"
=======
#include "fir.h"
>>>>>>> 29a88d1b07ed1adb4009ea4684b22c60e8f12110

int main(){
    int etat = 0;
    FILE* fichier = initFichier("record1_bin.dat");
    absorp myabsorp ;
    absorp signal_FIR;
    myabsorp.acir = 0;
    myabsorp.acr = 0;
    myabsorp.dcir = 2030; 
    myabsorp.dcr = 2030;
    oxy myOxy;
    myOxy.spo2 = 98;
    myOxy.pouls = 104;
    
    
    
    //mesure(myabsorp);
    //affichage(myOxy);
    signal_FIR = firTest("record1.dat");
    return 1;
}