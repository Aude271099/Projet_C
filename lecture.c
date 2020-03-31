#include "lecture.h"
/*BUT : -Ouvrir le document de donnée afin d'extraire
et reconnaitre ACr, DCr, ACir et DCir 
-Recadrer les composantes alternatives ACr et ACir
autour de 0 
-retourne struct type absorp(.acr, .acir, .dcr et .dcir)
->à la fin de la lecture du fichier la variable d'état
passe à EOF
->Fichier test d'entrée à utiliser : record1_bin.dat*/

absorp lecture(FILE* file_pf, int* file_state){

	absorp myAbsorp;
	*file_state=EOF;
	
	return myAbsorp; // return EOF flag

}

