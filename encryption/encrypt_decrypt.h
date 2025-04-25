#ifndef ENCRYPT_DECRYPT_H
#define ENCRYPT_DECRYPT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// XOR encryption/decryption
void xorEncryptDecrypt(char *message, const char *key);

// Function to encode in Base64
void encodeBase64(const char* input, char* output);

#endif // ENCRYPT_DECRYPT_H
