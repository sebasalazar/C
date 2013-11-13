#include "utils.h"

#ifdef __WIN32__

void limpiar(void) {
    system("cls");
}

void pausa(void) {
    fprintf(stdout, "\n");
    system("pause");
}

#else

void limpiar(void) {
    system("clear");
}

void pausa(void) {
    int hack = 0;
    do {
        fflush(stdin);
        hack = fgetc(stdin);
        fflush(stdout);
    } while (hack != EOF && hack != '\n');

    fprintf(stdout, "\nPresione enter para continuar...\n");
    getchar();
}
#endif                          /* POSIX */

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

char* leer_string(char *label) {
    char *resultado = NULL;
    char buffer[512];
    int largo = 0;

    memset(buffer, 0, sizeof (buffer));
    fprintf(stdout, "\n\t%s", label);
    fflush(NULL);
    getchar();
    fgets(buffer, sizeof (buffer), stdin);

    largo = strlen(buffer);
    if (largo > 0 && buffer[largo - 1] == '\n') {
        buffer[largo - 1] = '\0';
    }

    resultado = (char *) calloc(strlen(buffer), sizeof (char));
    sprintf(resultado, "%s", buffer);

    return resultado;
}

long leer_long(char *label) {
    long resultado = 0;

    fprintf(stdout, "\n\t%s", label);
    scanf("%ld", &resultado);

    return resultado;
}

int leer_int(char *label) {
    int resultado = 0;

    fprintf(stdout, "\n\t%s", label);
    scanf("%d", &resultado);

    return resultado;
}
