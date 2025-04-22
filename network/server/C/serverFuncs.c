#include "../H/serverFuncs.h"


int bindServer(SOCKET serverSocket, struct sockaddr_in* address){

    if (bind(serverSocket, (struct sockaddr*)address, sizeof(*address))==SOCKET_ERROR){
        printf("bind failed, error: %d \n ",WSAGetLastError());
        closesocket(serverSocket);
        return 1;
    } else {
        printf("bind successful \n");
        return 0;
    }
}

int listenConnection(SOCKET serverSocket){
    if (listen(serverSocket, SOMAXCONN)==SOCKET_ERROR){
        printf("listen failed, error: %d", WSAGetLastError());
        closesocket(serverSocket);
        return 1;
    } else{
        printf("now listening... \n");
        return 0;
    }

}