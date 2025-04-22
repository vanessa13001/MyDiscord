#ifndef SERVERFUNCS_H
#define SERVERFUNCS_H

#include "networkFuncs.h"

int bindServer(SOCKET serverSocket, struct sockaddr_in* address);

int listenConnection(SOCKET serverSocket);

#endif