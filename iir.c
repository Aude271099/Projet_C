#include "iir.h"
/*Fonction iirTest
BUT : -Fonction de test de le fonction IIR

Fonction IRR
BUT : -Filtre IRR appliqué sur les composantes ACr et ACir
(sert à supprimer la composante continue)
-retourne struct type absorp(.acr, .acir, .dcr et .dcir)
->Fichier test d'entrée à utiliser : record1_fir.dat*/

absorp iirTest(char* filename){
	absorp	myAbsorp;
	
	return myAbsorp;

}


absorp IRR(absorp myAbsorp){
	
	return myAbsorp;
}
/*
absorp iirTest(char* filename){
absorp inData,outData;
iirFilterParam_t* myIir_ps = iirFilterConstruct();
int a,b,c,d;
char x,y;
int fileState;
FILE* file_pf = initFichier(filename);
if(file_pf==NULL){
perror("in iir.c, function iirTest() : file not found");
}

iirFilterInit(myIir_ps);
inData=lireFichier(file_pf,&fileState);

while(fileState != EOF){
outData = iir(inData,myIir_ps);
inData = lireFichier(file_pf,&fileState);
}
finFichier(file_pf);
return outData;
*/