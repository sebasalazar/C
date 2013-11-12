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
#include "utils.h"
#include "db.h"

    typedef struct {
        char* asignatura;
        double aprobacion;
        double reprobacion;
        double promedio;
        double stddev;
    } ramo;

    typedef struct {
        long docente_id;
        double aprobacion;
        double reprobacion;
        double promedio;
        double stddev;
    } profesor;

    typedef struct {
        long estudiante_id;
        double aprobacion;
        double reprobacion;
        double promedio;
        double mediana;
        double stddev;
    } alumno;

    typedef struct {
        char* asignatura;
        long estudiante_id;
        double nota;
        double stddev;
    } alumno_ramo;


    ramo *consultar_asignatura(char* asignatura);
    profesor *consultar_docente(long docente_id);
    alumno *consultar_estudiante(long estudiante_id);
    alumno_ramo *consultar_asignatura_por_estudiante(long estudiante_id, long *tamano);

#ifdef	__cplusplus
}
#endif

#endif	/* TAREAS_H */

