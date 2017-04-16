#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

// Store the position of user
int storePosition(char * username, char * position, redisContext * redisConnection){
        // Compare timestamp
        int freshPacket;
        redisReply *reply;

        reply = redisCommand(redisConnection, "get pos_timestamp:%d", username);

        if(reply->type == REDIS_REPLY_STRING) {
                if(strcmp(reply->str, sessionKey) == 0) {
                        freshPacket = 1;
                }
                freshPacket = 0;
        } else {
                // The position of user has not been set ever
                freshPacket = 1;
        }

        redisCommand(redisConnection, "set pos_timestamp:%s %s", username, position);
}
