#include "encrypt_decrypt.h" 

int main() {
    char message[256];
    char encodedMessage[512];

    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);

     // Remove the newline "\n"
    message[strcspn(message, "\n")] = 0; 

    // Encrypt the message with the static key
    xorEncryptDecrypt(message, "maCleSecrete123");
    encodeBase64(message, encodedMessage);
    printf("\nEncrypted message in Base64: %s\n", encodedMessage);

    // Decrypt with the key
    xorEncryptDecrypt(message, "maCleSecrete123");
    printf("\nDecrypted message: %s\n", message);

    return 0;
}
