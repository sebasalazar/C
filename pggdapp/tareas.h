/* 
 * File:   tareas.h
 * Author: seba
 *
 * Created on 11 de noviembre de 2013, 11:20 PM
 */

#ifndef TAREAS_H
#define	TAREAS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "db.h"


    /**
     * num_tiendas  variables usada para almacenar la cantidad de tiendas.
     */
    char** getTiendas(int* num_tiendas);
    ventas_anuales* getVentasAnuales(int* cantidades_ventas);
    ventas_mensuales* getVentasMensuales(char* tienda, int* cantidades_ventas);
    ventas_horarias* getVentasHorarias(int* cantidades_ventas);

#ifdef	__cplusplus
}
#endif

#endif	/* TAREAS_H */

