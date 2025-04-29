#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ForgotPasswordProcess.h"
#include "HashPassword.h"
#include "config.h" 

// Verify security questions
bool verify_security_questions(PGconn *conn, const char *email, const char *answer1, const char *answer2) {
    const char *query = "SELECT question_1, question_2 FROM users WHERE email = $1";
    const char *params[1] = {email};

    PGresult *res = PQexecParams(conn, query, 1, NULL, params, NULL, NULL, 0);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Error fetching security questions: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }

    if (PQntuples(res) == 0) {
        fprintf(stderr, "Email not found\n");
        PQclear(res);
        return false;
    }

    const char *stored_answer1 = PQgetvalue(res, 0, 0);
    const char *stored_answer2 = PQgetvalue(res, 0, 1);
    PQclear(res);

    return (strcmp(stored_answer1, answer1) == 0 && strcmp(stored_answer2, answer2) == 0);
}

// Update password in the database
int update_password(PGconn *conn, const char *email, const char *new_password) {
    char *salt = generate_salt();
    char *hashed_password = hash_password(new_password, salt, PEPPER); 

    const char *query = "UPDATE users SET password_hash = $1, salt = $2 WHERE email = $3";
    const char *params[3] = {hashed_password, salt, email};

    PGresult *res = PQexecParams(conn, query, 3, NULL, params, NULL, NULL, 0);
    free(salt);
    free(hashed_password);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Error updating password: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return 0;
    }

    PQclear(res);
    return 1;
}