/* 
 * File:   main.c
 * Author: seba
 *
 * Created on 28 de diciembre de 2013, 02:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "logger.h"
#include "utils.h"

struct arg_struct {
    byte* datos;
    char* archivo_salida;
    char* ip;
    int puerto;
    int timeout;
};

void *procesar(void* args);

/*
 * 
 */
int main(int argc, char** argv) {
    unsigned long u = 0;
    unsigned long usuarios = 0;
    struct arg_struct argumentos;
    int tout = 5;

    initialize_log();

    if (argc < 5) {
        printf("ERROR\nuse: %s USUARIOS_CONCURRENTES FILE_SEND FILE_RECV IP PORT\n", argv[0]);
        logger(DEBUG_LOG, "Error de uso");
        exit(1);
    }

    printf("File Send = %s\nFile Recv  = %s\nIP     = %s\nPort     = %s\n", argv[1], argv[2], argv[3], argv[4]);
    printf("argc = %d\n", argc);
    if (argc == 7) {
        tout = atoi(argv[6]);
    }
    printf("time out %d seg\n", tout);


    usuarios = atoi(argv[1]);
    pthread_t hilos[usuarios];

    argumentos.datos = get_data(argv[2]);
    argumentos.ip = (char *) calloc(strlen(argv[4]) + 1, sizeof (char));
    sprintf(argumentos.ip, "%s", argv[4]);
    argumentos.puerto = atoi(argv[5]);
    argumentos.timeout = tout;

    for (u = 0; u < usuarios; u++) {
        logger(INFO_LOG, "Creando hilo");
        if (pthread_create(&hilos[u], NULL, &procesar, (void *) &argumentos) != 0) {
            logger(ERROR_LOG, "Error al crear hilo");
            return -1;
        }
    }

    for (u = 0; u < usuarios; u++) {
        pthread_join(hilos[u], NULL);
        logger(INFO_LOG, "Cerrando hilo");
    }

    pthread_exit(NULL);

    return (EXIT_SUCCESS);
}

void *procesar(void *arguments) {
    struct arg_struct *args = arguments;

    logger(INFO_LOG, "Procesando");

    int tamano = sizeof (args->datos);
    char* datos = hex2str(args->datos, tamano);

    logger(DEBUG_LOG, datos);
}
