#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

void
fetchLeaderBoard(char * outBuffer, MongoConnection mongoConnection)
{
    bson_t * filter;
    bson_t * doc;
    bson_t * opts;
    mongoc_cursor_t * cursor;
    bson_iter_t iter;
    bson_error_t error;
    int i = 0;
    char temp[20];

    filter = bson_new();

    opts = BCON_NEW(
      "limit", BCON_INT64(10), "sort", "{", "xp", BCON_INT32(1), "}");

    // Get cursor
    cursor = mongoc_collection_find_with_opts(mongoConnection.users, filter, opts, NULL);


    while (mongoc_cursor_next(cursor, &doc) && i < 10) {
        i++;
    }

    sprintf(outBuffer, "%d ", i);
    if (i > 0) {
        i      = 0;
        cursor = mongoc_cursor_clone(cursor);

        while (mongoc_cursor_next(cursor, &doc) && i < 10) {
            printf("%s\n", outBuffer);
            bson_iter_init(&iter, doc);
            bson_iter_find(&iter, "_id");
            strcat(outBuffer, bson_iter_utf8(&iter, NULL));
            strcat(outBuffer, " ");
            bson_iter_find(&iter, "level");
            sprintf(temp, "%d ", bson_iter_int32(&iter));
            strcat(outBuffer, temp);
            bson_iter_find(&iter, "xp");
            sprintf(temp, "%d ", bson_iter_int32(&iter));
            strcat(outBuffer, temp);
            i++;
        }
    }
    bson_destroy(filter);
    mongoc_cursor_destroy(cursor);
} /* fetchPokemonData */
