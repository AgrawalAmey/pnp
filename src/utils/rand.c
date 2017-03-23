#include "./includes.h"
#include "./utils.h"

// Genrates a random string of sepcified length
void random_string(char * string, int length){

	/* Seed number for rand() */
	srand((unsigned int) time(0) + getpid());

	/* ASCII characters 33 to 126 */
	int num_chars = length - 1;
	int i;
  	for (i = 0; i < num_chars; ++i){
		string[i] = rand() % (126 - 33 + 1) + 33;
	}

	string[num_chars] = '\0';
}
