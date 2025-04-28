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

    printf("Entrez le message : ");
    fgets(original_message, MAX_LENGTH, stdin);
    original_message[strcspn(original_message, "\n")] = '\0'; // Enlever le caractère de nouvelle ligne

    // Générer une clé aléatoire
    generate_random_key(key, KEY_LENGTH);
    printf("Cle generee : %s\n", key);

    // Copier le message original pour l'encryptage
    strcpy(encrypted_message, original_message);
    xor_cipher(encrypted_message, key);
    printf("Message crypte : %s\n", encrypted_message);

    // Copier le message crypté pour le décryptage
    strcpy(decrypted_message, encrypted_message);
    xor_cipher(decrypted_message, key);
    printf("Message decrypte : %s\n", decrypted_message);

    return 0;
}
