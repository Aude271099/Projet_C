#include "define.h"
#include "affichage.h"

int main(){
    oxy myOxy;
    myOxy.spo2 = 98;
    myOxy.pouls = 104;

    affichage(myOxy);
    return 1;
}