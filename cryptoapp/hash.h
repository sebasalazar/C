/**
 * @file hash.h
 * @autor Sebastián Salazar Molina. <sebasalazar@gmail.com>
 */

#ifndef HASH_H
#define	HASH_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "openssl/bio.h"
#include "openssl/evp.h"
#include "openssl/md5.h"
#include "openssl/sha.h"
#include "openssl/buffer.h"

#include "utils.h"

    /**
     * @fn byte* base64_encode(byte *buffer, unsigned int len, int *len_out)
     * @param buffer texto a ser encodeado.
     * @param len largo del texto a ser encodeado
     * @param len_out largo final del texto a ser encodeado.
     * @return La representación encodeada del texto ingresado.
     * @retval byte*
     */
    byte* base64_encode(byte *buffer, unsigned int len, int *len_out);

    /**
     * @fn byte* base64_decode(byte *buffer, unsigned int len, int *len_out)
     * @param buffer texto a ser desencodeado.
     * @param len largo del texto a ser desencodeado
     * @param len_out largo final del texto a ser desencodeado.
     * @return La representación desencodeada del texto ingresado.
     * @retval byte*
     */
    byte* base64_decode(byte *buffer, unsigned int len, int *len_out);

    /**
     * @fn byte* md5(const byte* input, size_t* len, int hex)
     * @param input texto de entrada
     * @param len largo del texto de entrada
     * @param hex si el texto debe representarse hexadecimalmente
     * @return una cadena de texto con la representación en md5 del texto
     * @retval byte*
     */
    byte* md5(const byte* input, size_t* len, int hex);

    /**
     * @fn byte* sha1(const byte* input, size_t* len, int hex)
     * @param input texto de entrada
     * @param len largo del texto de entrada
     * @param hex si el texto debe representarse hexadecimalmente
     * @return una cadena de texto con la representación en sha1 del texto
     * @retval byte*
     */
    byte* sha1(const byte* input, size_t* len, int hex);

    /**
     * @fn byte* url_encode(byte* input, int len_data, int *len_out)
     * @param input arreglo de entrada a ser encodeado
     * @param len_data largo del arreglo de entrada
     * @param len_out largo del texto url encodeado
     * @return un arreglo encodeado para urls.
     * @retval byte*
     */
    byte* url_encode(byte* input, int len_data, int *len_out);
    
    /**
     * @fn byte* url_decode(byte* input, int len_data, int *len_out)
     * @param input arreglo de entrada a ser desencodeado
     * @param len_data largo del arreglo de entrada
     * @param len_out largo del texto url desencodeado
     * @return un arreglo desencodeado 
     * @retval byte*
     */
    byte* url_decode(byte* input, int len_data, int *len_out);
#ifdef	__cplusplus
}
#endif

#endif	/* HASH_H */

