#ifndef NETWORKFUNCS_H
#define NETWORKFUNCS_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

int initWinsock();

SOCKET createSocket();

struct sockaddr_in createAddress(const char* ip, int port);

#endif