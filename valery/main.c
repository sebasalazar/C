/* 
 * File:   main.c
 * Author: seba
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "valery.h"

/*
 * 
 */
int main(int argc, char** argv) {

    int *pares, *impares;
    int tam_par = 0, tam_impar = 0;
    int i;
    time_t tiempo = time(NULL);
    srand(tiempo);

    if (tiempo % 5 == 0) {
        tam_par = 6;
        tam_impar = 4;
    } else if (tiempo % 7 == 0) {
        tam_par = 4;
        tam_impar = 6;
    } else {
        tam_par = 5;
        tam_impar = 5;
    }


    pares = (int *) malloc(tam_par * sizeof (int));
    impares = (int *) malloc(tam_impar * sizeof (int));
    lleno_pares(pares, tam_par);
    lleno_impares(impares, tam_impar);

    fprintf(stdout, "\n\t ARREGLO PARES: ");
    for (i = 0 ; i< tam_par; i++) {
        fprintf(stdout, "\t %d ", pares[i]);
    }
    fprintf(stdout, "\n");
    
    fprintf(stdout, "\t ARREGLO IMPARES: ");
    for (i = 0 ; i< tam_impar; i++) {
        fprintf(stdout, "\t %d ", impares[i]);
    }
    fprintf(stdout, "\n");

    return (EXIT_SUCCESS);
}


