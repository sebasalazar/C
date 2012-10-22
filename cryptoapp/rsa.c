#include "rsa.h"

byte* cifrar_llave_rsa(RSA *rsa, byte* mensaje, int* outlen) {
    byte* aeskeybytes = NULL;
    ERR_clear_error();

    if (rsa == NULL) {
        fprintf(stderr, "RSA nulo.");
    } else {
        int tamano = 0;
        tamano = RSA_size(rsa);

        aeskeybytes = (byte *) malloc(sizeof (byte *) * tamano);

        *outlen = RSA_public_encrypt(32, mensaje, aeskeybytes, rsa, RSA_PKCS1_OAEP_PADDING);
        if ((*outlen) == -1) {
            fprintf(stderr, "\nError: %s\n", ERR_error_string(ERR_get_error(), NULL));
        }
    }
    return aeskeybytes;
}

byte* descifrar_llave_rsa(RSA *rsa, byte* mensaje, int* outlen) {
    byte* mensajeDesnc = NULL;
    ERR_clear_error();

    if (rsa == NULL) {
        fprintf(stderr, "RSA nulo.");
    } else {
        int rsaencsize = RSA_size(rsa);

        mensajeDesnc = (byte *) malloc(32 * sizeof (byte *));

        *outlen = RSA_private_decrypt((rsaencsize), mensaje, mensajeDesnc, rsa, RSA_PKCS1_OAEP_PADDING);

        if ((*outlen) == -1) {
            fprintf(stderr, "\nError: %s\n", ERR_error_string(ERR_get_error(), NULL));
        }
    }
    return mensajeDesnc;

}

byte* descifrar_firma_rsa(RSA *rsa, byte* mensaje, int* outlen) {
    byte* mensajeDesnc = NULL;
    ERR_clear_error();

    if (rsa == NULL) {
        fprintf(stderr, "RSA nulo.");
    } else {
        int largo_mensaje = strlen((char *) mensaje);
        int rsaencsize = RSA_size(rsa);

        fprintf(stdout, "\nLargo Mensaje: %d %d\n", largo_mensaje, rsaencsize);

        mensajeDesnc = (byte *) malloc(largo_mensaje * sizeof (byte *));
        memset(mensaje, 0, largo_mensaje);

        *outlen = RSA_private_decrypt((rsaencsize), mensaje, mensajeDesnc, rsa, RSA_PKCS1_PADDING);

        if ((*outlen) == -1) {
            fprintf(stderr, "\nError: %s\n", ERR_error_string(ERR_get_error(), NULL));
        }
    }
    return mensajeDesnc;

}

RSA* obtenerRSA(char* archivo, int publica) {
    RSA *rsa;
    FILE *ptr;


    ptr = fopen(archivo, "rb");
    if (ptr != NULL) {

        if (publica > 0) {
            rsa = PEM_read_RSA_PUBKEY(ptr, NULL, NULL, NULL);
        } else {
            rsa = PEM_read_RSAPrivateKey(ptr, NULL, NULL, NULL);
        }
        fclose(ptr);
    } else {
        fprintf(stderr, "Error al abrir archivo %s", archivo);
        rsa = RSA_new();
    }

    return rsa;
}

byte* firma_mensaje(RSA* llave_firma_priv, byte* mensaje, int* outlen) {
    byte* salida = NULL;
    ERR_clear_error();

    if (llave_firma_priv != NULL) {
        int estado;
        unsigned int tamano_firma;
        int rsaensize = RSA_size(llave_firma_priv);
        int largo_mensaje = strlen((char *) mensaje);
        int rc = 0;
        // SHA256_CTX sha_ctx = {0};
        SHA256_CTX sha_ctx;
        byte digest[SHA256_DIGEST_LENGTH];

        rc = SHA256_Init(&sha_ctx);
        rc = SHA256_Update(&sha_ctx, mensaje, largo_mensaje);
        rc = SHA256_Final(digest, &sha_ctx);

        salida = (byte *) malloc(sizeof (byte *) * rsaensize);

        estado = RSA_sign(NID_sha256, digest, sizeof (digest), salida, &tamano_firma, llave_firma_priv);

        if (estado == 0) {
            *outlen = 0;
            fprintf(stderr, "\nError: %s\nRetorno del SHA256: %d", ERR_error_string(ERR_get_error(), NULL), rc);
        } else {
            *outlen = tamano_firma;
        }
    }
    return salida;
}


int verificar_mensaje(RSA* llave_firma_pub, byte* mensaje, int largo_mensaje, byte* firma) {
    int salida = 0;
    ERR_clear_error();

    if (llave_firma_pub != NULL) {
        int estado;
        int rsaensize = RSA_size(llave_firma_pub);

        int rc = 0;
        // SHA256_CTX sha_ctx = {0};
        SHA256_CTX sha_ctx;
        byte digest[SHA256_DIGEST_LENGTH];

        rc = SHA256_Init(&sha_ctx);
        rc = SHA256_Update(&sha_ctx, mensaje, largo_mensaje);
        rc = SHA256_Final(digest, &sha_ctx);

        estado = RSA_verify(NID_sha256, digest, sizeof(digest), firma, rsaensize, llave_firma_pub);

        if (estado == 0) {
            fprintf(stderr, "\nError: %s\nRetorno del SHA256: %d", ERR_error_string(ERR_get_error(), NULL), rc);
        }
        salida = estado;
    }

    return salida;
}
