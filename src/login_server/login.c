#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include "./login_server.h"

/*
    Mongo user model
    {
        username:string,
        name:string,
        password:string
    }
*/

// Validate user from mongodb
int login(char * username, char * password){
    mongoc_client_t *mongoClient;
	mongoc_database_t *database;
	mongoc_collection_t *collection;
    bson_t *document;
	bson_error_t error;
    int exitCode;

    // Required to initialize libmongoc's internals
    mongoc_init();

    // Create a new client instance
    mongoClient = mongoc_client_new("mongodb://localhost:27017");

    // Get a handle on the database "db_name" and collection "coll_name"
    database = mongoc_client_get_database(mongoClient, "pnp");
    collection = mongoc_client_get_collection(mongoClient, "pnp", "users");

    // Build query
    query = bson_new();
    BSON_APPEND_UTF8(query, "_id", username);
    BSON_APPEND_UTF8(query, "password", password);

    // Get cursor
    cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);

    if(mongoc_cursor_next(cursor, &doc)){
        // username and password are correct
        exitCode = 0;
    } else {
        // Error
        exitCode = -1;
    }

    bson_destroy (query);
    mongoc_cursor_destroy (cursor);
    // Release our handles and clean up libmongoc
	mongoc_collection_destroy(collection);
	mongoc_database_destroy(database);
	mongoc_client_destroy(mongoClient);
	mongoc_cleanup();

	return exitCode;
}
