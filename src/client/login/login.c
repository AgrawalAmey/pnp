#include "./../../utils/includes.h"
#include "./../../utils/utils.h"
#include "./login.h"

// Performs login
void
login(char * inBuffer, char * preference, char * name, char * username, char * password)
{
    // printf("%s %s %s %s\n", preference, name, username, password);
    int clientSocket;
    char outBuffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(10000);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("172.17.48.130");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;
    if (connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) < 0) {
        printf("Error in connecting to the server.\n");
        exit(1);
    }

    // Send username and password
    strcpy(outBuffer, preference);
    strcat(outBuffer, " ");
    strcat(outBuffer, name);
    strcat(outBuffer, " ");
    strcat(outBuffer, username);
    strcat(outBuffer, " ");
    strcat(outBuffer, hash(password));

    printf("Sending data: %s\n", outBuffer);

    // While making gui keep ensure that all the feilds are non-empty else
    // server will break
    send(clientSocket, outBuffer, 1024, 0);

    /*---- Read the message from the server into the buffer ----*/
    recv(clientSocket, inBuffer, 1024, 0);
} /* login */
