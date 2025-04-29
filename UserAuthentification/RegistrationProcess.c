#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "RegistrationProcess.h"
#include "HashPassword.h"
#include "config.h" 

// Register user process
int register_user(PGconn *conn, const char *name, const char *surname, const char *email, const char *password) {
    if (!validate_email(email)) {
        fprintf(stderr, "Invalid email format\n");
        return 0;
    }

    if (!validate_password(password)) {
        fprintf(stderr, "Password does not meet complexity requirements\n");
        return 0;
    }

    // Check if email already exists
    const char *check_email_query = "SELECT id FROM users WHERE email = $1";
    const char *params_check[1] = {email};

    PGresult *check_res = PQexecParams(conn, check_email_query, 1, NULL, params_check, NULL, NULL, 0);
    if (PQresultStatus(check_res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Error checking email: %s\n", PQerrorMessage(conn));
        PQclear(check_res);
        return 0;
    }

    if (PQntuples(check_res) > 0) {
        fprintf(stderr, "Email is already in use\n");
        PQclear(check_res);
        return 0;
    }

    // Free the result of the check
    PQclear(check_res);

    char *salt = generate_salt();
    char *hashed_password = hash_password(password, salt, PEPPER);

    const char *query = "INSERT INTO users (first_name, last_name, email, password_hash, salt) VALUES ($1, $2, $3, $4, $5)";
    const char *params[5] = {name, surname, email, hashed_password, salt};

    PGresult *res = PQexecParams(conn, query, 5, NULL, params, NULL, NULL, 0);
    free(salt);
    free(hashed_password);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Insert user failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return 0;
    }

    PQclear(res);
    return 1;
}