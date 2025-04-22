#include "../H/clientFuncs.h"

int main(){

    initWinsock();
    
    SOCKET clientSocket= createSocket();

    struct sockaddr_in serverAddress= createAddress("127.0.0.1", 8080);

    connectToServer(clientSocket,&serverAddress);

    return 0;
}
