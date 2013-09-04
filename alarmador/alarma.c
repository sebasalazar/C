/* 
 * @file:   alarma.c
 * @author: Sebastián Salazar Molina <ssalazar@orangepeople.cl>
 *
 */

#include "alarma.h"

#ifdef __WIN32__

void CALLBACK alarma(UINT uTimerID, UINT info, DWORD dwUser, DWORD dw1, DWORD dw2) {
    int thid = GetCurrentThreadId();
    fprintf(stderr, "\nThread Original: %d # Thread Actual: %d", dwUser, thid);

    genero_alarma = 1;
}
#else

void alarma() {
    genero_alarma = 1;
}

#endif

void alarmar(int timeout) {
#ifdef __WIN32__
    int thid = GetCurrentThreadId();
    wintimer = timeSetEvent((timeout * 1000), 10, alarma, thid, TIME_ONESHOT);
#else
    alarm(0);
    signal(SIGALRM, alarma);
    alarm(timeout);
#endif
}

void tranquilizar() {
#ifdef __WIN32__
    timeKillEvent(wintimer);
#else
    alarm(0);
#endif
}

int is_alarmado() {
    return genero_alarma;
}
