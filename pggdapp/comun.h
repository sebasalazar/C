/* 
 * File:   comun.h
 * Author: Sebastián Salazar Molina <ssalazar@experti.cl>
 *
 * Created on April 29, 2014, 12:32 PM
 */

#ifndef COMUN_H
#define	COMUN_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SERVIDOR "sebastian.cl"
#define PUERTO 5432
#define NOMBREDB "iswdb"
#define USUARIODB "isw"
#define PASSDB "isw"

#define IMG_WIDTH 800
#define IMG_HEIGHT 600
#define IMG_BPP 24
    
#define BORDE_ANCHO 70
#define BORDE_ALTO 50

    typedef struct {
        char* tienda;
        long monto;
    } ventas_anuales;

    typedef struct {
        char* tienda;
        int mes;
        long monto;
    } ventas_mensuales;

    typedef struct {
        char* tienda;
        int hora;
        long monto;
    } ventas_horarias;



#ifdef	__cplusplus
}
#endif

#endif	/* COMUN_H */

