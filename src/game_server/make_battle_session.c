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
int
makeBattleSession(char * outBuffer, char * username0, char * username1, char * pokemonId,
  redisContext * redisConnection)
{
    redisReply * reply;
    char gameSessionKey[16];

    // check if the other guy is already ready
    reply = redisCommand(redisConnection, "get ready_for_battle:%s", username1);

    if (reply->type == REDIS_REPLY_NIL) {
        // Set a flag that tells user is ready with expiry of 20 seconds
        // Set the pokemonId as value
        redisCommand(redisConnection, "set read_for_battle:%s %s ex 20", username0, pokemonId);

        strcpy(outBuffer, "wait");

        freeReplyObject(reply);
        return 0;
    } else {
        strcpy(outBuffer, "start");
        random_string(gameSessionKey, 16);
        strcat(outBuffer, gameSessionKey);

        // Set the ids of battling pokemons
        redisCommand(redisConnection, "set battle_pokemon_%s:%s %s", battleSessioKey, username0, pokemonId);
        redisCommand(redisConnection, "set battle_pokemon_%s:%s %s", battleSessioKey, username1, reply->str);

        // Set the health of both pokemons at 100%
        redisCommand(redisConnection, "set battle_pokemon_health_%s:%s 100", battleSessioKey, username0);
        redisCommand(redisConnection, "set battle_pokemon_health_%s:%s 100", battleSessioKey, username1);

        // As user1 has sent request first we will give him the chance
        redisCommand(redisConnection, "set battle_turn:%s %s", battleSessioKey, username1);

        freeReplyObject(reply);
        return 1;
    }
} /* makeBattleSession */
