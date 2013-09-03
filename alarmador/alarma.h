/* 
 * @file:   alarma.h
 * @author: Sebastián Salazar Molina <ssalazar@orangepeople.cl>
 *
 */

#ifndef ALARMA_H
#define	ALARMA_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


#ifdef __WIN32__
#include <windows.h>
#else
#include <unistd.h>
#endif	

#ifdef __WIN32__
    static unsigned int wintimer;
    void CALLBACK alarma(UINT uTimerID, UINT info, DWORD dwUser, DWORD dw1, DWORD dw2);
#else
    void alarma();
#endif

    static int genero_alarma = 0;

    void alarmar(int timeout);
    void tranquilizar();
    int is_alarmado();


#ifdef	__cplusplus
}
#endif

#endif	/* ALARMA_H */

