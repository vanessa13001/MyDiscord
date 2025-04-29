#ifndef HASHPASSWORD_H
#define HASHPASSWORD_H

#include <stdbool.h>

char* load_pepper();
char* generate_salt();
char* hash_password(const char *password, const char *salt, const char *pepper);

#endif 