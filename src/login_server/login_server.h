// Definations for all login server functions
#ifndef LOGIN_SERVER
#define LOGIN_SERVER

// TCP Server
void tcpServer(MongoConnection mongoConnection, redisContext ** redisConnection);

// Inserts user into mongodb
int signup(char * name, char * username,
           char * password, MongoConnection mongoConnection);

// Validate user from mongodb
int login(char * username, char * password, MongoConnection mongoConnection);

// Assign session key
char * assignSessionKey(char * sessionKey, char * username, redisContext * redisConnection);

// Assigns a game server
char* assignGameServer(char * gameServerAddr, char * username, redisContext * redisConnection);

#endif // LOGIN_SERVER
