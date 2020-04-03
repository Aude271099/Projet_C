#include "fichiers.h"

//fonction d'initialisation du fichier
FILE* initFichier(char* nomFichier ){
	
	FILE* pf=fopen(nomFichier,"r");//ouverture du fichier
	if(pf==NULL){ //si le fichier ne s'ouvre pas
		printf("dans fichiers.c : erreur ouverture fichier %s\n",nomFichier); //affichage d'une erreur
		exit(EXIT_FAILURE);//on ferme le programme
	}
	return pf; //on retourne le fichier
}

//fonction de lecture de fichier retournant un absorp correspondant au signal d'entrée
absorp lireFichier(FILE* pf, int* etat){
	absorp myAbsorp;//signal d'entrée
	char x,y;
	int a=0,b=0,c=0,d=0; //4 variables pour séparer les données d'une ligne des fichiers
	*etat=fscanf(pf,"%d,%d,%d,%d%c%c",&a,&b,&c,&d,&x,&y); //séparation des 4 valeurs
	myAbsorp.acr=a; //acr du signal d'entrée
	myAbsorp.dcr=b; //dcr du signal d'entrée
	myAbsorp.acir=c; //acir du signal d'entrée
	myAbsorp.dcir=d; //dcir du signal d'entrée
	return myAbsorp; //on retourne le signal d'entrée
}

//fonction de fermeture du fichier
void finFichier(FILE* pf){
	fclose(pf);


}

