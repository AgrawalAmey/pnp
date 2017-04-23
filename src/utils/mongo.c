#include "./includes.h"
#include "./utils.h"

// Setup mongo connection
void
connectToMongo(MongoConnection * connection)
{
    // Required to initialize libmongoc's internals
    mongoc_init();

    // Create a new client instance
    connection->mongoClient = mongoc_client_new("mongodb://localhost:27017");

    // Get a handle on the database "db_name" and collection "coll_name"
    connection->database = mongoc_client_get_database(connection->mongoClient, "pnp");
    connection->users    = mongoc_client_get_collection(connection->mongoClient, "pnp", "users");
    connection->pokemons = mongoc_client_get_collection(connection->mongoClient, "pnp", "pokemons");
    connection->pokedex  = mongoc_client_get_collection(connection->mongoClient, "pnp", "pokedex");
    connection->moves    = mongoc_client_get_collection(connection->mongoClient, "pnp", "moves");
}

// End mongo connection
void
endMongoConnection(MongoConnection * connection)
{
    // Release our handles and clean up libmongoc
    mongoc_collection_destroy(connection->users);
    mongoc_database_destroy(connection->database);
    mongoc_client_destroy(connection->mongoClient);
    mongoc_cleanup();
}
