// Definations for all parser functions
#ifndef LOGIN_SERVER
#define LOGIN_SERVER

// Inserts user into mongodb
int signup(char * name, char * username,
    char * password, MongoConnection mongoConnection);

// Validate user from mongodb
int login(char * username, char * password, MongoConnection mongoConnection);

#endif // LOGIN_SERVER
