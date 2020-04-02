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
    // init mesure
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


    FILE* myFile = initFichier(filename);
    do{
        myAbsorp = lireFichier(myFile,&etat);
        myAbsorp = fir(myAbsorp,*myFIR);
        myAbsorp = iir(myAbsorp,*myIIR);
        myOxy = mesure(myAbsorp, i, periode, tab_periode, deb, max_acr, max_acir, min_acr, min_acir, debut);
        affichage(myOxy);
    }while( etat != EOF );

    printf("\n\nSPO2 final : ");
    printf("%d", myOxy.spo2);
    printf("    Pouls final : ");
    printf("%d", myOxy.pouls);
}

