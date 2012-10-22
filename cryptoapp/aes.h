/**
 * @file aes.h
 * @autor Sebastián Salazar Molina. <sebasalazar@gmail.com>
 */

#ifndef AES_H
#define	AES_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "openssl/bio.h"
#include "openssl/aes.h"
#include "openssl/rand.h"
#include "openssl/evp.h"
#include "openssl/err.h"

#include "utils.h"    

    /**
     * @fn byte* generar_llave(char* llave)
     * @param llave texto base para generar la llave.
     * @return la representación en un arreglo de 32 bytes
     * @retval byte*
     */
    byte* generar_llave(char* llave);

    /**
     * @fn byte* cifrar_aes(byte* llave, byte* iv, byte* mensaje, int* largo_cifrado)
     * @param llave arreglo de 32 bytes con la llave.
     * @param iv vector de inicialización de 16 bytes
     * @param mensaje texto en claro a ser cifrado.
     * @param largo_cifrado largo final del cifrado.
     * @return Texto cifrado, por la llave y el vector de inicialización.
     * @retval byte*
     */
    byte* cifrar_aes(byte* llave, byte* iv, byte* mensaje, int* largo_cifrado);

    /**
     * @fn byte* descifrar_aes(byte* llave, byte* iv, byte* cifrado, int* largo)
     * @param llave arreglo de 32 bytes con la llave.
     * @param iv vector de inicialización de 16 bytes
     * @param cifrado texto cifrado
     * @param largo largo del texto descifrado
     * @return texto descifrado.
     * @retval byte*
     */
    byte* descifrar_aes(byte* llave, byte* iv, byte* cifrado, int* largo);

#ifdef	__cplusplus
}
#endif

#endif	/* AES_H */

