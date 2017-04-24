#include "includeGUI.h"

void initializeSHM(struct hashTable * hashtable){
	hashtable->size = 100;
	int i = 0;
	hashtable->myX = 0;
	hashtable->myY = 0;
	for(i=0;i<100;i++){
		memset(hashtable->list[i].username, '\0', 20);
		hashtable->list[i].x = 0;
		hashtable->list[i].y = 0;
	}
}