#include "utils.h"

char* hex2str(byte* hex, unsigned int len) {
    int i;
    unsigned long largo = len * 2;
    char *app;
    char *buf;
    app = (char *) malloc(sizeof (char *));
    buf = (char *) malloc((largo + 1) * sizeof (char *));
    strcpy(buf, "");
    for (i = 0; i < largo; i++) {
        sprintf(app, "%02x", (byte) hex[i]);
        strcat(buf, app);
    }
    buf[largo] = '\0';

    return buf;

}

long fsize(FILE * file) {
    if (fseek(file, 0, SEEK_END)) {
        return -1;
    }

    long size = ftell(file);
    if (size < 0) {
        return -1;
    }

    if (fseek(file, 0, SEEK_SET)) {
        return -1;
    }

    return size;
}

size_t leer_archivo(char ** str, const char * name, _Bool * error) {
    FILE * file = NULL;
    size_t read = 0;
    *str = NULL;
    if (error) {
        *error = 1;
    }

    do {
        file = fopen(name, "rb");
        if (!file) {
            break;
        }

        long size = fsize(file);
        if (size < 0) {
            break;
        }

        if (error) {
            *error = 0;
        }

        *str = malloc((size_t) size + 1);
        if (!*str) break;

        read = fread(*str, 1, (size_t) size, file);
        (*str)[read] = 0;
        *str = realloc(*str, read + 1);

        if (error) {
            *error = (size != (long) read);
        }
    } while (0);

    if (file) {
        fclose(file);
    }
    return read;
}
