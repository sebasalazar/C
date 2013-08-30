/* 
 * File:   main.c
 * Author: seba
 *
 * Created on August 30, 2013, 5:16 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "alarma.h"

int genero_alarma = 0;
void alarma();

/*
 * 
 */
int main(int argc, char** argv) {

    alarmar(5, alarma);
#ifdef __WIN32__
    Sleep(10 * 1000);
#else
    sleep(10);
#endif
    tranquilizar();

    if (genero_alarma != 0) {
        fprintf(stderr, "\nSe gatilló la alarma\n");
    }

    return (EXIT_SUCCESS);
}

void alarma() {
    genero_alarma = 1;
}
