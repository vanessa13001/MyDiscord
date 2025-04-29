#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "LoginProcess.h"
#include "HashPassword.h" 

// Login user process
int login_user(PGconn *conn, const char *email, const char *password) {
    const char *query = "SELECT id, password_hash, salt FROM users WHERE email = $1";
    const char *params[1] = {email};

    PGresult *res = PQexecParams(conn, query, 1, NULL, params, NULL, NULL, 0);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Login failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return 0;
    }

    if (PQntuples(res) == 0) {
        fprintf(stderr, "Invalid email or password\n");
        PQclear(res);
        return 0;
    }

    char *stored_password_hash = PQgetvalue(res, 0, 1);
    char *salt = PQgetvalue(res, 0, 2); 
    char *pepper = load_pepper();
    char *hashed_password = hash_password(password, salt, pepper);

    if (strcmp(stored_password_hash, hashed_password) != 0) {
        fprintf(stderr, "Invalid email or password\n");
        free(hashed_password);
        free(pepper);
        PQclear(res);
        return 0;
    }

    free(hashed_password);
    free(pepper);
    PQclear(res);
    return atoi(PQgetvalue(res, 0, 0)); // Return user id
}

   //BETTER HANDLE ERROR MESSAGES TO DISPLAY THEM IN UI AND IMPROVE USER EXPERIENCE