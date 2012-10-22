/**
 * @file comunicacion.h
 * @author Sebastián Salazar Molina <sebasalazar@gmail.com> 
 */

#ifndef COMUNICACION_H
#define	COMUNICACION_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>
#include "curl/curl.h"

    typedef struct {
        char *data;
        int body_size;
        int body_pos;
    } postdata;


    int enviar_post(char* servidor, int puerto, char *url, char* post, int desarrollo);
    int escribir_datos(void *ptr, size_t size, size_t nmemb, void *ctx);
    size_t leer_datos(void *ptr, size_t size, size_t nmemb, void *stream);
    int menor(int a, int b);
    char* comunicar(char* servidor, int puerto, char *url, char* enviar, int verificar_ssl);

#ifdef	__cplusplus
}
#endif

#endif	/* COMUNICACION_H */

