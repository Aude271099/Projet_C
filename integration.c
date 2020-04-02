/*BUT : -ouvre et lit les valeurs d'absorption contenu 
dans le fichier str des fct FIR, IRR, MESURE et AFFICHAGE
->Ensuite ces fct seront appelées itérativement 
jusqu'a la fin de la lecture du fichier
*/

#include "integration.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "affichage.h"
#include "fichiers.h"

void integrationTest(char* filename)
{
    int etat=0;
    absorp myAbsorp;
    oxy myOxy;
    param_fir* myFIR = init_fir(); // init FIR
    param_iir* myIIR = init_iir(); // init IIR
    mymes * myMesure = init_mesure();
    // init mesure
    //Initialisation des pointeurs 
    int tab_periode[100];
	int j ;
	for(j = 0; j < 100; j++){
		tab_periode[j] = 0;
	}

    FILE* myFile = initFichier(filename);
    do{
        myAbsorp = lireFichier(myFile,&etat);
        if(etat != EOF){
            myAbsorp = fir(myAbsorp,*myFIR);
            myAbsorp = iir(myAbsorp,*myIIR);
            myOxy = mesure(myAbsorp, tab_periode, myMesure);
            affichage(myOxy);
        }
    }while( etat != EOF );

    free_fir(myFIR);
    free_iir(myIIR);

    printf("\n\nSPO2 final : ");
    printf("%d", myOxy.spo2);
    printf("    Pouls final : ");
    printf("%d", myOxy.pouls);
}

