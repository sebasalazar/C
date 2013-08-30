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

    typedef __sighandler_t sig_handler_t;

    void alarmar(int timeout, sig_handler_t funcion);
    void tranquilizar();


#ifdef	__cplusplus
}
#endif

#endif	/* ALARMA_H */

