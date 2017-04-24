#include "../../utils/includes.h"
#include "includeGUI.h"

int hashUserame(struct hashTable * hashtable, char * username){
	int index = 0;
	int i = 0;
	for(i=0;i<strlen(username);i++){
		index = index + username[i];
	}
	index = index % 100;
	while(hashtable->list[index].username[0] != '\0'){
		index++;
		index = index % 100;
	}
	return index;
}