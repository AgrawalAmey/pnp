#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

// Validate the session of user
int
validateSession(char * username, char * sessionKey, redisContext * redisConnection)
{
    redisReply * reply;

    reply = redisCommand(redisConnection, "get sessions:%s", username);

    if (reply->type == REDIS_REPLY_STRING) {
        if (strcmp(reply->str, sessionKey) == 0) {
            return 1;
        }
    }

    return 0;
}
