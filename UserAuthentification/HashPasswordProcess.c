#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "HashPassword.h"
#include "config.h"

// Load pepper from config
char* load_pepper() {
    return (char*)PEPPER; 
}

// Generate Salt
char* generate_salt() {
    char *salt = malloc(17);
    if (salt == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 16; i++) {
        salt[i] = 'a' + rand() % 26; 
    }
    salt[16] = '\0';
    return salt;
}

// Hash password with salt and pepper
char* hash_password(const char *password, const char *salt, const char *pepper) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    size_t data_length = strlen(password) + strlen(salt) + strlen(pepper);
    char *data_to_hash = malloc(data_length + 1);
    
    if (data_to_hash == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    snprintf(data_to_hash, data_length + 1, "%s%s%s", password, salt, pepper);
    
    SHA256((unsigned char*)data_to_hash, data_length, hash);
    free(data_to_hash);
    
    // Convert hash to hex
    char *hashed = malloc(65);
    if (hashed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed[i * 2], "%02x", hash[i]);
    }
    hashed[64] = '\0';
    return hashed;
}

// bcrypt, Argon2, or PBKDF2 ??
// rand_s() ??
