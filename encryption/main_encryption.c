#include <stdio.h>
#include <string.h>
#include "encrypt_decrypt.h"

#define MAX_LENGTH 1500 // max message length
#define KEY_LENGTH 16   // length of the generated key


int main() {
    char original_message[MAX_LENGTH];
    char encrypted_message[MAX_LENGTH];
    char decrypted_message[MAX_LENGTH];
    char key[KEY_LENGTH + 1];

    printf("enter the message 150 max : ");
    fgets(original_message, MAX_LENGTH, stdin);
    original_message[strcspn(original_message, "\n")] = '\0'; // Enlever le caractère de nouvelle ligne

    // generate keys automatically
    // generate_random_key(key, KEY_LENGTH);

    generate_random_key(key, KEY_LENGTH);
    printf("generate keys : %s\n", key);

  // original message for encryption
    strcpy(encrypted_message, original_message);
    xor_cipher(encrypted_message, key);
    printf("crypte : %s\n", encrypted_message);

   // encrypted message for decryption
    strcpy(decrypted_message, encrypted_message);
    xor_cipher(decrypted_message, key);
    printf("decrypt : %s\n", decrypted_message);

    return 0;
}
