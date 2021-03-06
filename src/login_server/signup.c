#include "../utils/includes.h"
#include "./login_server.h"

/*
 *  Mongo user model
 *  {
 *      username:string,
 *      name:string,
 *      password:string,
 *      level: int32,
 *      xp: int32
 *  }
 */

// Inserts user into mongodb
int
signup(char * name, char * username, char * password, MongoConnection mongoConnection)
{
    bson_t * document;
    bson_error_t error;
    int exitCode;

    // Create user bson
    document = bson_new();
    BSON_APPEND_UTF8(document, "_id", username);
    BSON_APPEND_UTF8(document, "name", name);
    BSON_APPEND_UTF8(document, "password", password);
    BSON_APPEND_INT32(document, "level", 1);
    BSON_APPEND_INT32(document, "xp", 10);

    // Insert user
    if (!mongoc_collection_insert(mongoConnection.users, MONGOC_INSERT_NONE, document, NULL, &error)) {
        // To specify that username is not unique
        if (error.code == 11000) {
            exitCode = -2;
        } else {
            fprintf(stderr, "%s\n", error.message);
            // gen return on error
            exitCode = -1;
        }
    } else {
        // Every thing is fine
        exitCode = 0;
    }

    bson_destroy(document);

    return exitCode;
}
