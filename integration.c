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
    // absorp myAbsorp;
    // oxy myOxy;
    // int etat = 0;
    
    // FILE *fp = initFichier(filename);
    // lireFichier(fp, etat)



    // myAbsorp = firTest(filename);
    // myAbsorp = iirTest(filename);
    // myAbsorp = mesureTest(filename);
    // affichage(myOxy);
}

// int main(){
// int etat=0;
// absorp myAbsorp;
// oxy myOxy;
// param_fir* myFIR = init_fir(…); // init FIR
// param_iir* myIIR = init_iir(…); // init IIR
// param_mesure* myMes = init_mesure(…) // init mesure
// FILE* myFile = initFichier("record1.dat");
// do{
// myAbsorp = lireFichier(myFile,&etat);
// myAbsorp = fir(myAbsorp,myFIR);
// myAbsorp = iir(myAbsorp,myIIR);
// myOxy = mesure(myAbsorp,myMes);
// affichage(myOxy);
// }while( etat != EOF );
// finFichier(myFile);
// fin_mesure(myMes);
// fin_iir(myIIR);
// fin_fir(myFIR) ;
// return EXIT_SUCCESS;
// }