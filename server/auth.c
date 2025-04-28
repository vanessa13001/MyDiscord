#include <stdio.h>
#include <string.h>
#include "database.h"
#include "auth.h"

// XOR-
void xor_encrypt_decrypt(char *data, char key) {
    for (int i = 0; data[i] != '\0'; ++i) {
        data[i] ^= key;
    }
}

// Регистрация 
int register_user(PGconn *conn, const char *name, const char *surname, const char *email, const char *password) {
    if (!name || !surname || !email || !password) {
        fprintf(stderr, " Invalid input to register_user\n");
        return 0;
    }

    char encrypted[256];
    strncpy(encrypted, password, sizeof(encrypted) - 1);
    encrypted[sizeof(encrypted) - 1] = '\0';

    xor_encrypt_decrypt(encrypted, 'K');  //  шифрование

    return db_insert_user(conn, name, surname, email, encrypted);
}

//  (логин)
int login_user(PGconn *conn, const char *email, const char *password) {
    if (!email || !password) {
        fprintf(stderr, " Invalid input to login_user\n");
        return 0;
    }

    char encrypted[256];
    strncpy(encrypted, password, sizeof(encrypted) - 1);
    encrypted[sizeof(encrypted) - 1] = '\0';

    xor_encrypt_decrypt(encrypted, 'K');  // Шифруем 

    return db_check_user(conn, email, encrypted);
}