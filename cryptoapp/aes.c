#include "aes.h"

byte* generar_llave(char* llave) {
    int i = 0, redondeo = 5;
    byte* key = (byte *) malloc(32 * sizeof (byte *));
    i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), NULL, (byte *) llave, strlen(llave), redondeo, key, NULL);
    if (i != 32) {
        fprintf(stderr, "El tamaño de la llave es de %d bits - Debería ser de 256 bits\n", i);
        return NULL;
    }
    return key;
}

byte* cifrar_aes(byte* llave, byte* iv, byte* texto, int* largo) {
    int largo_cifrado = (((*largo) / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;

    EVP_CIPHER_CTX *ctx_cifrado = EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(ctx_cifrado, EVP_aes_256_cbc(), NULL, llave, iv);

    int largo_final = 0;
    byte *cifrado = (byte *) malloc(largo_cifrado * sizeof (byte*));

    EVP_EncryptUpdate(ctx_cifrado, cifrado, &largo_cifrado, texto, *largo);
    EVP_EncryptFinal_ex(ctx_cifrado, cifrado + largo_cifrado, &largo_final);

    *largo = largo_cifrado + largo_final;

    EVP_CIPHER_CTX_cleanup(ctx_cifrado);

    return cifrado;
}

byte* descifrar_aes(byte* llave, byte* iv, byte* cifrado, int* largo) {
    int largo_descifrado = *largo;
    int largo_final = 0;

    EVP_CIPHER_CTX *ctx_descifrado = EVP_CIPHER_CTX_new();

    EVP_DecryptInit_ex(ctx_descifrado, EVP_aes_256_cbc(), NULL, llave, iv);

    byte* texto = (byte *) malloc(largo_descifrado * sizeof (byte*));


    EVP_DecryptUpdate(ctx_descifrado, texto, &largo_descifrado, cifrado, *largo);
    EVP_DecryptFinal_ex(ctx_descifrado, texto + largo_descifrado, &largo_final);

    *largo = largo_descifrado + largo_final;

    EVP_CIPHER_CTX_cleanup(ctx_descifrado);

    return texto;
}
