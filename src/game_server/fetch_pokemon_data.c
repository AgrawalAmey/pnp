#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

void
fetchPokemonData(pokemon * pok, char * pokemonId, MongoConnection mongoConnection)
{
    double pokedexId;
    bson_t * query;
    const bson_t * doc;
    mongoc_cursor_t * cursor;
    bson_iter_t iter;
    bson_error_t error;

    query = bson_new();
    BSON_APPEND_INT32(query, "_id", atoi(pokemonId));

    // Get cursor
    cursor = mongoc_collection_find(mongoConnection.pokemons, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);
    // Get doc
    mongoc_cursor_next(cursor, &doc);

    bson_iter_init_find(&iter, doc, "pokedexId");
    pokedexId = bson_iter_double(&iter);
    bson_iter_find(&iter, "level");
    pok->level = bson_iter_int32(&iter);
    bson_iter_find(&iter, "xp");
    pok->xp = bson_iter_int32(&iter);

    bson_destroy(query);
    bson_destroy(doc);
    mongoc_cursor_destroy(cursor);

    query = bson_new();
    BSON_APPEND_DOUBLE(query, "id", pokedexId);

    // Get cursor
    cursor = mongoc_collection_find(mongoConnection.pokedex, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);
    // Get doc
    mongoc_cursor_next(cursor, &doc);

    bson_iter_init_find(&iter, doc, "name");
    strcpy(pok->name, bson_iter_utf8(&iter, NULL));
    bson_iter_init_find(&iter, doc, "type0");
    strcat(pok->type0, bson_iter_utf8(&iter, NULL));
    bson_iter_init_find(&iter, doc, "type1");
    strcat(pok->type1, bson_iter_utf8(&iter, NULL));
    bson_iter_init_find(&iter, doc, "move0");
    strcat(pok->move0, bson_iter_utf8(&iter, NULL));
    bson_iter_init_find(&iter, doc, "move1");
    strcat(pok->move1, bson_iter_utf8(&iter, NULL));
    bson_iter_init_find(&iter, doc, "move2");
    strcat(pok->move2, bson_iter_utf8(&iter, NULL));
    bson_iter_init_find(&iter, doc, "move3");
    strcat(pok->move3, bson_iter_utf8(&iter, NULL));
    bson_iter_init_find(&iter, doc, "defense");
    pok->defense = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "poison");
    pok->poison = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "speed");
    pok->speed = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "ground");
    pok->ground = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "spDefense");
    pok->spDefense = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "psychic");
    pok->psychic = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "flying");
    pok->flying = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "ice");
    pok->ice = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "fight");
    pok->fight = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "attack");
    pok->attack = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "steel");
    pok->steel = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "electric");
    pok->electric = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "normal");
    pok->normal = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "fire");
    pok->fire = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "spAttack");
    pok->spAttack = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "hp");
    pok->hp = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "dark");
    pok->dark = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "bug");
    pok->bug = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "ghost");
    pok->ghost = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "water");
    pok->water = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "grass");
    pok->grass = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "capturerate");
    pok->capturerate = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "dragon");
    pok->dragon = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "rock");
    pok->rock = bson_iter_double(&iter);
    bson_iter_init_find(&iter, doc, "expgrowth");
    pok->expgrowth = bson_iter_double(&iter);

    bson_destroy(query);
    bson_destroy(doc);
    mongoc_cursor_destroy(cursor);
} /* fetchPokemonData */
