#ifndef FORGOTPASSWORDPROCESS_H
#define FORGOTPASSWORDPROCESS_H

#include <gtk/gtk.h>
#include <libpq-fe.h>
#include <stdbool.h>

bool verify_security_questions(PGconn *conn, const char *email, const char *answer1, const char *answer2);
int update_password(PGconn *conn, const char *email, const char *new_password);
char* generate_salt();
char* hash_password(const char *password, const char *salt, const char *pepper);
char* load_pepper();

#endif 