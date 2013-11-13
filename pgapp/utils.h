/* 
 * File:   utils.h
 * Author: seba
 *
 * Created on November 12, 2013, 4:22 PM
 */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    void limpiar(void);
    void pausa(void);
    char* getString(char *texto);
    long getLong(char *texto);
    int getInt(char *texto);
    double getDouble(char *texto);
    char* leer_string(char *label);
    long leer_long(char *label);
    int leer_int(char *label);
#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */

