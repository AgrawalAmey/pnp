#include "../utils/includes.h"
#include "../utils/utils.h"


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
    redisContext * redisConnection;
    connectToRedis(redisConnection);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //                           Init TCP server
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    // int welcomeSocket, newSocket;
    // char inBuffer[1024], outBuffer[1024];
    // struct sockaddr_in serverAddr;
    // struct sockaddr_storage serverStorage;
    // socklen_t addr_size;
    // int enable;
    //
    // /*---- Create the socket. The three arguments are: ----*/
    // /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    // welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
    //
    // /*make the port reusable*/
    // if (setsockopt(welcomeSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){
    //     printf("setsockopt: There was an error in hosting the server.\n");
    //     exit(1);
    // }
    //
    // /*---- Configure settings of the server address struct ----*/
    // /* Address family = Internet */
    // serverAddr.sin_family = AF_INET;
    // /* Set port number, using htons function to use proper byte order */
    // serverAddr.sin_port = htons(11000);
    // /* Set IP address to localhost */
    // serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    // /* Set all bits of the padding field to 0 */
    // memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
    //
    //
    // /*---- Bind the address struct to the socket ----*/
    // if (bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1){
    //     printf("bind: There was an error in hosting the server.\n");
    //     exit(1);
    // }
    //
    // /*---- Listen on the socket, with 100 max connection requests queued ----*/
    // if(listen(welcomeSocket, 100)==0)
    //     printf("Listening\n");
    // else
    //     printf("Error\n");
    //
    // /*---- Accept call creates a new socket for the incoming connection ----*/
    //
    // addr_size = sizeof(serverStorage);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //                           Init UDP server
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    int udpSocket;
    char buffer[1024];
    struct sockaddr_in udpServerAddr, udpClientAddr;
    struct sockaddr_storage udpServerStorage;
    socklen_t udp_addr_size, udp_client_addr_size;

    /*Create UDP socket*/
    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

    /*Configure settings in address struct*/
    udpServerAddr.sin_family = AF_INET;
    udpServerAddr.sin_port = htons(7891);
    udpServerAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    memset(udpServerAddr.sin_zero, '\0', sizeof udpServerAddr.sin_zero);

    /*Bind socket with address struct*/
    bind(udpSocket, (struct sockaddr *) &udpServerAddr, sizeof(udpServerAddr));

    /*Initialize size variable to be used later on*/
    udp_addr_size = sizeof udpServerStorage;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //                           Action Loop
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    char ** userDetails;
    int insertResult;
    int identityVerified;
    char sessionKey[16];

    while(! listen(welcomeSocket, 100))
    {
        if((newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size)) < 0){
            printf("Error in accepting connection!\n");
            exit(1);
        }

        /*---- Recieve username and password ----*/

        recv(newSocket, inBuffer, 1024, 0);

        printf("%s\n", inBuffer);

        userDetails = strSplit(inBuffer, ' ');

        if (strcmp(userDetails[0], "signup") == 0)
        {
            insertResult = signup(userDetails[1], userDetails[2], userDetails[3], mongoConnection);

            /*---- Send appropriate message ----*/
            if(insertResult == 0){
                strcpy(outBuffer, "Signed up succesfully!");
            } else if(insertResult == -1){
                strcpy(outBuffer, "Sorry! Something went wrong.");
            } else {
                strcpy(outBuffer, "Username already exists.");
            }


            send(newSocket, outBuffer, 1024, 0);

            close(newSocket);
        }
        else if (strcmp(userDetails[0], "login") == 0)
        {
            identityVerified = login(userDetails[2], userDetails[3],mongoConnection);

            /*---- Send appropriate message ----*/
            if (identityVerified == 0){
                strcpy(outBuffer, "Logged in succesfully!");
            }
            else if(identityVerified == -1){
                strcpy(outBuffer, "Username and/or password Incorrect. Please try again!");
            }

            send(newSocket, outBuffer, 1024, 0);

            close(newSocket);
        }

    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //                          Distroy database connections
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    // Mongo
    endMongoConnection(&mongoConnection);

    // Redis
    endRedisConnection(redisConnection);

    // Exit
    return 0;
}
