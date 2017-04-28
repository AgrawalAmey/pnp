#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

void
fetchUserData(user * u, char * username, MongoConnection mongoConnection)
{
    int pokedexId;
    bson_t * query;
    const bson_t * doc;
    mongoc_cursor_t * cursor;
    bson_iter_t iter;
    bson_error_t error;

    query = bson_new();
    BSON_APPEND_UTF8(query, "_id", username);

    // Get cursor
    cursor = mongoc_collection_find(mongoConnection.pokemons, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);
    // Get doc
    mongoc_cursor_next(cursor, &doc)

    bson_iter_init(&iter, &doc);
    bson_iter_find(&iter, "level");
    u->level = bson_iter_int32(&iter);
    bson_iter_find(&iter, "xp");
    u->xp = bson_iter_int32(&iter);
    bson_iter_find(&iter, "name");
    strcpy(u->name, bson_iter_int32(&iter));

    bson_destroy(query);
    bson_destroy(doc);
    mongoc_cursor_destroy(cursor);
} /* fetchPokemonData */
