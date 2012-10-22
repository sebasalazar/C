#include <stdio.h>
#include <stdlib.h>

#include "aes.h"
#include "rsa.h"
#include "utils.h"
#include "cifrado.h"
#include "openssl/ssl.h"

int main(int argc, char** argv) {

    // Variables
    char llave_publica[1024];
    char llave_privada[1024];
    char mensaje[1024];
    
    // Inicialización de OpenSSL
    SSL_library_init();
    ERR_load_BIO_strings();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    fprintf(stdout, "\nEjemplo de uso AES / RSA con OpenSSL en C\n\t\tDesarrollado por Sebastian Salazar Molina\n");
    if (argc < 4) {
        fprintf(stdout,"\nForma de uso: %s \"ruta llave publica\" \"ruta llave privada\" \"mensaje\" \n", argv[0]);
    } else {
        sprintf(llave_publica, "%s", argv[1]);
        sprintf(llave_privada, "%s", argv[2]);
        sprintf(mensaje, argv[3]);
        
        char* cifrado = cifrar(llave_publica, llave_privada, (byte *) mensaje);
        char* descifrado = descifrar(llave_privada, llave_publica, cifrado);
        fprintf(stdout, "\nMensaje: %s-%d", mensaje, (int) strlen(mensaje));
        fprintf(stdout, "\nMensaje Cifrado: %s-%d", cifrado, (int) strlen(cifrado));
        fprintf(stdout, "\nMensaje Descifrado: %s-%d", descifrado, (int) strlen(descifrado));
        fprintf(stdout, "\n\n");
    }

    return (EXIT_SUCCESS);
}

