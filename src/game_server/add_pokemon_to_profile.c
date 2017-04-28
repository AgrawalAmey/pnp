#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

/*
 *  Mongo pokemons model
 *  {
 *      username:string,
 *      pokedexId:int32,
 *      level: int32,
 *      xp: int32
 *  }
 */

/**
 * [addPokemon Inserts pet pokemons into mongodb]
 * @param  username
 * @param  pokedexId
 * @param  level
 * @param  xp
 * @param  mongoConnection
 * @return                 [Success value]
 */
int
addPokemon(char * username, int pokedexId, int level, int xp, MongoConnection mongoConnection)
{
    bson_t * document;
    bson_error_t error;
    int exitCode;

    // Create user bson
    document = bson_new();
    BSON_APPEND_INT32(document, "_id", rand());
    BSON_APPEND_UTF8(document, "username", username);
    BSON_APPEND_DOUBLE(document, "pokedexId", pokedexId);
    BSON_APPEND_INT32(document, "level", level);
    BSON_APPEND_INT32(document, "xp", xp);

    // Insert pokemon
    if (!mongoc_collection_insert(mongoConnection.pokemons, MONGOC_INSERT_NONE, document, NULL, &error)) {
        fprintf(stderr, "%s\n", error.message);
        // gen return on error
        exitCode = -1;
    } else {
        // Every thing is fine
        exitCode = 0;
    }

    bson_destroy(document);

    return exitCode;
}
