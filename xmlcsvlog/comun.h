/* 
 * File:   comun.h
 * Author: Sebastián Salazar Molina <sebasalazar@gmail.com>
 *
 * Created on 20 de abril de 2015, 1:00
 */

#ifndef COMUN_H
#define	COMUN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <string.h>
    
    /**
     * Estructura de base de datos simple
     */
    typedef struct {
        char* llave;
        char* valor;
    } bd;

#ifdef	__cplusplus
}
#endif

#endif	/* COMUN_H */

