#include "../utils/includes.h"
#include "./game_server.h"

/*
 *  Mongo pokemons model
 *  {
 *      username:string,
 *      pokedex_id:int32,
 *      level: int32,
 *      hp: int32
 *  }
 */

// Make a step in the battle
int
battleStep(char * username0, char * username1, char * battleSessionKey, MongoConnection mongoConnection)
{
    bson_t * query;
    const bson_t * doc;
    mongoc_cursor_t * cursor;
    bson_iter_t iter;
    bson_error_t error;
    redisReply * reply;

    char * pokemonId0[16], pokemonId1[16];
    int health0, health1;

    // //////////////////////////////////////////
    // Verify if it is actually user0's step   //
    // check if the other guy is already ready //
    // //////////////////////////////////////////

    reply = redisCommand(redisConnection, "get battle_turn:%s", battleSessionKey);

    if (reply->type == REDIS_REPLY_STRING) {
        if (strcmp(reply->str, username0) != 0) {
            // Not user 1's turn
            return -1;
        }
    } else {
        // Invalid battle session
        return -2;
    }

    freeReplyObject(reply);

    // ///////////////////////////////////////
    // Get the pokemon id of both pokemons //
    // ///////////////////////////////////////

    reply = redisCommand(redisConnection, "get battle_pokemon_%s:%s", battleSessioKey, username0);
    strcpy(pokemonId0, reply->str);
    freeReplyObject(reply);

    reply = redisCommand(redisConnection, "get battle_pokemon_%s:%s", battleSessioKey, username1);
    strcpy(pokemonId1, reply->str);
    freeReplyObject(reply);

    // Get health of both pokemons
    reply   = redisCommand(redisConnection, "get battle_pokemon_health_%s:%s", battleSessioKey, username0);
    health0 = atoi(reply->str);
    freeReplyObject(reply);

    reply   = redisCommand(redisConnection, "get battle_pokemon_health_%s:%s", battleSessioKey, username1);
    health1 = atoi(reply->str);
    freeReplyObject(reply);

    // ////////////////////////////////////////////
    // Get the hp and level of the two pokemons //
    // ////////////////////////////////////////////

    // Player 0
    // Build query
    query = bson_new();
    BSON_APPEND_UTF8(query, "_id", pokemonId0);

    // Get cursor
    cursor = mongoc_collection_find(mongoConnection.pokemons, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);

    bson_iter_init(&iter, &doc, "pokedex_id");
    pokedexId0 = bson_iter_int32(&iter);
    bson_iter_find(&iter, "level");
    level0 = bson_iter_int32(&iter);
    bson_iter_find(&iter, "hp");
    hp0 = bson_iter_int32(&iter);

    bson_destroy(query);
    mongoc_cursor_destroy(cursor);

    // Player 1
    // Build query
    query = bson_new();
    BSON_APPEND_UTF8(query, "_id", pokemonId1);

    // Get cursor
    cursor = mongoc_collection_find(mongoConnection.pokemons, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);

    bson_iter_init(&iter, &doc, "pokedex_id");
    pokedexId1 = bson_iter_int32(&iter);
    bson_iter_find(&iter, "level");
    level1 = bson_iter_int32(&iter);
    bson_iter_find(&iter, "hp");
    hp1 = bson_iter_int32(&iter);

    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
} /* battleStep */
