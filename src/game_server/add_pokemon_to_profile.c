#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

/*
 *  Mongo pokemons model
 *  {
 *      username:string,
 *      pokedexId:int32,
 *      level: int32,
 *      hp: int32
 *  }
 */

/**
 * [addPokemon Inserts pet pokemons into mongodb]
 * @param  pokemonId       [16 byte string PokemonId returned if successful]
 * @param  username
 * @param  pokedexId
 * @param  level
 * @param  hp
 * @param  mongoConnection
 * @return                 [Success value]
 */
int
addPokemon(char * pokemonId, char * username, int pokedexId, int level, int hp, MongoConnection mongoConnection)
{
    bson_t * document;
    bson_error_t error;
    int exitCode;

    // Get a random pokemon id
    random_string(pokemonId, 16);
    // Create user bson
    document = bson_new();
    BSON_APPEND_UTF8(document, "_id", pokemonId);
    BSON_APPEND_UTF8(document, "username", username);
    BSON_APPEND_INT(document, "pokedexId", pokedexId);
    BSON_APPEND_INT(document, "level", level);
    BSON_APPEND_INT(document, "hp", hp);

    // Insert pokemon
    if (!mongoc_collection_insert(mongoConnection.pokemon, MONGOC_INSERT_NONE, document, NULL, &error)) {
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
