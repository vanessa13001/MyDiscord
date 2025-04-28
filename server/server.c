#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#include "auth.h"
#include "database.h"
#include "server.h"

#define PORT 8080

// регистрации и логина пользователей, 
extern int register_user(PGconn *conn, const char *name, const char *surname, const char *email, const char *password);
extern int login_user(PGconn *conn, const char *email, const char *password);

void handle_client(SOCKET client_sock, PGconn *conn) {
    char buffer[1024];
    int valread = recv(client_sock, buffer, sizeof(buffer) - 1, 0);

    if (valread <= 0) {
        printf(" Failed to read from client or client disconnected.\n");
        closesocket(client_sock);
        return;
    }

    buffer[valread] = '\0';
    printf(" Received: %s\n", buffer);

    char *cmd = strtok(buffer, "|");
    if (!cmd) {
        const char *msg = "Invalid command format";
        send(client_sock, msg, strlen(msg), 0);
        closesocket(client_sock);
        return;
    }

    if (strcmp(cmd, "REGISTER") == 0) {
        char *name = strtok(NULL, "|");
        char *surname = strtok(NULL, "|");
        char *email = strtok(NULL, "|");
        char *password = strtok(NULL, "|");

        if (!name || !surname || !email || !password) {
            const char *msg = " Invalid registration data";
            send(client_sock, msg, strlen(msg), 0);
        } else if (register_user(conn, name, surname, email, password)) {
            const char *msg = " Registration successful";
            send(client_sock, msg, strlen(msg), 0);
        } else {
            const char *msg = "Registration failed";
            send(client_sock, msg, strlen(msg), 0);
        }

    } else if (strcmp(cmd, "LOGIN") == 0) {
        char *email = strtok(NULL, "|");
        char *password = strtok(NULL, "|");

        if (!email || !password) {
            const char *msg = " Invalid login data";
            send(client_sock, msg, strlen(msg), 0);
        } else if (login_user(conn, email, password)) {
            const char *msg = " Login successful";
            send(client_sock, msg, strlen(msg), 0);
        } else {
            const char *msg = " Login failed";
            send(client_sock, msg, strlen(msg), 0);
        }

    } else {
        const char *msg = " Unknown command";
        send(client_sock, msg, strlen(msg), 0);
    }

    closesocket(client_sock);
    printf("🔌 Client disconnected\n");
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf(" WSAStartup failed.\n");
        return 1;
    }

    PGconn *conn = connect_to_db();
    if (!conn) {
        WSACleanup();
        return 1;
    }

    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_fd == INVALID_SOCKET) {
        printf(" Socket creation failed: %d\n", WSAGetLastError());
        disconnect_db(conn);
        WSACleanup();
        return 1;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt)) == SOCKET_ERROR) {
        printf(" setsockopt failed: %d\n", WSAGetLastError());
    }

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    ZeroMemory(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        printf(" Bind failed: %d\n", WSAGetLastError());
        closesocket(server_fd);
        disconnect_db(conn);
        WSACleanup();
        return 1;
    }

    if (listen(server_fd, SOMAXCONN) == SOCKET_ERROR) {
        printf(" Listen failed: %d\n", WSAGetLastError());
        closesocket(server_fd);
        disconnect_db(conn);
        WSACleanup();
        return 1;
    }

    printf(" Server is listening on port %d\n", PORT);

    while (1) {
        SOCKET client_sock = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (client_sock != INVALID_SOCKET) {
            printf("🔗 Client connected\n");
            handle_client(client_sock, conn);
        } else {
            printf(" Accept failed: %d\n", WSAGetLastError());
        }
    }

    closesocket(server_fd);
    disconnect_db(conn);
    WSACleanup();
    return 0;
}