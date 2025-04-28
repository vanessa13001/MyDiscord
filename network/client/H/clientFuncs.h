#ifndef CLIENTFUNCS_H
#define CLIENTFUNCS_H

#include "../../networkFuncs.h"

int connectToServer(SOCKET clientSocket, struct sockaddr_in* serverAddress);


#endif