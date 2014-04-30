/* 
 * File:   tareas.h
 * Author: Sebastián Salazar Molina <sebasalazar@gmail.com>
 *
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
#include "utils.h"


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

