/* 
 * @file:   alarma.c
 * @author: Sebastián Salazar Molina <ssalazar@orangepeople.cl>
 *
 */

#include "alarma.h"

void alarmar(int timeout, sig_handler_t funcion) {
#ifdef __WIN32__
    timeSetEvent((timeout * 1000), 10, funcion, 0, TIME_ONESHOT);
#else
    alarm(0);
    signal(SIGALRM, funcion);
    alarm(timeout);
#endif
}

void tranquilizar() {
#ifdef __WIN32__
#else
    alarm(0);
#endif
}

