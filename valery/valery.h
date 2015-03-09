/* 
 * File:   valery.h
 * Author: Sebastián Salazar Molina <sebasalazar@gmail.com>
 *
 * Created on 8 de marzo de 2015, 18:50
 */

#ifndef VALERY_H
#define	VALERY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


#ifdef __WIN32__
#include <windows.h>
#include <winbase.h>
#else
#include <unistd.h>
#endif	

    int obtener_par(int limite_inferior, int limite_superior);
    int obtener_impar(int limite_inferior, int limite_superior);

    void lleno_pares(int* arreglo, int cantidad);
    void lleno_impares(int* arreglo, int cantidad);

    int existe(int numero, int* arreglo, int tamano);

    
#ifdef	__cplusplus
}
#endif

#endif	/* VALERY_H */

