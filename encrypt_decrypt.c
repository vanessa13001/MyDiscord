// declare fonctions
#include "encrypt_decrypt.h"  


// static key encrypt_decrypt
const char *key = "maCleSecrete123"; 

// XOR encrypt_decrypt
void xorEncryptDecrypt(char *message, const char *key) {
    int messageLength = strlen(message);
    int keyLength = strlen(key);

    for (int i = 0; i < messageLength; i++) {
        message[i] = message[i] ^ key[i % keyLength]; // Opération XOR
    }
}

// Function to encode in Base64
void encodeBase64(const char* input, char* output) {
    static const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int input_length = strlen(input);
    int i = 0, j = 0;
    unsigned char arr_3[3], arr_4[4];


    // We enter the loop as long as input_length > 0, and decrease it by 1 after evaluation
    while (input_length--) {
        arr_3[i++] = *(input++);
        if (i == 3) {
            arr_4[0] = (arr_3[0] & 0xfc) >> 2;

            //0x0f = 00001111 → Keep the last 4 bits of arr_3[1], shift them left by 2 bits
            arr_4[1] = ((arr_3[0] & 0x03) << 4) | ((arr_3[1] & 0xf0) >> 4);

            //0xc0 = 11000000 → Keep the first 2 bits of arr_3[2], shift them right by 6 bits
            arr_4[2] = ((arr_3[1] & 0x0f) << 2) | ((arr_3[2] & 0xc0) >> 6);
            arr_4[3] = arr_3[2] & 0x3f;

            for (i = 0; i < 4; i++) {
                output[j++] = encoding_table[arr_4[i]];
            }
            i = 0;
        }
    }

    if (i) {
        for (int k = i; k < 3; k++) {
            arr_3[k] = '\0';
        }

        arr_4[0] = (arr_3[0] & 0xfc) >> 2;
        arr_4[1] = ((arr_3[0] & 0x03) << 4) | ((arr_3[1] & 0xf0) >> 4);
        arr_4[2] = ((arr_3[1] & 0x0f) << 2) | ((arr_3[2] & 0xc0) >> 6);

        //0x3f = 00111111 → Keep the last 6 bits of arr_3[2].
        arr_4[3] = arr_3[2] & 0x3f;

        for (int k = 0; k < i + 1; k++) {
            output[j++] = encoding_table[arr_4[k]];
        }

        while (i++ < 3) {
            output[j++] = '=';
        }
    }
    output[j] = '\0';
}
