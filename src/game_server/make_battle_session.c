#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

/**
 * [makeBattleSession creates unique battle session key when both the users are ready]
 * @param  battleSessioKey   [if successful returns a unique string which represents the game session]
 * @param  username_0      [the player who sends ready signal]
 * @param  username_1      [the oponent]
 * @param  pokemonId       [the pokemonId of pokemon user0 has chossen]
 * @param  redisConnection [redis context]
 * @return                 [success value]
 */
void
makeBattleSession(char * outBuffer, char * username0, char * username1, char * pokemonId,
  int count, MongoConnection mongoConnection, redisContext * redisConnection)
{
    redisReply * reply;
    char gameSessionKey[16];
    char temp[50];

    printf("waiting outside\n");
    // check if the other guy is already ready
    reply = redisCommand(redisConnection, "get ready_for_battle:%s", username1);

    if (reply->type == REDIS_REPLY_NIL) {
        printf("waiting\n");
        // Set a flag that tells user is ready with expiry of 20 seconds
        // Set the pokemonId as value
        redisCommand(redisConnection, "set ready_for_battle:%s %s ex 2", username0, pokemonId);
        sleep(1);
        if (count++ < 20) {
            makeBattleSession(outBuffer, username0, username1, pokemonId, count, mongoConnection, redisConnection);
        } else {
            strcpy(outBuffer, "lite");
        }
    } else {
        redisCommand(redisConnection, "set ready_for_battle:%s %s ex 3", username0, pokemonId);

        strcpy(outBuffer, "start ");

        random_string(gameSessionKey, 16);
        strcat(outBuffer, gameSessionKey);
        strcat(outBuffer, " ");

        user u;
        pokemon p;

        fetchUserData(&u, username0, mongoConnection);
        sprintf(temp, "%s %s %d %d ", username0, u.name, u.xp, u.level);
        strcat(outBuffer, temp);


        fetchPokemonData(&p, pokemonId, mongoConnection);
        sprintf(temp, "%s %d %d ", p.name, p.xp, p.level);
        strcat(outBuffer, temp);


        fetchUserData(&u, username1, mongoConnection);
        sprintf(temp, "%s %s %d %d ", username1, u.name, u.xp, u.level);
        strcat(outBuffer, temp);


        fetchPokemonData(&p, reply->str, mongoConnection);
        sprintf(temp, "%s %d %d ", p.name, p.xp, p.level);
        strcat(outBuffer, temp);

        // Set the ids of battling pokemons
        redisCommand(redisConnection, "set battle_pokemon_%s:%s %s", gameSessionKey, username0, pokemonId);
        redisCommand(redisConnection, "set battle_pokemon_%s:%s %s", gameSessionKey, username1, reply->str);

        // Set the health of both pokemons at 100%
        redisCommand(redisConnection, "set battle_pokemon_health_%s:%s 100", gameSessionKey, username0);
        redisCommand(redisConnection, "set battle_pokemon_health_%s:%s 100", gameSessionKey, username1);

        // As user1 has sent request first we will give him the chance
        redisCommand(redisConnection, "set battle_turn:%s %s", gameSessionKey, username1);
    }

    freeReplyObject(reply);
} /* makeBattleSession */
