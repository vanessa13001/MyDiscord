#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "client.h" 

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

void send_command(int sock, const char *cmd) {
    send(sock, cmd, strlen(cmd), 0);
}

void get_input(char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; 
}

int main() {
   
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }

   
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

   
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stderr, "Connection failed\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("1. Register\n2. Login\nChoose option: ");
    char option[2];
    fgets(option, sizeof(option), stdin);
    getchar(); 
    char name[100], surname[100], email[100], password[100];
    char buffer[1024];

    if (option[0] == '1') {
        get_input("Name: ", name, sizeof(name));
        get_input("Surname: ", surname, sizeof(surname));
        get_input("Email: ", email, sizeof(email));
        get_input("Password: ", password, sizeof(password));
        snprintf(buffer, sizeof(buffer), "REGISTER|%s|%s|%s|%s", name, surname, email, password);
    } else if (option[0] == '2') {
        get_input("Email: ", email, sizeof(email));
        get_input("Password: ", password, sizeof(password));
        snprintf(buffer, sizeof(buffer), "LOGIN|%s|%s", email, password);
    } else {
        printf("Invalid option.\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    send_command(sock, buffer);

    char response[1024];
    int len = recv(sock, response, sizeof(response) - 1, 0);
    if (len > 0) {
        response[len] = '\0';
        printf("Server response: %s\n", response);
    } else {
        printf("Error receiving response from server.\n");
    }

   
    closesocket(sock);

    
    WSACleanup();

    return 0;
}