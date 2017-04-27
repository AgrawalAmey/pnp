#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

void
fetchMoveData(move * m, char * move, MongoConnection mongoConnection)
{
    bson_t * query;
    const bson_t * doc;
    mongoc_cursor_t * cursor;
    bson_iter_t iter;
    bson_error_t error;

    query = bson_new();
    BSON_APPEND_UTF8(query, "name", move);

    // Get cursor
    cursor = mongoc_collection_find(mongoConnection.moves, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);

    // Get doc
    mongoc_cursor_next(cursor, &doc);

    bson_iter_init_find(&iter, &doc, "type");
    strcpy(m->type, bson_iter_utf8(&iter, NULL));
    bson_iter_find(&iter, "bp");
    pok->bp = bson_iter_int32(&iter);

    bson_destroy(query);
    bson_destroy(doc);
    mongoc_cursor_destroy(cursor);
} /* fetchMoveData */
