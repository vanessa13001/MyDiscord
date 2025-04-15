#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <pthread.h>

#define PORT 12345
#define BUFFER_SIZE 1024

void *receive_messages(void *arg) {
    SOCKET client_socket = *(SOCKET *)arg;
    char buffer[BUFFER_SIZE];
    int read_size;

    while ((read_size = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[read_size] = '\0';
        printf("%s\n", buffer);
        memset(buffer, 0, BUFFER_SIZE);
    }

    if (read_size == 0) {
        printf("disconnected from server.\n");
        closesocket(client_socket);
    }

    pthread_exit(NULL);
    return NULL;
}

int main() {
    WSADATA wsaData;
    SOCKET client_socket;
    struct sockaddr_in address;
    pthread_t receive_thread;
    char buffer[BUFFER_SIZE];

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("socket failed");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
        perror("invalid address");
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("connect failed");
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    printf("Connecté au serveur. Tapez /quit pour quitter.\n");

    if (pthread_create(&receive_thread, NULL, receive_messages, (void *)&client_socket) < 0) {
        perror("could not create thread");
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "/quit") == 0) {
            send(client_socket, buffer, strlen(buffer), 0);
            printf("Déconnexion demandée. Fermeture du client...\n");
            break;
        }

        send(client_socket, buffer, strlen(buffer), 0);
    }

    closesocket(client_socket);
    WSACleanup();
    pthread_exit(NULL);
    return 0;
}
