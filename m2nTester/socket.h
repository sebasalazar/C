#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>    /*  for ssize_t data type  */
#include <errno.h>
#include "utils.h"

#define LISTENQ        (1024)   /*  Backlog for listen()   */


/*  Function declarations  */

ssize_t leer_socket(int fd, void *vptr, size_t maxlen);
ssize_t escribir_socket(int fc, const void *vptr, size_t maxlen);


#endif  /*  SOCKET_H  */

