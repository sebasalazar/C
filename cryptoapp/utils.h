/**
 * @file utils.h
 * @autor Sebastián Salazar Molina. <sebasalazar@gmail.com>
 */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    /**
     * @typede typedef unsigned char byte
     * Definición por comodidad de un unsigned char byte 
     */
    typedef unsigned char byte;

    /**
     * @fn char* hex2str(byte *hex, unsigned int len)
     * @param hex representación hexadecimal.
     * @param len largo del mensaje hexadecimal.
     * @return una representación string del mensaje hexadecimal.
     * @retval char*
     */
    char* hex2str(byte *hex, unsigned int len);
    
    /**
     * @fn long fsize(FILE * file)
     * @param file Puntero a un archivo.
     * @return retorna el tamaño del archivo
     * @retval long
     */
    long fsize(FILE * file);
    
    /**
     * @fn size_t leer_archivo(char ** str, const char * name, _Bool * error)
     * @param str 
     * @param name Nombre de la variable en que se almacena el texto.
     * @param error Variable que indica si existió error en el proceso.
     * @return El tamaño del archivo leido.
     * @retval size_t
     */
    size_t leer_archivo(char ** str, const char * name, _Bool * error);

#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */

