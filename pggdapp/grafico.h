/* 
 * File:   grafico.h
 * Author: Sebastián Salazar Molina <ssalazar@experti.cl>
 *
 * Created on April 28, 2014, 7:52 PM
 */

#ifndef GRAFICO_H
#define	GRAFICO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gd.h>
#include <gdfonts.h>
#include "comun.h"
#include "utils.h"

    void graficar(ventas_mensuales* ventas);

#ifdef	__cplusplus
}
#endif

#endif	/* GRAFICO_H */

