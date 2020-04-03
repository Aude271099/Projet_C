#include "define.h"
#include "affichage.h"
#include "mesure.h"
#include "fir.h"
#include "iir.h"
#include "lecture.h"
#include "fichiers.h"
#include "integration.h"

int main(){
    /*int etat=0;
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
    return 1;*/



    FILE* pf;
	absorp myAbsorp;
	float metric1, metric2;
	oxy	mes,ref;
	int spo2data;
	int poulsdata;
	char* myFile;

	/*************************
	Check all the program with test1
	**************************/


myFile = "Files/test1_c.dat";
	// Last values :
	// SP02 = 50
	// pouls = 180
	ref.spo2=50;
	ref.pouls=180;

	// Initialise data.txt with values
	mes.spo2 = 30;
	mes.pouls = 40;
	pf=fopen("Data.txt","w");
	if(pf==NULL){
		perror("in test_integration.c, file not found");
	}
	fprintf(pf,"%d\n%d\n",mes.spo2,mes.pouls);
	fclose(pf);
	integrationTest(myFile);
	pf=fopen("Data.txt","r");
	if(pf==NULL){
		//#ifdef DEBUG
		printf("test_integration2 KO [unable to open Data.txt]\n");
		//#endif
		//CU_FAIL("test_integration2");
	}
	else
	{
		fscanf(pf,"%d\n%d",&spo2data,&poulsdata);
		fclose(pf);

		metric1 = fabs(spo2data-ref.spo2);
		metric2 = fabs(poulsdata-ref.pouls);

		if(metric1>2.0){
			//#ifdef DEBUG
			printf("test_integration2 KO [spo2=%d %% instead of %d %%]\n",spo2data,ref.spo2);
			//#endif
			//CU_FAIL("test_integration2");
		}
		else
		{
			if(metric2>5.0){
				//#ifdef DEBUG
				printf("test_integration2 KO [pouls=%d bpm instead of %d bpm]\n",poulsdata,ref.pouls);
				//#endif
				//CU_FAIL("test_integration2");
			}
			else
			{
				//#ifdef DEBUG
				printf("test_integration2 OK\n");
				//#endif
				//CU_PASS("test_integration2");
			}
		}
	}

}
