#include "../utils/includes.h"
#include "./login_server.h"

// Validate user from mongodb
void
signout(char * username, redisContext * redisConnection)
{
    redisCommand(redisConnection, "del sessions:%s", username);
    redisCommand(redisConnection, "zrem x %s", x, username);
    redisCommand(redisConnection, "zrem y %s", y, username);
    redisCommand(redisConnection, "set position_x:%s", username, x);
    redisCommand(redisConnection, "set position_y:%s", username, y);
}
