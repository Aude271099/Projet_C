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
    /*myabsorp.acir = 0;
    myabsorp.acr = 0;
    myabsorp.dcir = 2030;
    myabsorp.dcr = 2030;
    oxy myOxy;
    myOxy.spo2 = 98;
    myOxy.pouls = 104;*/

   
    /* while (etat != EOF){
        //myabsorp = lecture(fichier, &etat);
        //myabsorp = fir(myabsorp, tab_acr, tab_acir);
        //myabsorp = irr(myabsorp, tab_acr, tab_acir, tab_signal_sortie);
        //myOxy = mesure(myabsorp, max_acr, max_acir, min_acr, min_acir, debut);
        //affichage(myOxy);
    }*/
    //printf("hello");
   /* myOxy = mesureTest("record1_iir.dat");
    //mesure(absorp myabsorp, int* max_acr, int* max_acir, int* min_acr, int* min_acir, int* debut);
    //signal_FIR = firTest("record1.dat");
    return 1;*/


float metric;
	char* myFile = "Files/test2_f2.dat";
	oxy mes;
	oxy ref;
	ref.pouls = 120;
	ref.spo2=92;

	/*******************************
	Check mesure function: pulse
	*********************************/
	mes=mesureTest(myFile);	//Sp02=92, pouls=120
	metric = fabs(mes.pouls-ref.pouls);


	if(metric>5.0){
		printf("test_mesure_pouls KO [%d bpm instead of %d bpm]\n",mes.pouls,ref.pouls);
	}else{
		printf("test_mesure_pouls OK \n");
	}

	metric = fabs(mes.spo2-ref.spo2);

	if(metric>5.0){
		printf("test_mesure_spo2 KO [%d %% instead of %d %%]\n",mes.spo2,ref.spo2);
	}else{
		printf("test_mesure_spo2 OK \n");
	}
}
