#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./login.h"

// Performs login
int login(){
    int clientSocket;
    char inBuffer[1024], outBuffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char name[20], username[20], password[20], preference[20];
    //set option y if user wants to register
    char option = 'n';

    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(9090);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;
    if (connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) < 0){
        printf("Error in connecting to the server.\n");
        return 0;
    }

    /*---- Get username and password ----*/
    printf("Welcome to PNP\n");

    printf("Are you already registered on pnp? (y/n)\n");
    scanf("%c",&option);

    if (option == 'n')
    {
        strcpy(preference, "signup");
    }
    else if (option == 'y')
    {
        strcpy(preference, "login");
    }

    printf("Enter your name:");
    scanf("%s", name);
    printf("Enter username:");
    scanf("%s", username);
    printf("Enter password:");
    scanf("%s", password);

    // Send username and password
    strcpy(outBuffer, preference);
    strcat(outBuffer, " ");
    strcat(outBuffer, name);
    strcat(outBuffer, " ");
    strcat(outBuffer, username);
    strcat(outBuffer, " ");
    strcat(outBuffer, password);

    printf("Sending data: %s\n", outBuffer);

    // While making gui keep ensure that all the feilds are non-empty else
    // server will break
    send(clientSocket, outBuffer, 1024, 0);

    /*---- Read the message from the server into the buffer ----*/
    recv(clientSocket, inBuffer, 1024, 0);

    printf("%s\n", inBuffer);

    return 0;
}
