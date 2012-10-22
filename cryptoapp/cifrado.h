/**
 * @file crypto_firm.h
 * @autor Sebastián Salazar Molina. <ssalazar@orangepeople.cl>
 */

#ifndef CRYPTO_FIRM_H
#define	CRYPTO_FIRM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>

#include "rsa.h"
#include "aes.h"
#include "hash.h"

    /**
     * @fn char* cifrar(char* pub_cert, char* llave, byte* mensaje)
     * @param pub_cert Ruta al certificado público, debe ser tipo PEM.
     * @param llave_privada Ruta al certificado privado, usado para firmar., debe ser tipo PEM.
     * @param llave clave para hacer el cifrado.
     * @param mensaje texto a ser cifrado
     * @return El mensaje cifrado en base64, el mensaje se compone de 16 bytes del vector IV + el tamaño del RSA (que tiene contenida la llave) + el texto cifrado.
     * @retval char*
     *
     */
    char* cifrar(char* pub_cert, char* llave_privada, byte* mensaje);

    /**
     * @fn byte* descifrar(char* priv_cert, char* encodeado)
     * @param priv_cert Ruta al certificado privado, debe ser del tipo PEM.
     * @param llave_publica Ruta al certificado público, usado para firmar., debe ser tipo PEM.
     * @param encodeado Texto encodeado en base64
     * @return El mensaje descifrado.
     * @retval byte*
     */
    byte* descifrar(char* priv_cert, char* llave_publica, char* encodeado);


#ifdef	__cplusplus
}
#endif

#endif	/* CRYPTO_FIRM_H */

