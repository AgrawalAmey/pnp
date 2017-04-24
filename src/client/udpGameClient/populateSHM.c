#include "./../GUIUtils/includeGUI.h"
#include "./udpGameClient.h"
#include "../../utils/includes.h"
#include "../../utils/utils.h"

void populateSHM(struct hashTable * hashtable, char * userPositions){
	char ** positionArray;
	positionArray = strSplit(userPositions, ' ');
	int entries = atoi(positionArray[0]);

	int i = 1;

	for(i=1;i<=entries;i++){
		strcpy(hashtable->list[i].username, positionArray[2*i - 1]);
		char ** positions = strSplit(positionArray[2*i], ':');
		hashtable->list[i].x = atoi(positions[0]);
		hashtable->list[i].y = atoi(positions[1]);
	}
}