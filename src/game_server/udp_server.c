#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./game_server.h"

void udpServer(MongoConnection mongoConnection, redisContext ** redisConnection){
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        //                           Init socket
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        int udpSocket;
        struct sockaddr_in ServerAddr, ClientAddr;
        struct sockaddr_storage serverStorage;
        socklen_t addr_size;

        /*Create UDP socket*/
        udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

        /*Configure settings in address struct*/
        ServerAddr.sin_family = AF_INET;
        ServerAddr.sin_port = htons(11000);
        ServerAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
        memset(ServerAddr.sin_zero, '\0', sizeof ServerAddr.sin_zero);

        /*Bind socket with address struct*/
        bind(udpSocket, (struct sockaddr *) &ServerAddr, sizeof(ServerAddr));

        /*Initialize size variable to be used later on*/
        addr_size = sizeof serverStorage;

        printf("UDP server Initialized\n");


        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////
        //                             Action Loop
        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////

        char inBuffer[1024], outBuffer[1024];
        char ** reqTokens;
        int nBytes, sessionValid;
        int i;

        while(1) {
                /* Try to receive any incoming UDP datagram. Address and port of
                   requesting client will be stored on serverStorage variable */
                nBytes = recvfrom(udpSocket, inBuffer, 1024, 0, (struct sockaddr *)&serverStorage, &addr_size);
                // Fork out to handle concurrent requests
                if(fork() == 0) {
                        reqTokens = strSplit(inBuffer, ' ');

                        sessionValid = validateSession(reqTokens[1], reqTokens[2], *redisConnection);

                        if(sessionValid == 1) {

                        } else {
                                strcpy(outBuffer, "error");
                        }

                        /*Convert message received to uppercase*/
                        for(i=0; i<nBytes-1; i++)
                                inBuffer[i] = toupper(inBuffer[i]);

                        /*Send uppercase message back to client, using serverStorage as the address*/
                        int j = 0;
                        for (j = 0; j < 1000; j++) {
                                char data[6];
                                sprintf(data, "yo%d\n", j);
                                sendto(udpSocket, data, 6, 0, (struct sockaddr *)&serverStorage, addr_size);
                                // usleep(25000);
                        }

                        sendto(udpSocket, inBuffer, nBytes, 0, (struct sockaddr *)&serverStorage, addr_size);

                        return;
                }

        }
}
