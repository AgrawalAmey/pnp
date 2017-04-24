// Definations for all udpGameClient functions
#ifndef UDPGAMECLIENT
#define UDPGAMECLIENT

void udpGameClient(struct hashTable * hashtable, char * sessionKey, char * serverAddr, char * username);

void populateSHM(struct hashTable * hashtable, char * userPositions);

#endif // UDPGAMECLIENT
