#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./login_server.h"
#include "limits.h"

// Assigns a session-key to user i.e makes corrosponing entry in redis
// and returns the value of key (Note: It does not send the key to user)

char* assignGameServer(char * username, redisContext * redisConnection){
    int i, minIndex, min = MAX_INT;
    redisReply *servers, keys;

    servers = redisCommand(redisConnection, "lrange servers 0 -1");

    for (i = 0; i < servers->elements; i++) {
        keys = redisCommand(redisConnection, "keys %d*", servers->element[j]->str);

        if (keys->type == REDIS_REPLY_ARRAY) {
            if (min >= keys->elements){
                min = keys->elements;
                minIndex = i;
            }
        }
    }

    // Set the server record with expiry
    redisCommand(redisConnection,"set servers:%s:%s 1 ex 5000", servers->element[minIndex]->str, username);
}
