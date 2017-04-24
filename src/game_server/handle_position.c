#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

// Store the position of user and returns position of nearby users
void
handlePositionRequest(char * outBuffer, char * username, char * position, long int timestamp,
  redisContext * redisConnection)
{
    redisReply * r;

    long int last_timestamp;
    char ** positions;

    char usersX[100][100];
    char usersY[100][100];
    char users[100][100];

    int x, y;
    int userCountX, userCountY, userCount = 0;

    char temp[200];
    int i, j;

    // /////////////////////
    // Compare timestamp //
    // /////////////////////

    r = redisCommand(redisConnection, "get pos_timestamp:%s", username);
    if (r->type == REDIS_REPLY_STRING) {
        last_timestamp = atol(r->str);
        printf("%ld\n", last_timestamp);
        if (timestamp < last_timestamp)
            strcat(outBuffer, "error");
    } // Else: The position of user has not been set ever

    freeReplyObject(r);

    // ////////////////////////
    // Set position of user //
    // ////////////////////////

    // First we need to split it up the position
    positions = strSplit(position, ':');
    x         = atoi(positions[0]);
    y         = atoi(positions[1]);

    // Set sorted sets
    redisCommand(redisConnection, "zadd x %d %s", x, username);
    redisCommand(redisConnection, "zadd y %d %s", y, username);

    // Set key value pair (becaus i can not figure out how hiredis handles zrangescore with scores :p)
    redisCommand(redisConnection, "set position_x:%s %d", username, x);
    redisCommand(redisConnection, "set position_y:%s %d", username, y);

    // /////////////////////////////////////////////////
    // Get positions of users in range x+-480 y+-360 //
    // /////////////////////////////////////////////////

    // X ranage

    r = redisCommand(redisConnection, "zrangebyscore x %d %d", x - 480, x + 480);

    if (r->type == REDIS_REPLY_ARRAY) {
        userCountX = r->elements;
        for (i = 0; i < r->elements; ++i) {
            redisReply * childReply = r->element[i];
            // Before has been introduced, the get command returns the data type string.
            // For there is no return value key, the type REDIS_REPLY_NIL.
            if (childReply->type == REDIS_REPLY_STRING)
                strcpy(usersX[i], childReply->str);
        }
    }

    freeReplyObject(r);

    // Y range

    r = redisCommand(redisConnection, "zrangebyscore y %d %d", y - 360, y + 360);

    if (r->type == REDIS_REPLY_ARRAY) {
        userCountY = r->elements;
        for (i = 0; i < r->elements; ++i) {
            redisReply * childReply = r->element[i];
            // Before has been introduced, the get command returns the data type string.
            // For there is no return value key, the type REDIS_REPLY_NIL.
            if (childReply->type == REDIS_REPLY_STRING)
                strcpy(usersY[i], childReply->str);
        }
    }

    freeReplyObject(r);

    // Take union the hard way :p
    for (i = 0; i < userCountX; i++) {
        for (j = 0; j < userCountY; j++) {
            if (strcmp(usersX[i], usersY[j]) == 0) {
                strcat(users[userCount], usersX[i]);
                userCount++;
            }
        }
    }

    // Append the usercount to buffer
    sprintf(temp, "%d ", userCount - 1);
    strcat(outBuffer, temp);

    // Get position of each user
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i], username) != 0) {
            strcat(outBuffer, users[i]);
            strcat(outBuffer, " ");
            r = redisCommand(redisConnection, "get position_x:%s", users[i]);
            strcat(outBuffer, r->str);
            strcat(outBuffer, ":");
            freeReplyObject(r);
            r = redisCommand(redisConnection, "get position_y:%s", users[i]);
            strcat(outBuffer, r->str);
            strcat(outBuffer, " ");
            freeReplyObject(r);
        }
    }

    printf("%s\n", outBuffer);

    // Set new timestamp
    redisCommand(redisConnection, "set pos_timestamp:%s %lf", username, timestamp);
} /* storePosition */
