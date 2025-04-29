#ifndef REGISTRATIONPROCESS_H
#define REGISTRATIONPROCESS_H

#include <libpq-fe.h>

int register_user(PGconn *conn, const char *name, const char *surname, const char *email, const char *password);

#endif 