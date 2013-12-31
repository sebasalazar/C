#include "utils.h"

int print_time(void) {
    struct timeval tv;
    struct timezone tz;
    time_t t;
    gettimeofday(&tv, &tz);
    t = tv.tv_sec;

    struct tm timeinfoL;
    localtime_r(&t, &timeinfoL);

    printf("%.2d/%.2d/%.2d", timeinfoL.tm_year + 1900, timeinfoL.tm_mon + 1, timeinfoL.tm_mday);
    printf("%.2d:%.2d:%.2d.%.6d ", timeinfoL.tm_hour, timeinfoL.tm_min, timeinfoL.tm_sec, (int) tv.tv_usec);
    return (t);
}

char* str_now() {
    char* date_str = NULL;
    char text[128];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    memset(text, 0, sizeof (text));
    strftime(text, sizeof (text) - 1, "%Y-%m-%d %H:%M:%S", t);

    date_str = (char *) calloc(strlen(text) + 1, sizeof (char));
    sprintf(date_str, "%s", text);

    return date_str;
}

byte* get_data(char* data_file) {
    byte *buffer;
    FILE *pf;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char strtmp[16];

    if ((pf = fopen(data_file, "r")) == NULL) {
        perror("error en archivo");
        return NULL;
    }

    /*
    while ((read = getline(&line, &len, pf)) != -1) {
        buffer = (byte *) calloc(len / 3 + 3, sizeof (char));
        int nbyte = 0;
        int i;
        for (i = 0; i < strlen(line); i += 3) {
            if (line[i] == '\n') break;
            byte c = (isdigit(line[i + 1]) ? line[i + 1] - '0' : line[i + 1] - 'A' + 10)*16 + (isdigit(line[i + 2]) ? line[i + 2] - '0' : line[i + 2] - 'A' + 10);
            buffer[nbyte++] = c;
        }
    }
     */

    while ((read = getline(&line, &len, pf)) != -1) {
        buffer = (byte *) calloc(len / 3 + 3, sizeof (char));
        int nbyte = 0;
        int i;
        for (i = 0; i < strlen(line); i += 3) {
            if (line[i] == '\n') break;
            byte c = (isdigit(line[i + 1]) ? line[i + 1] - '0' : line[i + 1] - 'A' + 10)*16 + \
 (isdigit(line[i + 2]) ? line[i + 2] - '0' : line[i + 2] - 'A' + 10);
            buffer[2 + nbyte++] = c;
        }
        // sprintf(strtmp, "%.4d", nbyte);
        // fprintf(stderr, "enviando %s bytes\n", strtmp);
        // buffer[0] = ((strtmp[0] - '0') << 4) + ((strtmp[1] - '0') & 0x0F);
        // buffer[1] = ((strtmp[2] - '0') << 4) + ((strtmp[3] - '0') & 0x0F);
        buffer[0] = 0x02;
        buffer[1] = 17;
    }

    fclose(pf);
    return buffer;
}

char* hex2str(byte* hex, unsigned int len) {
    int i;
    unsigned long largo = len * 2;
    char *app;
    char *buf;
    app = (char *) calloc(4, sizeof (char));
    buf = (char *) calloc((largo + 1), sizeof (char));
    for (i = 0; i < len; i++) {
        sprintf(app, "%02x", (byte) hex[i]);
        strcat(buf, app);
    }
    buf[largo] = '\0';

    return buf;

}

byte* static_data() {
    byte *buffer;
    char* data = " 60 00 00 00 00 02 00 30 20 05 80 20 C4 10 03 00 00 00 00 00 00 65 00 00 00 01 00 00 21 01 09 00 36 59 00 20 60 33 33 33 33 2D 15 12 10 10 00 04 32 10 01 37 35 30 30 30 30 30 31 35 39 37 30 30 30 30 30 30 30 30 30 20 20 20 00 48 00 46 30 31 30 31 54 37 54 42 4E 4B 50 54 30 34 20 43 31 35 36 31 32 30 30 20 20 20 20 20 20 20 20 34 32 32 38 32 35 34 20 20 20 20 20 20 20 20 F8 03 1C F0 75 43 76 B5 00 70 00 10 31 30 30 30 30 30 30 30 30 30 00 56 31 34 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 C2 AE BD CD 00 00 00 00 \n";
    size_t len = 0;
    ssize_t read;

    buffer = (byte *) calloc(len / 3 + 3, sizeof (char));
    int nbyte = 0;
    int i;
    for (i = 0; i < strlen(data); i += 3) {
        if (data[i] == '\n') break;
        byte c = (isdigit(data[i + 1]) ? data[i + 1] - '0' : data[i + 1] - 'A' + 10)*16 + \
 (isdigit(data[i + 2]) ? data[i + 2] - '0' : data[i + 2] - 'A' + 10);
        buffer[2 + nbyte++] = c;
    }
    buffer[0] = 0x02;
    buffer[1] = 17;

    return buffer;
}
