// Definations for all util functions
#ifndef UTILS
#define UTILS

// Genrates a random string of sepcified length
void random_string(char * string, int length);

// Spilits string using a delimter
char** strSplit(char* a_str, const char a_delim);

// Setup mongo connection
void connectToMongo(MongoConnection *connection);

// End mongo connection
void endMongoConnection(MongoConnection *connection);

// Setup redis connection
void connectToRedis(redisContext **c);

// End redis connection
void endRedisConnection(redisContext *c);

//hash password
char * hash(char * password);

int
startsWith(const char * pre, const char * str);

int pow(int x, unsigned int y);

#endif // UTILS
