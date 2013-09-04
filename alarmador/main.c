/* 
 * File:   main.c
 * Author: seba
 *
 * Created on August 30, 2013, 5:16 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "alarma.h"

/*
 * 
 */
int main(int argc, char** argv) {

    alarmar(5);
#ifdef __WIN32__
    fprintf(stderr,"\nThread id: %d", GetCurrentThreadId());
    Sleep(10 * 1000);
#else
    sleep(10);
#endif
    tranquilizar();

    if (is_alarmado() != 0) {
        fprintf(stderr, "\nSe gatillo la alarma\n");
    } else {
        fprintf(stderr, "\nNormal\n");
    }

    return (EXIT_SUCCESS);
}


