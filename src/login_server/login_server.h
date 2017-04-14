// Definations for all parser functions
#ifndef LOGIN_SERVER
#define LOGIN_SERVER

// Inserts user into mongodb
int signup(char * name, char * username,
    char * password, MongoConnection mongoConnection);

// Validate user from mongodb
int login(char * username, char * password, MongoConnection mongoConnection);

// Assign session key
char * assignSessionKey(char * sessionKey, char * username, redisContext * redisConnection);

char* assignGameServer(char * gameServerAddr, char * username, redisContext * redisConnection);

#endif // LOGIN_SERVER
