#include "socket.h"

ssize_t leer_socket(int sockd, void *vptr, size_t maxlen) {
    ssize_t n, rc;
    byte c;
    byte *buffer = (byte *) vptr;

    for (n = 1; n < maxlen; n++) {

        if ((rc = read(sockd, &c, 1)) == 1) {
            *buffer++ = c;
            if (c == '\n')
                break;
        } else if (rc == 0) {
            if (n == 1)
                return 0;
            else
                break;
        } else {
            if (errno == EINTR)
                continue;
            return -1;
        }
    }

    *buffer = NULL;
    return n;
}

ssize_t escribir_socket(int sockd, const void *vptr, size_t n) {
    size_t nleft;
    ssize_t nwritten;
    byte *buffer;

    buffer = (byte *) vptr;
    nleft = n;

    while (nleft > 0) {
        if ((nwritten = write(sockd, buffer, nleft)) <= 0) {
            if (errno == EINTR) {
                nwritten = 0;
            } else {
                return -1;
            }
        }
        nleft -= nwritten;
        buffer += nwritten;
    }

    return n;
}
