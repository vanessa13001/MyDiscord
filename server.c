#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <pthread.h>

#define PORT 12345
#define MAX_CLIENTS 30
#define BUFFER_SIZE 1024

int client_sockets[MAX_CLIENTS] = {0};
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void send_client_list(SOCKET client_socket) {
    char list_msg[BUFFER_SIZE] = "Connected clients:\n";

    pthread_mutex_lock(&lock);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] != 0) {
            char client_info[64];
            snprintf(client_info, sizeof(client_info), " - Client #%d (socket %lld)\n", i + 1, (long long)client_sockets[i]);
            strncat(list_msg, client_info, sizeof(list_msg) - strlen(list_msg) - 1);
        }
    }
    pthread_mutex_unlock(&lock);

    send(client_socket, list_msg, strlen(list_msg), 0);
}

void *handle_client(void *arg) {
    SOCKET client_socket = *(SOCKET *)arg;
    char buffer[BUFFER_SIZE];
    int read_size;

    while ((read_size = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[read_size] = '\0';

        if (strncmp(buffer, "/quit", 5) == 0) {
            printf("Client %lld requested disconnection.\n", (long long)client_socket);
            break;
        }

        if (strncmp(buffer, "/list", 5) == 0) {
            send_client_list(client_socket);
            continue;
        }

        pthread_mutex_lock(&lock);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_sockets[i] != 0 && client_sockets[i] != (int)client_socket) {
                send(client_sockets[i], buffer, read_size, 0);
            }
        }
        pthread_mutex_unlock(&lock);
        memset(buffer, 0, BUFFER_SIZE);
    }

    if (read_size == 0) {
        printf("Client %lld disconnected.\n", (long long)client_socket);
    }

    closesocket(client_socket);
    pthread_mutex_lock(&lock);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] == (int)client_socket) {
            client_sockets[i] = 0;
            break;
        }
    }
    pthread_mutex_unlock(&lock);

    free(arg);
    pthread_exit(NULL);
    return NULL;
}

int main() {
    WSADATA wsaData;
    SOCKET server_socket, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    pthread_t client_thread;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("Socket creation failed");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) < 0) {
        perror("Listen failed");
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_socket, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
            perror("Accept failed");
            continue;
        }

        pthread_mutex_lock(&lock);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_sockets[i] == 0) {
                client_sockets[i] = (int)new_socket;
                break;
            }
        }
        pthread_mutex_unlock(&lock);

        SOCKET *new_sock = malloc(sizeof(SOCKET));
        *new_sock = new_socket;

        if (pthread_create(&client_thread, NULL, handle_client, (void *)new_sock) < 0) {
            perror("Could not create thread");
            closesocket(new_socket);
            free(new_sock);
            continue;
        }

        pthread_detach(client_thread);

        printf("New client connected: %lld\n", (long long)new_socket);
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}
