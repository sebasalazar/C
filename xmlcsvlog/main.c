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

    char *ip = calloc(16, sizeof (char));
    sprintf(ip,"%s", "127.0.0.1");
    unsigned int numero = ip2numero(ip);

    printf("\n %d %s \n", numero, numero2ip(numero));

    return (EXIT_SUCCESS);
}

