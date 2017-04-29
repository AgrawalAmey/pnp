#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

void
tcpServer(MongoConnection mongoConnection, redisContext ** redisConnection)
{
    // //////////////////////////////////////////////////////////////////////////
    // //////////////////////////////////////////////////////////////////////////
    //                           Init socket
    // //////////////////////////////////////////////////////////////////////////
    // //////////////////////////////////////////////////////////////////////////

    int welcomeSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    int enable;

    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*make the port reusable*/
    if (setsockopt(welcomeSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        printf("setsockopt: There was an error in hosting the server.\n");
        exit(1);
    }

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(11000);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));


    /*---- Bind the address struct to the socket ----*/
    if (bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1) {
        printf("bind: There was an error in hosting the server.\n");
        exit(1);
    }

    /*---- Listen on the socket, with 100 max connection requests queued ----*/
    if (listen(welcomeSocket, 100) == 0)
        printf("Listening\n");
    else
        printf("Error\n");

    /*---- Accept call creates a new socket for the incoming connection ----*/

    addr_size = sizeof(serverStorage);

    printf("TCP server Initialized\n");

    // //////////////////////////////////////////////////////////////////////////
    // //////////////////////////////////////////////////////////////////////////
    //                           Action Loop
    // //////////////////////////////////////////////////////////////////////////
    // //////////////////////////////////////////////////////////////////////////

    char inBuffer[1024], outBuffer[1024];
    char ** reqTokens;
    int insertResult;
    int identityVerified;
    char sessionKey[16];
    int sessionValid;

    while (!listen(welcomeSocket, 100)) {
        if ((newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size)) < 0) {
            printf("Error in accepting connection!\n");
            exit(1);
        }
        // Fork out to handle concurrent requests
        if (fork() == 0) {
            /*---- Recieve username and password ----*/

            recv(newSocket, inBuffer, 1024, 0);

            printf("%s\n", inBuffer);

            reqTokens = strSplit(inBuffer, ' ');

            sessionValid = validateSession(reqTokens[1], reqTokens[2], *redisConnection);

            if (sessionValid == 1) {
                if (strcmp(reqTokens[0], "list_pokemons") == 0) {
                    fetchPokemonList(outBuffer, reqTokens[1], mongoConnection);
                } else if (strcmp(reqTokens[0], "battle_start") == 0) {
                    makeBattleSession(outBuffer, reqTokens[1], reqTokens[3], reqTokens[4], 0, mongoConnection,
                      *redisConnection);
                } else if (strcmp(reqTokens[0], "battle_make_move")) {
                    battleStep(outBuffer, reqTokens[1], reqTokens[4], reqTokens[5], reqTokens[3], redisConnection,
                      mongoConnection);
                } else {
                    strcpy(outBuffer, "error");
                }
            } else {
                strcpy(outBuffer, "error");
            }


            printf("Sending : %s\n", outBuffer);
            send(newSocket, outBuffer, 1024, 0);

            close(newSocket);
        }
    }
} /* tcpServer */
