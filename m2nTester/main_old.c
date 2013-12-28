#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

#include "logger.h"
#include "utils.h"

int main(int argc, char **argv) {
    int tout;

    initialize_log();
    
    if (argc < 4) {
        printf("ERROR\nuse: sendf FILE_SEND FILE_RECV IP PORT\n");
        logger(DEBUG_LOG,"Error de uso");
        exit(1);
    }

    printf("File Send = %s\nFile Recv  = %s\nIP     = %s\nPort     = %s\n", argv[1], argv[2], argv[3], argv[4]);
    printf("argc = %d\n", argc);
    if (argc == 6) {
        tout = atoi(argv[5]);
    } else {
        tout = 5;
    }
    printf("time out %d seg\n", tout);


    // Server Begin
    FILE *pf;
    FILE *pf2;
    if ((pf = fopen(argv[1], "r")) == NULL) {
        perror("error en archivo");
        exit(1);
    }

    if ((pf2 = fopen(argv[2], "w")) == NULL) {
        perror("error en archivo");
        exit(1);
    }

    char * line = NULL;
    unsigned char *buffer;
    char strtmp[16];
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, pf)) != -1) {


        buffer = (unsigned char *) calloc(len / 3 + 3, sizeof (char));
        int nbyte = 0;
        int i;
        for (i = 0; i < strlen(line); i += 3) {
            if (line[i] == '\n') break;
            unsigned char c = (isdigit(line[i + 1]) ? line[i + 1] - '0' : line[i + 1] - 'A' + 10)*16 + \
 (isdigit(line[i + 2]) ? line[i + 2] - '0' : line[i + 2] - 'A' + 10);
            buffer[nbyte++] = c;
        }
        sprintf(strtmp, "%.4d", nbyte);
        fprintf(stderr, "enviando %s bytes\n", strtmp);
        fwrite(buffer, nbyte, 1, pf2);
    }



    fclose(pf);
    fclose(pf2);

    return EXIT_SUCCESS;
}
