#include "encrypt_decrypt.h"

#define MAX_LENGTH 1000 // Max length of the message
#define KEY_LENGTH 16 // Length of the key  

int main() {
    char original_message[MAX_LENGTH];
    char encrypted_message[MAX_LENGTH];// Encrypted message
    // char decrypted_message[MAX_LENGTH]; // Decrypted message 
    char decrypted_message[MAX_LENGTH];
    char key[KEY_LENGTH + 1];

    printf("Enter the message: ");
    fgets(original_message, MAX_LENGTH, stdin);
    original_message[strcspn(original_message, "\n")] = '\0'; 

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
