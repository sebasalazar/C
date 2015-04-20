/* 
 * File:   ip_utils.h
 * Author: Sebastián Salazar Molina <sebasalazar@gmail.com>
 *
 * Created on 20 de abril de 2015, 1:53
 */

#ifndef IP_UTILS_H
#define	IP_UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

    /**
     * Transforma una ipv4 en un número
     * @param ip 
     * @return el número correspondiente
     */
    unsigned long ip2numero(char *ip);

    /**
     * Transforma un número en una ipv4
     * @param numero
     * @return la representación con puntos de la ip
     */
    char* numero2ip(unsigned long numero);

    /**
     * Determina si es una ipv4
     * @param ip representación con puntos de la ip
     * @return 1 si es una ipv4 o 0 en cualquier otro caso
     */
    int es_ipv4(char *ip);

    /**
     * Determina la cantidad de equipos que están en la red según el cidr dado
     * @param cidr
     * @return el número de ip de dicha red
     */
    unsigned long cantidad_direcciones(int cidr);
#ifdef	__cplusplus
}
#endif

#endif	/* IP_UTILS_H */

