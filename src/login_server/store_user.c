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

// Inserts user into mongodb
int insertUser(char * name, char * username, char * password){
    mongoc_client_t *mongoClient;
	mongoc_database_t *database;
	mongoc_collection_t *collection;
    bson_t *document;
	bson_error_t error;

    // Required to initialize libmongoc's internals
    mongoc_init();

    // Create a new client instance
    mongoClient = mongoc_client_new("mongodb://localhost:27017");

    // Get a handle on the database "db_name" and collection "coll_name"
    database = mongoc_client_get_database(mongoClient, "pnp");
    collection = mongoc_client_get_collection(mongoClient, "pnp", "users");

    // Create user bson
    document = bson_new ();
    BSON_APPEND_UTF8(document, "_id", username);
    BSON_APPEND_UTF8(document, "name", name);
    BSON_APPEND_UTF8(document, "password", password);

    // Insert user
    if (!mongoc_collection_insert(collection, MONGOC_INSERT_NONE, document, NULL, &error)) {
        // To specify that username is not unique
        if(error.code == 11000){
            return -2;
        }
        fprintf(stderr, "%d\n", error.message);
        // gen return on error
        return -1;
    }

	bson_destroy(document);

    // Release our handles and clean up libmongoc
	mongoc_collection_destroy(collection);
	mongoc_database_destroy(database);
	mongoc_client_destroy(mongoClient);
	mongoc_cleanup();

	return 0;
}
