#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include "./utils.h"
#include "./types.h"

// Setup mongo connection
MongoConnection* connectToMongo(){
    MongoConnection connection;

    // Required to initialize libmongoc's internals
    mongoc_init();

    // Create a new client instance
    connection.mongoClient = mongoc_client_new("mongodb://localhost:27017");

    // Get a handle on the database "db_name" and collection "coll_name"
    connection.database = mongoc_client_get_database(connection.mongoClient, "pnp");
    connection.collection = mongoc_client_get_collection(connection.mongoClient, "pnp", "users");

    // Release our handles and clean up libmongoc
	mongoc_collection_destroy(connection.collection);
	mongoc_database_destroy(connection.database);
	mongoc_client_destroy(connection.mongoClient);
	mongoc_cleanup();
}
