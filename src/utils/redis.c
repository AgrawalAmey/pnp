#include "./includes.h"
#include "./utils.h"

// Setup redis connection
void connectToRedis(redisContext **c){
    const char *hostname = "127.0.0.1";
    int port = 6379;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds

    *c = redisConnectWithTimeout(hostname, port, timeout);
    if (*c == NULL || (**c).err) {
        if (*c) {
            printf("Connection error: %s\n", (**c).errstr);
            redisFree(*c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }
}

// End redis connection
void endRedisConnection(redisContext *c){
    /* Disconnects and frees the context */
    redisFree(c);
}
