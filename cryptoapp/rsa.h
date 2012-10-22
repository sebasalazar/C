/**
 * @file rsa.h
 * @autor Sebastián Salazar Molina. <sebasalazar@gmail.com>
 */

#ifndef RSA_H
#define	RSA_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "openssl/bio.h"
#include "openssl/buffer.h"
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/err.h"
#include "openssl/evp.h"

#include "utils.h"

    /**
     * @fn byte* cifrar_llave_rsa(RSA *rsa, byte* mensaje, int* outlen)
     * @param rsa Estructura con el RSA del certificado.
     * @param mensaje mensaje a ser cifrado.
     * @param outlen largo del texto final a ser cifrado.
     * @return La llave cifrada en RSA, sólo se cifran 32 bytes.
     * @retval byte*
     */
    byte* cifrar_llave_rsa(RSA *rsa, byte* mensaje, int* outlen);

    /**
     * @fn byte* descifrar_llave_rsa(RSA *rsa, byte* mensaje, int* outlen)
     * @param rsa Estructura con el RSA del certificado.
     * @param mensaje mensaje cifrado en RSA
     * @param outlen tamaño del mensaje descifrado RSA
     * @return Llave descifrada del RSA.
     * @retval byte*
     */
    byte* descifrar_llave_rsa(RSA *rsa, byte* mensaje, int* outlen);

    /**
     * @fn byte* descifrar_firma_rsa(RSA *rsa, byte* mensaje, int* outlen)
     * @param rsa Estructura con el RSA del certificado.
     * @param mensaje mensaje cifrado en RSA
     * @param outlen tamaño del mensaje descifrado RSA
     * @return Retorna el mensaje descifrado de RSA.
     * @retval byte*
     */
    byte* descifrar_firma_rsa(RSA *rsa, byte* mensaje, int* outlen);

    /**
     * @fn RSA* obtenerRSA(char* archivo, int publica)
     * @param archivo Ruta al archivo que contiene el certificado.
     * @param publica Variable que indica si el certificado es público o privado.
     * @return una estructura RSA con todos sus campos, basados en el cerficado.
     * @retval RSA*
     */
    RSA* obtenerRSA(char* archivo, int publica);

    /**
     * @fn byte* firma_mensaje(RSA* llave_firma_priv, byte* mensaje, int* outlen);
     * @param llave_firma_priv Estructura RSA que contiene el certificado privado usado para la firma.
     * @param mensaje Mensaje para ser firmado
     * @param outlen Tamaño de salida de la firma
     * @return La firma del mensaje. Esta función utiliza métodos nativos.
     * @retval byte*
     */
    byte* firma_mensaje(RSA* llave_firma_priv, byte* mensaje, int* outlen);
    
    
    /**
     * @fn int verificar_mensaje(RSA* llave_firma_pub, byte* mensaje, int largo_mensaje, byte* firma)
     * @param llave_firma_pub Estructura RSA que contiene el certificado público usado para la firma.
     * @param mensaje Mensaje que se desea validar.
     * @param largo_mensaje largo del mensaje validado.
     * @param firma bytes con la firma.
     * @return 1 Si la firma es válida, 0 Si no lo es. Esta función utiliza métodos nativos.
     * @retval int
     */
    int verificar_mensaje(RSA* llave_firma_pub, byte* mensaje, int largo_mensaje, byte* firma);
    

#ifdef	__cplusplus
}
#endif

#endif	/* RSA_H */

