#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "config.h"


PGconn* connect_to_db(void) {

    char conninfo[256];
    snprintf(conninfo, sizeof(conninfo), "host=%s port=%s dbname=%s user=%s password=%s", 
             DB_HOST, DB_PORT, DB_NAME, DB_USER, DB_PASSWORD);

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }

    printf("Connected to database successfully\n");
    return conn;
}

/* 
PGconn* connect_to_db(void) {
    const char *conninfo = "host=localhost port=5432 dbname=Discord user=postgres password=131721";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {  
        fprintf(stderr, " Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }

    printf(" Connected to database successfully\n");
    return conn;
}
*/
 
void disconnect_db(PGconn *conn) {
    if (conn) {
        PQfinish(conn);
        printf(" Disconnected from database\n");
    }
}

//  SQL
void execute_sql_from_file(const char *filename, PGconn *conn) {
    if (!conn || !filename) return;

    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, " Error opening file %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *query = malloc(size + 1);
    if (!query) {
        fprintf(stderr, " Memory allocation failed\n");
        fclose(file);
        return;
    }

    fread(query, 1, size, file);
    query[size] = '\0';

    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, " SQL execution failed: %s\n", PQerrorMessage(conn));
    } else {
        printf(" SQL executed successfully from %s\n", filename);
    }

    PQclear(res);
    free(query);
    fclose(file);
}

// Вставка 
    int db_insert_user(PGconn *conn, const char *name, const char *surname, const char *email, const char *encrypted) {
    if (!conn) return 0;

    const char *query = "INSERT INTO users (first_name, last_name, email, password_hash) VALUES ($1, $2, $3, $4)";
    const char *params[4] = {name, surname, email, encrypted};  // передаем правильные параметры

    PGresult *res = PQexecParams(conn, query, 4, NULL, params, NULL, NULL, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, " Insert user failed: %s\n", PQresultErrorMessage(res));
        PQclear(res);
        return 0;
    }

    printf(" User inserted successfully\n");
    PQclear(res);
    return 1;
}

// Проверка 
int db_check_user(PGconn *conn, const char* email, const char* encrypted) {
    if (!conn) return 0;

    const char *query = "SELECT id FROM users WHERE email = $1 AND password_hash = $2";
    const char *params[2] = {email, encrypted};

    PGresult *res = PQexecParams(conn, query, 2, NULL, params, NULL, NULL, 0);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, " Check user failed: %s\n", PQresultErrorMessage(res));
        PQclear(res);
        return 0;
    }

    int rows = PQntuples(res);
    PQclear(res);
    return rows > 0;
}