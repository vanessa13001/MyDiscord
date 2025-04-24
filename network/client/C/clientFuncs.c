#include "../H/clientFuncs.h"


int connectToServer(SOCKET clientSocket, struct sockaddr_in* serverAddress){
    if (connect(clientSocket, (struct sockaddr*)serverAddress, sizeof(*serverAddress))==SOCKET_ERROR){
        printf("unable to connect, error: %d", WSAGetLastError());
        return 1;
    }
    printf("connected to server successfully \n");
    return 0;
}