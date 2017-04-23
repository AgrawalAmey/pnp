// Definations for all parser functions
#ifndef GAME_SERVER
#define GAME_SERVER

// Validate the session of user
int validateSession(char * username, char * sessionKey, redisContext * redisConnection);

// TCP Server
void tcpServer(MongoConnection mongoConnection, redisContext ** redisConnection);

// UDP Server
void udpServer(MongoConnection mongoConnection, redisContext ** redisConnection);

// Store the position of user and returns position of nearby users
void
handlePositionRequest(char * outBuffer, char * username, char * position, double timestamp,
  redisContext * redisConnection);

#endif // GAME_SERVER
