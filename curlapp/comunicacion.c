/**
 * @file comunicacion.c
 * @author Sebastián Salazar Molina <sebasalazar@gmail.com> 
 */
#include "comunicacion.h"

int enviar_post(char* servidor, int puerto, char *url, char* post, int desarrollo) {
    CURL *curl;
    CURLcode res;

    char* conexion;

    // Reservo espacio para el buffer del servidor
    conexion = (char *) calloc((strlen(servidor) + strlen(url) + 15), sizeof (char));

    sprintf(conexion, "https://%s:%d%s", servidor, puerto, url);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "OrangePeople/1.0");
        curl_easy_setopt(curl, CURLOPT_URL, conexion);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, ""); // mantener cookies en memoria. 
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);

        if (desarrollo == 1) {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); // No verificar el certificar peer 
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0); // No verificar contra el host del cert
        }

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1); // rebotar a la siguiente página 
        curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1); // mimic real world use
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); // Desabilitar señales en el uso de thread 


        /*
                curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");
                curl_easy_setopt(curl, CURLOPT_SSLCERT, certificado);
         */

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);

#ifdef DEBUG
        fprintf(stderr, "\n [comunicacion] Intento conectarme a: %s \n", conexion);
        fprintf(stderr, "\n [comunicacion] Post: %s \n", post);
#endif

        res = curl_easy_perform(curl);

        /* Limpiar */
        curl_easy_cleanup(curl);

    }

    return (int) res;
}

int escribir_datos(void *ptr, size_t size, size_t nmemb, void *ctx) {
    postdata *cbc = ctx;

    if (cbc->body_pos + size * nmemb > cbc->body_size) {
        return 0;
        /* overflow */
    }



    memcpy(&cbc->data[cbc->body_pos], ptr, size * nmemb);
    cbc->body_pos += size * nmemb;
    return size * nmemb;
}

size_t leer_datos(void *ptr, size_t size, size_t nmemb, void *stream) {
    int written = 0;
    if (stream) {
        postdata *ud = (postdata*) stream;

        int available = (ud->body_size - ud->body_pos);

        if (available > 0) {
            written = menor(size * nmemb, available);
            memcpy(ptr, ((char*) (ud->data)) + ud->body_pos, written);
            ud->body_pos += written;
            return written;
        }
    }

    return 0;
}

int menor(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

char* comunicar(char* servidor, int puerto, char *url, char* enviar, int verificar_ssl) {
    CURL *curl;
    CURLcode res;

    char* conexion;
    char* respuesta;
    char datos[4096];
    int tamano = 4096;
    postdata cbc;
    cbc.data = datos;
    cbc.body_size = tamano;
    cbc.body_pos = 0;

    // Reservo espacio para el buffer del servidor
    conexion = (char *) calloc((strlen(servidor) + strlen(url) + 15), sizeof (char));

    sprintf(conexion, "%s:%d%s", servidor, puerto, url);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Sebastian.cl/1.0");
        curl_easy_setopt(curl, CURLOPT_URL, conexion);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, ""); // mantener cookies en memoria. 
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);

        if (verificar_ssl == 0) {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); // No verificar el certificar peer 
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0); // No verificar contra el host del cert
        }
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1); // rebotar a la siguiente página 
        curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1); // mimic real world use
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); // Desabilitar señales en el uso de thread 


        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 15L);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, enviar);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &escribir_datos);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &cbc);



        res = curl_easy_perform(curl);
#ifdef DEBUG
        fprintf(stderr, "\n [comunicacion] Salida: %d \n", res);
        fprintf(stderr, "\n [comunicacion] Intento conectarme a: %s \n", conexion);
        fprintf(stderr, "\n [comunicacion] Post: %s \n", enviar);
        fprintf(stderr, "\n [comunicacion] Recibo: %s-%d-%d", cbc.data, (int) strlen(cbc.data), (int) cbc.body_size);
#endif

        respuesta = (char*) calloc(strlen(cbc.data) + 1, sizeof (char));
        sprintf(respuesta, "%s", cbc.data);
        respuesta[strlen(cbc.data)] = '\0';

        /* Limpiar */
        curl_easy_cleanup(curl);

    }

    return respuesta;
}
