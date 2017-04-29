#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./login_server.h"
#include "../game_server/game_server.h"

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
    serverAddr.sin_port = htons(10000);
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

    // //////////////////////////////////////////////////////////////////////////
    // //////////////////////////////////////////////////////////////////////////
    //                           Action Loop
    // //////////////////////////////////////////////////////////////////////////
    // //////////////////////////////////////////////////////////////////////////

    char ** userDetails;
    int insertResult;
    int identityVerified;
    char sessionKey[16];
    char gameServerAddr[30];
    char inBuffer[1024], outBuffer[1024];

    while (!listen(welcomeSocket, 100)) {
        if ((newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size)) < 0) {
            printf("Error in accepting connection!\n");
            exit(1);
        }

        /*---- Recieve username and password ----*/

        recv(newSocket, inBuffer, 1024, 0);

        printf("%s\n", inBuffer);

        userDetails = strSplit(inBuffer, ' ');

        if (strcmp(userDetails[0], "signup") == 0) {
            // Type, name, username, password
            insertResult = signup(userDetails[1], userDetails[2], userDetails[3], mongoConnection);

            /*---- Send appropriate message ----*/
            if (insertResult == 0) {
                strcpy(outBuffer, "success");
            } else if (insertResult == -1) {
                strcpy(outBuffer, "error");
            } else {
                strcpy(outBuffer, "duplicate");
            }

            // username, pokedexId, level, xp
            // Some weired stuff to randomly select betweeen the three base pokemons
            addPokemon(userDetails[2], (((rand() % 3) * 3) + 1), 1, 15, mongoConnection);

            send(newSocket, outBuffer, 1024, 0);

            close(newSocket);
        } else if (strcmp(userDetails[0], "login") == 0) {
            // Type, name, username, password
            identityVerified = login(userDetails[2], userDetails[3], mongoConnection);
            /*---- Send appropriate message ----*/
            if (identityVerified == 0) {
                assignGameServer(gameServerAddr, userDetails[2], *redisConnection);
                assignSessionKey(sessionKey, userDetails[2], *redisConnection);
                strcpy(outBuffer, "success");
                strcat(outBuffer, " ");
                strcat(outBuffer, sessionKey);
                strcat(outBuffer, " ");
                strcat(outBuffer, gameServerAddr);
            } else if (identityVerified == -1) {
                strcpy(outBuffer, "error");
            }

            send(newSocket, outBuffer, 1024, 0);

            close(newSocket);
        } else if (strcmp(userDetails[0], "signout") == 0) {
            // Type, name, username, password
            /*---- Send appropriate message ----*/
            signout(userDetails[1], *redisConnection);

            close(newSocket);
        }
    }
} /* tcpServer */
