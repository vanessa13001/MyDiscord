#include <stdio.h>
#include <string.h>
#include "encrypt_decrypt.h"

#define MAX_LENGTH 1000
#define KEY_LENGTH 16 // Longueur de la clé générée

int main() {
    char original_message[MAX_LENGTH];
    char encrypted_message[MAX_LENGTH];
    char decrypted_message[MAX_LENGTH];
    char key[KEY_LENGTH + 1];

    printf("Enter the message: ");
    fgets(original_message, MAX_LENGTH, stdin);
    original_message[strcspn(original_message, "\n")] = '\0'; // Enlever le caractère de nouvelle ligne

    // keys generate automatically
    generate_random_key(key, KEY_LENGTH);
    printf("keys generate : %s\n", key);

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
