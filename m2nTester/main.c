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
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "logger.h"
#include "utils.h"

struct arg_struct {
    FILE *log;
    byte* datos;
    int largo_datos;
    char* archivo_salida;
    int timeout;
    int repeticiones;
    struct sockaddr_in servidor;
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
    char* ip;
    int puerto;
    int repeticiones = 1;

    FILE *archivo = fopen("m2nTester.log", "a+");

    if (archivo == NULL) {
        printf("No se puede abrir archivo log");
        exit(1);
    }

    if (argc < 5) {
        printf("ERROR\nuse: %s USUARIOS_CONCURRENTES REPETICIONES IP PORT\n", argv[0]);
        logger(archivo, DEBUG_LOG, "Error de uso");
        exit(1);
    }


    printf("IP     = %s\nPort     = %s\n", argv[3], argv[4]);
    printf("argc = %d\n", argc);
    if (argc == 6) {
        tout = atoi(argv[5]);
    }
    printf("time out %d seg\n", tout);


    usuarios = (long) atol(argv[1]);
    pthread_t hilos[usuarios];

    ip = (char *) calloc(strlen(argv[3]) + 1, sizeof (char));
    sprintf(ip, "%s", argv[3]);
    puerto = atoi(argv[4]);

    repeticiones = atoi(argv[2]);
    if (repeticiones > 255) {
        repeticiones = 256;
    }

    struct hostent* hostname = gethostbyname(ip);
    argumentos.servidor.sin_family = AF_INET;
    argumentos.servidor.sin_port = htons(puerto);
    bcopy((char *) hostname->h_addr, (char *) &(argumentos.servidor.sin_addr.s_addr), hostname->h_length);

    argumentos.log = archivo;
    argumentos.datos = static_data();
    argumentos.largo_datos = 217;
    argumentos.timeout = tout;
    argumentos.repeticiones = repeticiones;


    for (u = 0; u < usuarios; u++) {
        logger(archivo, INFO_LOG, "Creando hilo");
        if (pthread_create(&hilos[u], NULL, &procesar, (void *) &argumentos) != 0) {
            logger(archivo, ERROR_LOG, "Error al crear hilo");
            // return -1;
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
    struct arg_struct *args = arguments;
    int sockfd, i;
    long datos_enviados = 0;
    long datos_recibidos = 0;
    struct timespec inicio, fin;
    double transcurrido;
    int ok = 0;
    FILE* csv;

    byte respuesta[512];
    char mensaje[512];

    for (i = 0; i < (args->repeticiones); i++) {
        datos_enviados = 0;
        datos_recibidos = 0;
        ok = 0;
        clock_gettime(CLOCK_MONOTONIC, &inicio);

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            logger(args->log, ERROR_LOG, "ERROR abriendo socket\n");
        } else {

            if (connect(sockfd, (struct sockaddr *) &(args->servidor), sizeof (args->servidor)) < 0) {
                logger(args->log, ERROR_LOG, "ERROR al conectar");
            } else {
                datos_enviados = send(sockfd, args->datos, args->largo_datos + 2, 0);
                if (datos_enviados <= 0) {
                    logger(args->log, ERROR_LOG, "ERROR escribiendo socket");
                } else {
                    char* enviado = hex2str(args->datos, datos_enviados);
                    memset(mensaje, 0, 512);
                    sprintf(mensaje, "Enviado %ld bytes %s", datos_enviados, enviado);
                    logger(args->log, DEBUG_LOG, mensaje);

                    datos_recibidos = read(sockfd, respuesta, datos_enviados);
                    if (datos_recibidos <= 0) {
                        logger(args->log, ERROR_LOG, "ERROR leyendo del socket");
                    } else {
                        char* salida = hex2str(respuesta, datos_recibidos + 1);
                        memset(mensaje, 0, 512);
                        sprintf(mensaje, "Recibido %ld bytes %s", datos_recibidos, salida);
                        logger(args->log, DEBUG_LOG, mensaje);
                        ok = 1;
                    }
                }
            }

            close(sockfd);
        }

        clock_gettime(CLOCK_MONOTONIC, &fin);
        transcurrido = fin.tv_sec - inicio.tv_sec;
        transcurrido += (fin.tv_nsec - inicio.tv_nsec) / 1000000000.0;

        csv = fopen("resultado.csv", "a+");
        if (csv != NULL) {
            fprintf(csv, "%s;%ld;%ld,%d;%lf\n", str_now(), datos_enviados, datos_recibidos, ok, transcurrido);
            fclose(csv);
        }
    }
    return NULL;
}

/*
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

    if (connect(fd, (struct sockaddr *) &servidor, sizeof (servidor)) != -1) {
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
 */
