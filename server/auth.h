#ifndef AUTH_H
#define AUTH_H

#include <libpq-fe.h>

int register_user(PGconn *conn, const char *name, const char *surname, const char *email, const char *password);
int login_user(PGconn *conn, const char *email, const char *password);
void xor_encrypt_decrypt(char *data, char key);

#endif // AUTH_H