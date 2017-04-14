#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./login_server.h"
#include "limits.h"

// Assigns a session-key to user i.e makes corrosponing entry in redis
// and returns the value of key (Note: It does not send the key to user)

char* assignGameServer(char * gameServerAddr, char * username, redisContext * redisConnection){
    int i, minIndex, min = INT_MAX;
    redisReply * servers;
    redisReply * keys;

    servers = redisCommand(redisConnection, "lrange servers 0 -1");

    for (i = 0; i < servers->elements; i++) {
        keys = redisCommand(redisConnection, "keys %d*", servers->element[i]->str);

        if (keys->type == REDIS_REPLY_ARRAY) {
            if (min >= keys->elements){
                min = keys->elements;
                minIndex = i;
            }
        }
    }

    // Assignn the string
    strcpy(gameServerAddr, servers->element[minIndex]->str);

    // Set the session key corrosponing to the user
    redisCommand(redisConnection,"set servers:%s:%s 1 ex 5000", servers->element[minIndex]->str, username);
}
