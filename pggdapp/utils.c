/* 
 * File:   utils.c
 * Author: Sebastián Salazar Molina <sebasalazar@gmail.com>
 *
 */

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
    //    getchar();
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

char* ahora() {
    char* fecha = NULL;
    time_t ts = time(NULL);
    struct tm *tiempo = localtime(&ts);

    fecha = (char *) calloc(129, sizeof (char));

    int dia = tiempo->tm_mday;
    int mes = tiempo->tm_mon + 1; // Mes de 0 - 11
    int anio = tiempo->tm_year + 1900;
    int hora = tiempo->tm_hour;
    int min = tiempo->tm_min;
    int seg = tiempo->tm_sec;

    snprintf(fecha, 128, "%02d/%02d/%04d %02d:%02d:%02d", dia, mes, anio, hora, min, seg);
    return fecha;
}

int color_aleatoreo() {
    return rand() % 256;
}

char* etiquetaMes(int num) {
    if (num == 1) {
        return "Ene";
    } else if (num == 2) {
        return "Feb";
    } else if (num == 3) {
        return "Mar";
    } else if (num == 4) {
        return "Abr";
    } else if (num == 5) {
        return "May";
    } else if (num == 6) {
        return "Jun";
    } else if (num == 7) {
        return "Jul";
    } else if (num == 8) {
        return "Ago";
    } else if (num == 9) {
        return "Sep";
    } else if (num == 10) {
        return "Oct";
    } else if (num == 11) {
        return "Nov";
    } else if (num == 12) {
        return "Dic";
    } else {
        return "";
    }
}

char* longStr(long num) {
    char* texto = NULL;
    // Esto se puede hacer mejor, pero no hace daño
    texto = (char *) calloc(65, sizeof (char *));
    snprintf(texto, 64, "%ld", num);
    return texto;
}

