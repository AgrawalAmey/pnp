#include "./../GUIUtils/includeGUI.h"
#include "./udpGameClient.h"
#include "../../utils/includes.h"
#include "../../utils/utils.h"

void
udpGameClient(struct hashTable * hashtable, char * sessionKey, char * serverStr, char * username)
{
    int clientSocket, portNum;
    char ** gameServerAddress;

    gameServerAddress = strSplit(serverStr, ':');
    portNum = atoi(gameServerAddress[1]);


    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    /*Create UDP socket*/
    clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

    /*Configure settings in address struct*/
    serverAddr.sin_family      = AF_INET;
    serverAddr.sin_port        = htons(portNum);
    serverAddr.sin_addr.s_addr = inet_addr(gameServerAddress[0]);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /*Initialize size variable to be used later on*/
    addr_size = sizeof serverAddr;


    while (1) {
        char outBuffer[1024] = { '\0' };
        char inBuffer[1024]  = { '\0' };
        char tempbuf[10]     = { '\0' };

        strcat(outBuffer, "position");
        strcat(outBuffer, " ");
        strcat(outBuffer, username);
        strcat(outBuffer, " ");
        strcat(outBuffer, sessionKey);
        strcat(outBuffer, " ");
        sprintf(tempbuf, "%ld", time(NULL));
        strcat(outBuffer, tempbuf);
        strcat(outBuffer, " ");
        sprintf(tempbuf, "%d", hashtable->myX);
        strcat(outBuffer, tempbuf);
        strcat(outBuffer, ":");
        sprintf(tempbuf, "%d", hashtable->myY);
        strcat(outBuffer, tempbuf);

        int nBytes = strlen(outBuffer) + 1;

        printf("Sending : %s\n", outBuffer);

        sendto(clientSocket, outBuffer, nBytes, 0, (struct sockaddr *) &serverAddr, addr_size);

        nBytes = recvfrom(clientSocket, inBuffer, 1024, 0, NULL, NULL);

        printf("Receiveed : %s\n", inBuffer);

        populateSHM(hashtable, inBuffer);

<<<<<<< HEAD
        // usleep(40000);
        usleep(1000000);
    }
} /* udpGameClient */
=======
		// usleep(40000);
		usleep(500000);
	}

}
>>>>>>> c3d3cad19cb62e78cfc7a0ab97dcf2586ef6d1da
