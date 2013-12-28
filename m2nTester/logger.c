#include "logger.h"

void logger(FILE* archivo, int nivel, char* mensaje) {
    pthread_mutex_lock(&mutex);

    if (archivo != NULL) {
        char texto[1024];
        char nivel_str[20];

        if (nivel == INFO_LOG) {
            sprintf(nivel_str, "INFO");
        } else if (nivel == ERROR_LOG) {
            sprintf(nivel_str, "ERROR");
        } else {
            sprintf(nivel_str, "DEBUG");
        }

        memset(texto, 0, sizeof (texto));
        snprintf(texto, 1023, "[%s] [\t%s\t] [%ld] %s", str_now(), nivel_str, (long) pthread_self(), mensaje);

        fprintf(archivo, "%s\n", texto);
    }
    pthread_mutex_unlock(&mutex);
}
