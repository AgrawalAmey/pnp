#include "./includes.h"
#include "./utils.h"

//generates the cryptographic hash of the password
char * hash(char * password){

	/* Seed number for rand() */
	srand((unsigned int) time(0) + getpid());

	char * hashedPassword;
	int i, passwordLen, sum = 0, A[8];
	
	hashedPassword = malloc(9 * sizeof(char));
	passwordLen = strlen(password);
	for(i=0;i<passwordLen;i++){
		sum += password[i];
	}
	A[0] = 36;
	A[1] = 28;
	A[2] = 35;
	A[3] = 49;
	A[4] = 1;
	A[5] = 22;
	A[6] = 57;
	A[7] = 24;
	for(i=0;i<8;i++){
		hashedPassword[i] = 65 + (((password[i]*A[i])%100)%26);
	}
	hashedPassword[i] = '\0';
	return hashedPassword;
}