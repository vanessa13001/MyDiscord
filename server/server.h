#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <libpq-fe.h>

void handle_client(SOCKET client_sock, PGconn *conn);

#endif // SERVER_H