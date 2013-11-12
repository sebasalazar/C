#include "utils.h"

char* getString(char *texto) {
    char* resultado = NULL;

    if (strlen(texto) > 0) {
        int tamano = strlen(texto) + 1;
        resultado = (char *) calloc(tamano, sizeof (char));

        sprintf(resultado, "%s", texto);
    }

    return resultado;
}

long getLong(char *texto) {
    long resultado = 0;
    if (strlen(texto) > 0) {
        sscanf(texto, "%ld", &resultado);
    }
    return resultado;
}

int getInt(char *texto) {
    int resultado = 0;
    if (strlen(texto) > 0) {
        sscanf(texto, "%d", &resultado);
    }
    return resultado;
}

double getDouble(char *texto) {
    double resultado = 0.0;
    if (strlen(texto) > 0) {
        sscanf(texto, "%lf", &resultado);
    }
    return resultado;
}

