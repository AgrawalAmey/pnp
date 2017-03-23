#include "../utils/includes.h"
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
int login(char * username, char * password, MongoConnection mongoConnection){
    bson_t *query;
    const bson_t *doc;
    mongoc_cursor_t *cursor;
	bson_error_t error;
    int exitCode;

    // Build query
    query = bson_new();
    BSON_APPEND_UTF8(query, "_id", username);
    BSON_APPEND_UTF8(query, "password", password);

    // Get cursor
    cursor = mongoc_collection_find(mongoConnection.users, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);

    if(mongoc_cursor_next(cursor, &doc)){
        // username and password are correct
        exitCode = 0;
    } else {
        // Error
        exitCode = -1;
    }

    bson_destroy (query);
    mongoc_cursor_destroy (cursor);

	return exitCode;
}
