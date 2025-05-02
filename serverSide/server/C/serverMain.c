#include "../H/serverFuncs.h"

int main(){
    if (!initWinsock()){
        return 1;
    }

    SOCKET serverSocket= createSocket();

    if (serverSocket== INVALID_SOCKET){
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serverAddress = createAddress("127.0.0.1", 8081);


    if (bindServer(serverSocket, &serverAddress)==1){
        WSACleanup();
        return 1;
    }

    if (listenConnection(serverSocket)==1){
        WSACleanup();
        return 1;
    }
    printf("waiting for client connection \n");



    while(1){
    SOCKET clientSocket = accept(serverSocket,NULL, NULL);
    if (clientSocket==INVALID_SOCKET){
        printf("connection failed, error: %d", WSAGetLastError());

        continue;
    }

    printf("client connected! \n");

    SOCKET* clientPtr= malloc(sizeof(SOCKET));
    if (clientPtr==NULL){
        printf("failed to allocate memory for client socket \n");
        closesocket(clientSocket);
        continue;
    }
    *clientPtr=clientSocket;

    HANDLE threadHandle= newThread(clientPtr, clientThread);
    if (threadHandle!=NULL){
        CloseHandle(threadHandle);
    }



    }
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}