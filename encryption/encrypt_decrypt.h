
#ifndef ENCRYPT_DECRYPT_H
#define ENCRYPT_DECRYPT_H
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void xor_cipher(char *message, const char *key);
void generate_random_key(char *key, int length);

#endif // ENCRYPT_DECRYPT_H
