#include "define.h"
#include "affichage.h"
#include "mesure.h"

int main(){
    absorp myabsorp ;
    myabsorp.acir = 0;
    myabsorp.acr = 0;
    myabsorp.dcir = 2030; 
    myabsorp.dcr = 2030;
    oxy myOxy;
    myOxy.spo2 = 98;
    myOxy.pouls = 104;
    mesure(myabsorp);
    //affichage(myOxy);
    return 1;
}