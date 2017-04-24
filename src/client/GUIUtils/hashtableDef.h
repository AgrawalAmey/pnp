// Definations for all util functions
#ifndef HASHTABLEDEF
#define HASHTABLEDEF

struct hashtableNode{
	char username[20];
	int x;
	int y;
};

struct hashTable{
	int size;
	int myX;
	int myY;
	struct hashtableNode list[100];
};

#endif