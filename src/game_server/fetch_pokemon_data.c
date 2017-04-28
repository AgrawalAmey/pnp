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
    BSON_APPEND_UTF8(query, "_id", pokemonId);

    // Get cursor
    cursor = mongoc_collection_find(mongoConnection.pokemons, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);
    // Get doc
    mongoc_cursor_next(cursor, &doc)

    bson_iter_init_find(&iter, &doc, "pokedex_id");
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

    bson_iter_init_find(&iter, &doc, "name");
    strcpy(pok->name, bson_iter_utf8(&iter, NULL));
    bson_iter_find(&iter, "type0");
    strcat(pok->type0, bson_iter_utf8(&iter, NULL));
    bson_iter_find(&iter, "type1");
    strcat(pok->type1, bson_iter_utf8(&iter, NULL));
    bson_iter_find(&iter, "move0");
    strcat(pok->move0, bson_iter_utf8(&iter, NULL));
    bson_iter_find(&iter, "move1");
    strcat(pok->move1, bson_iter_utf8(&iter, NULL));
    bson_iter_find(&iter, "move2");
    strcat(pok->move2, bson_iter_utf8(&iter, NULL));
    bson_iter_find(&iter, "move3");
    strcat(pok->move3, bson_iter_utf8(&iter, NULL));
    bson_iter_find(&itr, "defense");
    pok->defense = bson_iter_double(&iter);
    bson_iter_find(&itr, "poison");
    pok->poison = bson_iter_double(&iter);
    bson_iter_find(&itr, "speed");
    pok->speed = bson_iter_double(&iter);
    bson_iter_find(&itr, "ground");
    pok->ground = bson_iter_double(&iter);
    bson_iter_find(&itr, "spDefense");
    pok->spDefense = bson_iter_double(&iter);
    bson_iter_find(&itr, "psychic");
    pok->psychic = bson_iter_double(&iter);
    bson_iter_find(&itr, "flying");
    pok->flying = bson_iter_double(&iter);
    bson_iter_find(&itr, "ice");
    pok->ice = bson_iter_double(&iter);
    bson_iter_find(&itr, "fight");
    pok->fight = bson_iter_double(&iter);
    bson_iter_find(&itr, "attack");
    pok->attack = bson_iter_double(&iter);
    bson_iter_find(&itr, "steel");
    pok->steel = bson_iter_double(&iter);
    bson_iter_find(&itr, "electric");
    pok->electric = bson_iter_double(&iter);
    bson_iter_find(&itr, "normal");
    pok->normal = bson_iter_double(&iter);
    bson_iter_find(&itr, "fire");
    pok->fire = bson_iter_double(&iter);
    bson_iter_find(&itr, "spAttack");
    pok->spAttack = bson_iter_double(&iter);
    bson_iter_find(&itr, "hp");
    pok->hp = bson_iter_double(&iter);
    bson_iter_find(&itr, "dark");
    pok->dark = bson_iter_double(&iter);
    bson_iter_find(&itr, "bug");
    pok->bug = bson_iter_double(&iter);
    bson_iter_find(&itr, "ghost");
    pok->ghost = bson_iter_double(&iter);
    bson_iter_find(&itr, "water");
    pok->water = bson_iter_double(&iter);
    bson_iter_find(&itr, "grass");
    pok->grass = bson_iter_double(&iter);
    bson_iter_find(&itr, "capturerate");
    pok->capturerate = bson_iter_double(&iter);
    bson_iter_find(&itr, "dragon");
    pok->dragon = bson_iter_double(&iter);
    bson_iter_find(&itr, "rock");
    pok->rock = bson_iter_double(&iter);
    bson_iter_find(&itr, "expgrowth");
    pok->expgrowth = bson_iter_double(&iter);

    bson_destroy(query);
    bson_destroy(doc);
    mongoc_cursor_destroy(cursor);
} /* fetchPokemonData */
