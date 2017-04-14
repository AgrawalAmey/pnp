#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./login_server.h"

// Assigns a session-key to user i.e makes corrosponing entry in redis
// and returns the value of key (Note: It does not send the key to user)

char* assignSessionKey(char * sessionKey, char * username, redisContext * redisConnection){
    // Get random string
    random_string(sessionKey, 16);

    // Set the session key corrosponing to the user with expiry of 5000 seconds
    redisCommand(redisConnection,"set sessions:%s %s ex 5000", username, sessionKey);

}
