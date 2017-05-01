#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

/*
 *  Mongo pokemons model
 *  {
 *      username:string,
 *      pokedex_id:int32,
 *      level: int32,
 *      xp: int32
 *  }
 */

// Make a step in the battle
void
battleStep(char * outBuffer, char * username0, char * username1, char * move_str, char * battleSessionKey,
  redisContext * redisConnection,
  MongoConnection mongoConnection)
{
    redisReply * reply;

    char pokemonId0[16], pokemonId1[16];

    // //////////////////////////////////////////
    // Verify if it is actually user0's step   //
    // check if the other guy is already ready //
    // //////////////////////////////////////////

    reply = redisCommand(redisConnection, "get battle_turn:%s", battleSessionKey);

    if (reply->type == REDIS_REPLY_STRING) {
        if (strcmp(reply->str, username0) != 0) {
            // Not user 1's turn
            strcpy(outBuffer, "invalid_turn");
            return;
        }
    } else {
        // Invalid battle session
        strcpy(outBuffer, "invalid_game_session");
        return;
    }

    freeReplyObject(reply);

    // ///////////////////////////////////////
    // Get the pokemon id of both pokemons //
    // ///////////////////////////////////////

    reply = redisCommand(redisConnection, "get battle_pokemon_%s:%s", battleSessionKey, username0);
    strcpy(pokemonId0, reply->str);
    freeReplyObject(reply);

    reply = redisCommand(redisConnection, "get battle_pokemon_%s:%s", battleSessionKey, username1);
    strcpy(pokemonId1, reply->str);
    freeReplyObject(reply);

    // ////////////////////////////////////////////////////
    // Get the info about the two pokemons from mongo //
    // ////////////////////////////////////////////////////

    pokemon pokemon0, pokemon1;

    fetchPokemonData(&pokemon0, pokemonId0, mongoConnection);
    fetchPokemonData(&pokemon1, pokemonId1, mongoConnection);

    // //////////////////////////////////////////
    // Get health of defendent pokemons from redis //
    // //////////////////////////////////////////

    int health;

    reply  = redisCommand(redisConnection, "get battle_pokemon_health_%s:%s", battleSessionKey, username1);
    health = atoi(reply->str);
    freeReplyObject(reply);

    // /////////////////
    // Get move info //
    // /////////////////

    move m;
    fetchMoveData(&m, move_str, mongoConnection);

    // /////////////////////
    // Calculate damaage //
    // /////////////////////

    float damage;
    int damage_int;
    int random;
    float random_flt;

    damage = (((2 * pokemon0.level / 5) + 2) * m.bp);

    if (strcmp(m.type, "normal") == 0) {
        damage *= pokemon0.attack;
        damage /= pokemon1.defense;
    } else {
        damage *= pokemon0.spAttack;
        damage /= pokemon1.spDefense;
    }

    damage /= 50;
    damage += 2;

    random      = rand();
    random     %= 15;
    random_flt /= 100;
    random_flt += 0.85;

    damage *= random_flt;

    if (strcmp(m.type, pokemon0.type0) == 0 || strcmp(m.type, pokemon0.type1) == 0) {
        damage *= 1.5;
    }

    if (strcmp("defense", pokemon1.type0) == 0 || strcmp("defense", pokemon1.type1) == 0) {
        damage *= pokemon0.defense;
    }
    if (strcmp("poison", pokemon1.type0) == 0 || strcmp("poison", pokemon1.type1) == 0) {
        damage *= pokemon0.poison;
    }
    if (strcmp("speed", pokemon1.type0) == 0 || strcmp("speed", pokemon1.type1) == 0) {
        damage *= pokemon0.speed;
    }
    if (strcmp("ground", pokemon1.type0) == 0 || strcmp("ground", pokemon1.type1) == 0) {
        damage *= pokemon0.ground;
    }
    if (strcmp("spDefense", pokemon1.type0) == 0 || strcmp("spDefense", pokemon1.type1) == 0) {
        damage *= pokemon0.spDefense;
    }
    if (strcmp("psychic", pokemon1.type0) == 0 || strcmp("psychic", pokemon1.type1) == 0) {
        damage *= pokemon0.psychic;
    }
    if (strcmp("flying", pokemon1.type0) == 0 || strcmp("flying", pokemon1.type1) == 0) {
        damage *= pokemon0.flying;
    }
    if (strcmp("ice", pokemon1.type0) == 0 || strcmp("ice", pokemon1.type1) == 0) {
        damage *= pokemon0.ice;
    }
    if (strcmp("fight", pokemon1.type0) == 0 || strcmp("fight", pokemon1.type1) == 0) {
        damage *= pokemon0.fight;
    }
    if (strcmp("attack", pokemon1.type0) == 0 || strcmp("attack", pokemon1.type1) == 0) {
        damage *= pokemon0.attack;
    }
    if (strcmp("steel", pokemon1.type0) == 0 || strcmp("steel", pokemon1.type1) == 0) {
        damage *= pokemon0.steel;
    }
    if (strcmp("electric", pokemon1.type0) == 0 || strcmp("electric", pokemon1.type1) == 0) {
        damage *= pokemon0.electric;
    }
    if (strcmp("normal", pokemon1.type0) == 0 || strcmp("normal", pokemon1.type1) == 0) {
        damage *= pokemon0.normal;
    }
    if (strcmp("fire", pokemon1.type0) == 0 || strcmp("fire", pokemon1.type1) == 0) {
        damage *= pokemon0.fire;
    }
    if (strcmp("spAttack", pokemon1.type0) == 0 || strcmp("spAttack", pokemon1.type1) == 0) {
        damage *= pokemon0.spAttack;
    }
    if (strcmp("hp", pokemon1.type0) == 0 || strcmp("hp", pokemon1.type1) == 0) {
        damage *= pokemon0.hp;
    }
    if (strcmp("dark", pokemon1.type0) == 0 || strcmp("dark", pokemon1.type1) == 0) {
        damage *= pokemon0.dark;
    }
    if (strcmp("bug", pokemon1.type0) == 0 || strcmp("bug", pokemon1.type1) == 0) {
        damage *= pokemon0.bug;
    }
    if (strcmp("ghost", pokemon1.type0) == 0 || strcmp("ghost", pokemon1.type1) == 0) {
        damage *= pokemon0.ghost;
    }
    if (strcmp("water", pokemon1.type0) == 0 || strcmp("water", pokemon1.type1) == 0) {
        damage *= pokemon0.water;
    }
    if (strcmp("grass", pokemon1.type0) == 0 || strcmp("grass", pokemon1.type1) == 0) {
        damage *= pokemon0.grass;
    }
    if (strcmp("capturerate", pokemon1.type0) == 0 || strcmp("capturerate", pokemon1.type1) == 0) {
        damage *= pokemon0.capturerate;
    }
    if (strcmp("dragon", pokemon1.type0) == 0 || strcmp("dragon", pokemon1.type1) == 0) {
        damage *= pokemon0.dragon;
    }
    if (strcmp("rock", pokemon1.type0) == 0 || strcmp("rock", pokemon1.type1) == 0) {
        damage *= pokemon0.rock;
    }

    damage_int = (int) damage;

    // /////////////////////////////////////////
    // Update the health of attacked pokemon //
    // /////////////////////////////////////////
    redisCommand(redisConnection, "set battle_pokemon_health_%s:%s %d", battleSessionKey, username1,
      health - damage_int);

    // ///////////////
    // Update turn //
    // ///////////////
    redisCommand(redisConnection, "set battle_turn:%s %s", battleSessionKey, username1);

    // //////////////////
    // Set outBuffer  //
    // //////////////////

    // (ongoing/over) (username of acting player) (new health of other player)
    if (health - damage_int > 0) {
        strcpy(outBuffer, "ongoing");
    } else {
        strcpy(outBuffer, "over");
    }
    char tempBuffer[20];

    strcat(outBuffer, " ");
    strcat(outBuffer, username0);
    strcat(outBuffer, " ");
    sprintf(tempBuffer, "%d ", health - damage_int);
    strcat(outBuffer, tempBuffer);

    // /////////////////////
    // /////////////////////
    // If battle is over //
    // /////////////////////
    // /////////////////////

    if (health - damage_int > 0) {
        return;
    }

    // /////////////////////////////////////////
    // Update the expirance value of pokemon //
    // ///////////////////////////////////////
    int new_xp,
      new_level = pokemon0.level;

    double xp_gain = 1;

    if (startsWith("__npc__", username1) == 0) {
        xp_gain *= 1.5;
    }

    xp_gain *= pokemon0.expgrowth;
    xp_gain *= pokemon0.level;
    xp_gain *= pokemon1.level;

    xp_gain /= 7;

    new_xp = pokemon0.xp + (int) xp_gain;

    if (new_xp >= (5 * power(pokemon0.level + 1, 3) / 4)) {
        new_level++;
    }

    sprintf(tempBuffer, "%d ", new_xp);
    strcat(outBuffer, tempBuffer);
    sprintf(tempBuffer, "%d ", new_level);
    strcat(outBuffer, tempBuffer);


    // Update pokeomn info in mongo
    updatePokemonInfo(pokemonId0, new_xp, new_level, mongoConnection);

    // ///////////////////////////////////
    // Fetch and udpate user stats     //
    // ///////////////////////////////////

    user u;
    fetchUserData(&u, username0, mongoConnection);

    new_xp    = u.xp + 10;
    new_level = u.level;

    if (new_xp >= (50 * (u.level + 1))) {
        new_level++;
    }

    updateUserInfo(username0, new_xp, new_level, mongoConnection);

    // ///////////////////////////////////////////////////////////
    // If the loosing pokemon was wild add it to users profile //
    // ///////////////////////////////////////////////////////////
    addPokemon(username0, pokemon1.id, pokemon1.level, pokemon1.xp, mongoConnection);
} /* battleStep */
