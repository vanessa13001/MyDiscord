#ifndef DATABASE_H
#define DATABASE_H

#include <libpq-fe.h>

PGconn* connect_to_db(void);
void disconnect_db(PGconn *conn);
void execute_sql_from_file(const char *filename, PGconn *conn);
int db_insert_user(PGconn *conn, const char* name, const char* surname, const char* email, const char* encrypted);
int db_check_user(PGconn *conn, const char* email, const char* encrypted);

#endif // DATABASE_H