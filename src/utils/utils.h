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

//hash password
char * hash(char * password);

#endif // UTILS
