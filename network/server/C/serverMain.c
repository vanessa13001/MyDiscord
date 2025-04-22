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

    struct sockaddr_in serverAddress = createAddress("127.0.0.1", 8080);



    if (bindServer(serverSocket, &serverAddress)==1){
        WSACleanup();
        return 1;
    }

    if (listenConnection(serverSocket)==1){
        WSACleanup();
        return 1;
    }
    printf("waiting for client connection \n");

    SOCKET clientSocket = accept(serverSocket,NULL, NULL);
    if (clientSocket==INVALID_SOCKET){
        printf("connection failed, error: %d", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("client connected! \n");

    char buffer[512];

    int bytesReceived= recv(clientSocket, buffer, sizeof(buffer)-1, 0);
    if (bytesReceived>0){
        buffer[bytesReceived]='\0';
        printf("message from client: %s \n",buffer);
    }else {
        printf("no message or connection lost \n");
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}