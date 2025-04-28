#ifndef CLIENT_H
#define CLIENT_H

void send_command(int sock, const char *cmd);
void get_input(char *prompt, char *buffer, int size);

#endif // CLIENT_H