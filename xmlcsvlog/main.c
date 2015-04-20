/* 
 * File:   main.c
 * Author: Sebastián Salazar Molina <sebasalazar@gmail.com>
 *
 * Created on 20 de abril de 2015, 0:49
 */

#include <stdio.h>
#include <stdlib.h>
#include "ip_utils.h"

/*
 * 
 */
int main(int argc, char** argv) {

    unsigned long i;
    char *ip = calloc(16, sizeof (char));
    unsigned long numero = 0;
    unsigned long total = 0;

    
    sprintf(ip, "%s", "146.83.0.0");
    numero = ip2numero(ip);
    total = cantidad_direcciones(16);
    
    printf("\n%ld %ld\n", numero, total);
    
    for (i = numero; i < (numero + total); i++) {
        printf("%s\n", numero2ip(i));
    }

    return (EXIT_SUCCESS);
}

