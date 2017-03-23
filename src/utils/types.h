// Definations for all util functions
#ifndef TYPES
#define TYPES

// Define struct for mongo connection
typedef struct{
    mongoc_client_t *mongoClient;
    mongoc_database_t *database;
    mongoc_collection_t *users;
} MongoConnection;

#endif // TYPES
