#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

void
fetchPokemonList(char * outBuffer, char * username, MongoConnection mongoConnection)
{
    int pokedexId;
    bson_t * query;
    bson_t * doc;
    mongoc_cursor_t * cursor;
    bson_iter_t iter;
    bson_error_t error;
    int i = 0;
    char temp[20];

    query = bson_new();
    BSON_APPEND_UTF8(query, "username", username);

    // Get cursor
    cursor = mongoc_collection_find(mongoConnection.pokemons, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);

    while (mongoc_cursor_next(cursor, &doc)) {
        i++;
    }

    sprintf(outBuffer, "%d ", i);
    if (i > 0) {
        cursor = mongoc_cursor_clone(cursor);

        while (mongoc_cursor_next(cursor, &doc)) {
            printf("%s\n", outBuffer);
            bson_iter_init(&iter, doc);
            bson_iter_find(&iter, "_id");
            sprintf(temp, "%d ", bson_iter_int32(&iter));
            strcat(outBuffer, temp);
            bson_iter_find(&iter, "pokedexId");
            sprintf(temp, "%lf ", bson_iter_double(&iter));
            strcat(outBuffer, temp);
            bson_iter_find(&iter, "level");
            sprintf(temp, "%d ", bson_iter_int32(&iter));
            strcat(outBuffer, temp);
            bson_iter_find(&iter, "xp");
            sprintf(temp, "%d", bson_iter_int32(&iter));
            strcat(outBuffer, temp);
            printf("%s\n", outBuffer);
        }
    }
    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
} /* fetchPokemonData */
