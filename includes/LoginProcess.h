#ifndef LOGINPROCESS_H
#define LOGINPROCESS_H

#include <libpq-fe.h>

int login_user(PGconn *conn, const char *email, const char *password);

#endif 