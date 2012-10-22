/**
 * @file main.c
 * @author Sebastián Salazar Molina <sebasalazar@gmail.com>
 */
#include <stdio.h>

#include "comunicacion.h"
#include <stdlib.h>

/*
 * Pequeño programa para ocupar Curl en C
 */
int main(int argc, char** argv) {

    fprintf(stdout, "\nEjemplo de uso Curl en C\n\t\tDesarrollado por Sebastian Salazar Molina\n");
    char* mensaje = "var=seba";
    fprintf(stdout, "\nMensaje Enviado: %s\n", mensaje);
    char* respuesta = comunicar("https://sebastian.cl", 443, "/~seba/seba_curl.php", mensaje, 0);
    if (respuesta != NULL) {
        fprintf(stderr, "\nRespuesta : %s\n", respuesta);
    } else {
        fprintf(stderr, "\nError de Comunicacion.");
    }

    return (EXIT_SUCCESS);
}

