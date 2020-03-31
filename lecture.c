#include "lecture.h"
/*BUT : -Lire le document de donnée afin d'extraire
et reconnaitre ACr, DCr, ACir et DCir 
-Recadrer les composantes alternatives ACr et ACir
autour de 0 
-retourne struct type absorp(.acr, .acir, .dcr et .dcir)
->à la fin de la lecture du fichier la variable d'état
passe à EOF
->Fichier test d'entrée à utiliser : record1_bin.dat*/

absorp lecture(FILE* file_pf, int* file_state){
	//Initialisations
	absorp myAbsorp;
	char x,y;
	int a=0,b=0,c=0,d=0;

	//Lecture fichier
	fscanf(file_pf,"%d,%d,%d,%d%c%c",&a,&b,&c,&d,&x,&y);

	//Mise à EOF de l'état lorsque le fichier à fini d'être lu
	if (a == 0 && b==0 && c==0 && d==0){
		*file_state=EOF;
		return;
	}
	
	//Calcul du nombre utilisé pour centré ACr et ACir
	int centre = 4096/2;

	//Renvoie de myabsorb mis à jour
	myAbsorp = init_myabsorp (a, b, c, d, centre);
	printf("%f,%f,%f,%f\n", myAbsorp.acr, myAbsorp.dcr, myAbsorp.acir, myAbsorp.dcir);
	return myAbsorp; //return EOF flag

}

absorp init_myabsorp(int a,int b,int c,int d, int centre){
	absorp myAbsorp;
	myAbsorp.acir = c - centre;
	myAbsorp.acr = a - centre;
	myAbsorp.dcir =d;
	myAbsorp.dcr = b;
	return myAbsorp;
}