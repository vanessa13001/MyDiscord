#include "../H/clientFuncs.h"

int main(){

    if (!initWinsock()){
        return 1;
    }

    SOCKET clientSocket= createSocket();
    if (clientSocket== INVALID_SOCKET){
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serverAddress= createAddress("127.0.0.1", 8081);

    if (connectToServer(clientSocket,&serverAddress)==1){
        printf(" Connection failed, terminate session \n", WSAGetLastError());
        WSACleanup();
        return 1;
    }


    SOCKET *clientPtr= malloc(sizeof(SOCKET));

    if (clientPtr==NULL){
        printf("cannot allocate memory to socket pointer \n");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    *clientPtr=clientSocket;

    HANDLE reception= newThread(clientPtr, recvThread);
    if(reception==NULL){
        printf("failed to create reception handle \n");
        free(clientPtr);
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    HANDLE sending= newThread(clientPtr, sendThread);

    if (sending==NULL){
        printf("can't make send handle \n");
        free(clientPtr);
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    WaitForSingleObject(reception, INFINITE);
    WaitForSingleObject(sending, INFINITE);

    CloseHandle(reception);
    CloseHandle(sending);
    free(clientPtr);
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
