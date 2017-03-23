#include "../utils/includes.h"
#include "../utils/utils.h"
#include "./login_server.h"


int main(){

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //                           Init Mongo server
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    MongoConnection mongoConnection;

    connectToMongo(&mongoConnection);


    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //                           Init server
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    int welcomeSocket, newSocket;
    char inBuffer[1024], outBuffer[1024];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    char * sessionKey[25];
    char ** userDetails;
    int insertResult;


    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(9090);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    /*---- Bind the address struct to the socket ----*/
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    /*---- Listen on the socket, with 100 max connection requests queued ----*/
    if(listen(welcomeSocket, 100)==0)
        printf("Listening\n");
    else
        printf("Error\n");

    /*---- Accept call creates a new socket for the incoming connection ----*/

    addr_size = sizeof(serverStorage);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //                           Action Loop
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

    /*---- Recieve username and password ----*/

    recv(newSocket, inBuffer, 1024, 0);

    printf("%s\n", inBuffer);

    userDetails = strSplit(inBuffer, ' ');

    insertResult = signup(userDetails[0], userDetails[1], userDetails[2], mongoConnection);

    /*---- Send appropriate message ----*/
    if(insertResult == 0){
        strcpy(outBuffer, "Signed up succesfully!");
    } else if(insertResult == -1){
        strcpy(outBuffer, "Sorry! Something went wrong.");
    } else {
        strcpy(outBuffer, "Username already exists.");
    }

    send(newSocket, outBuffer, 1024, 0);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //                          Distroy mongo connection
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    endMongoConnection(&mongoConnection);
    return 0;
}
