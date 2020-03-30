#include "mesure.h"
/*Fonction mesureTest
BUT : -Fonction de test de le fonction MESURE

Fonction MESURE
BUT : -Calcul de SPO2 (taux de saturation de 
l'oxygène dans le sang)
    -calcul des valeurs PTP de ACir et ACr
    -clacul de RSIR avec DCr, DCir et les valeurs PTP
    -calcul de SPO2 avec le rapport entre RSIR et SP02(%)
-Calcul du rythme cardiaque
    -calcul de la période des signaux ACr et ACir 
    (qui est presque identique)
    -calcul de la fréquence en BPM
-retourne struct type oxy(.SPO2 et .pouls)
->Fichier test d'entre à utiliser : record1_irr.dat*/

oxy mesureTest(char* filename){
	oxy myOxy;
	return myOxy;

}

oxy mesure (absorp myabsorp){
	oxy myoxy;
	//Calcul des valeurs PTP
	int ptp_acir = ptp(myabsorp.acir);
	int ptp_acr = ptp(myabsorp.acr);

	//Calcul de RSIR
	float rsir;
	rsir = (ptp_acr/myabsorp.dcr)/(ptp_acir/myabsorp.dcir);

	//Calcul de SPO2
	myoxy.spo2 = spo2(rsir);

	//calcul de la période
	int per = ;
	//calcul de la frequence en BPM
	myoxy.pouls = 1/per;
}

float ptp (float AC){
	return Ptp = 2*abs(AC);
}

int spo2 (float rsir){
	int int_rsir = (int) rsir;
	int result;
	if (rsir>=0,4 & rsir<=1){
		return result = -(10/0,4)*int_rsir + 110;
	} else if (rsir>1 & rsir<= 3,4){
		return result = -(85/2,4)*int_rsir + 120;
	}else{
		//affiche erreur ??
		break;
	}	
}