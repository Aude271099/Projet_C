#include "lecture.h"
/*BUT : -Lire le document de donnée afin d'extraire
et reconnaitre ACr, DCr, ACir et DCir 
-Recadrer les composantes alternatives ACr et ACir
autour de 0 
-retourne struct type absorp(.acr, .acir, .dcr et .dcir)
-ignore les lignes corrompues
->à la fin de la lecture du fichier la variable d'état
passe à EOF
->Fichier test d'entrée à utiliser : record1_bin.dat*/

absorp lecture(FILE* file_pf, int* file_state){
	//Initialisations
	absorp myAbsorp;
	myAbsorp.acr = 0;
	myAbsorp.acir = 0;
	myAbsorp.dcr = 0;
	myAbsorp.dcir = 0;
	int a=0,b=0,c=0,d=0;
	char chaine[25];
	int corrompu = 1;

	//Vérification des lignes corrompues et lecture du fichier
	while (corrompu == 1){
		int nb = 0;
		
		fgets(chaine, 25, file_pf);
		
		//Mise à EOF de l'état lorsque le fichier à fini d'être lu
		if (feof(file_pf)){
			*file_state=EOF;
			return myAbsorp;
		}
		
		char delim[] = ",";
		char* ptr = strtok(chaine, delim);
		while(ptr != NULL){
			
			if(nb == 0){
				a = atoi(ptr) ;
			}else if (nb == 1)		{
				b = atoi(ptr);
			}else if (nb == 2)		{
				c = atoi(ptr);
			}else if (nb == 3)		{
				d = atoi(ptr);
			}
	
			ptr = strtok(NULL, delim);
			nb ++;
		}

		//Ignorement des lignes corompues
		if (nb == 4){
			printf("ligne pas corrompue\n");
			corrompu = 0;
		}else{
			printf("ligne corrompue\n");

		}
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

