#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

void
updatePokemonInfo(char * pokemonId, int new_xp, int new_level, MongoConnection mongoConnection)
{
    bson_t * query;
    const bson_t * update;
    mongoc_cursor_t * cursor;
    bson_iter_t iter;

    query = bson_new();
    BSON_APPEND_INT32(query, "_id", atoi(pokemonId));

    update = BCON_NEW("$set", "{",
      "xp", BCON_INT32(new_xp),
      "level", BCON_INT32(new_level),
      "}");

    // Get cursor
    mongoc_collection_update(mongoConnection.moves, MONGOC_UPDATE_NONE, query, update, NULL, NULL);

    bson_destroy(query);
    bson_destroy(update);
    mongoc_cursor_destroy(cursor);
} /* fetchMoveData */
