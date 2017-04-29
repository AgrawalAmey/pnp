#include "../utils/includes.h"
#include "./login_server.h"

// Validate user from mongodb
void
signout(char * username, redisContext * redisConnection)
{
    redisCommand(redisConnection, "del sessions:%s", username);
    redisCommand(redisConnection, "zrem x %s", username);
    redisCommand(redisConnection, "zrem y %s", username);
    redisCommand(redisConnection, "del position_x:%s", username);
    redisCommand(redisConnection, "del position_y:%s", username);
}
