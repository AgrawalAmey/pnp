#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./login_server.h"


int main(){
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        //                           Init databse connections
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////

        // Mongo
        MongoConnection mongoConnection;
        connectToMongo(&mongoConnection);

        // Redis
        redisContext ** redisConnection;
        redisConnection = (redisContext **)malloc(sizeof(redisContext *));
        connectToRedis(redisConnection);

        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        //                           Init Server Child
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////

        // Fork out tcp server
        if(fork() == 0) {
                tcpServer(mongoConnection, redisConnection);
        }

        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        //                           Wait Loop
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////

        pid_t wpid;
        int status = 0;

        while ((wpid = wait(&status)) > 0) ;

        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        //                          Distroy database connections
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////

        // Mongo
        endMongoConnection(&mongoConnection);

        // Redis
        endRedisConnection(*redisConnection);

        // Exit
        return 0;
}
