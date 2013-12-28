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
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "logger.h"
#include "utils.h"
#include "socket.h"

struct arg_struct {
    FILE *log;
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
    long u = 0;
    long usuarios = 0;
    struct arg_struct argumentos;
    int tout = 5;
    FILE *archivo = fopen("m2nTester.log", "a+");

    if (archivo == NULL) {
        printf("No se puede abrir archivo log");
        exit(1);
    }

    if (argc < 5) {
        printf("ERROR\nuse: %s USUARIOS_CONCURRENTES FILE_SEND FILE_RECV IP PORT\n", argv[0]);
        logger(archivo, DEBUG_LOG, "Error de uso");
        exit(1);
    }



    printf("File Send = %s\nFile Recv  = %s\nIP     = %s\nPort     = %s\n", argv[2], argv[3], argv[4], argv[5]);
    printf("argc = %d\n", argc);
    if (argc == 7) {
        tout = atoi(argv[6]);
    }
    printf("time out %d seg\n", tout);


    usuarios = (long) atol(argv[1]);
    pthread_t hilos[usuarios];

    argumentos.log = archivo;
    argumentos.datos = get_data(argv[2]);
    argumentos.ip = (char *) calloc(strlen(argv[4]) + 1, sizeof (char));
    sprintf(argumentos.ip, "%s", argv[4]);
    argumentos.puerto = atoi(argv[5]);
    argumentos.timeout = tout;

    for (u = 0; u < usuarios; u++) {
        logger(archivo, INFO_LOG, "Creando hilo");
        if (pthread_create(&hilos[u], NULL, &procesar, (void *) &argumentos) != 0) {
            logger(archivo, ERROR_LOG, "Error al crear hilo");
            return -1;
        }
    }

    for (u = 0; u < usuarios; u++) {
        pthread_join(hilos[u], NULL);
        logger(archivo, INFO_LOG, "Cerrando hilo");
    }

    fclose(archivo);
    pthread_exit(NULL);

    return (EXIT_SUCCESS);
}

void *procesar(void *arguments) {
    struct sockaddr_in servidor;
    struct arg_struct *args = arguments;
    byte *respuesta;
    char buffer[512];

    memset(&servidor, 0, sizeof (servidor));
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = inet_addr(args->ip);
    servidor.sin_port = htons(args->puerto);

    int fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (connect(fd, (struct sockaddr *) &servidor, sizeof (servidor))) {
        int largo = (sizeof (args->datos) + 1);
        respuesta = (byte *) malloc(sizeof (byte) * largo);
        memset(respuesta, 0, largo);

        int es = escribir_socket(fd, args->datos, largo - 1);
        int ls = leer_socket(fd, respuesta, sizeof (respuesta));

        memset(buffer, 0, sizeof (buffer));
        sprintf(buffer, "envio: %s %d # recibo: %s %d", hex2str(args->datos, largo - 1), es, hex2str(respuesta, sizeof (respuesta)), ls);

        logger(args->log, DEBUG_LOG, buffer);
    }


    return NULL;
}
