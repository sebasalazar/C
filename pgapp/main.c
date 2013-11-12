/* 
 * File:   main.c
 * Author: seba
 *
 * Created on November 11, 2013, 6:52 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "db.h"
#include "utils.h"
#include "tareas.h"

/*
 * 
 */
int main(int argc, char** argv) {
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;
    ramo *asignatura = NULL;
    profesor *docente = NULL;
    alumno *estudiante = NULL;
    alumno_ramo *promedios = NULL;
    long i = 0;
    long cant_ramos = 0;

    conexion = dbconnect("146.83.181.4", 6432, "iswdb", "isw", "isw");
    resultado = dbquery(conexion, "SELECT NOW(), CAST(10 AS int)");
    fprintf(stdout, "\nAhora: %s # Diez: %d\n", getString(dbresult(resultado, 0, 0)), getInt(dbresult(resultado, 0, 1)));
    dbclose(conexion);

    asignatura = consultar_asignatura("CALCULO I");
    if (asignatura != NULL) {
        fprintf(stdout, "\nAsignatura: %s Aprobacion: %lf Reprobacion: %lf Promedio: %lf Desviacion Estandar: %lf\n", asignatura->asignatura, asignatura->aprobacion, asignatura->reprobacion, asignatura->promedio, asignatura->stddev);
    }

    docente = consultar_docente(21);
    if (docente != NULL) {
        fprintf(stdout, "\nDocente id: %ld Aprobacion: %lf Reprobacion: %lf Promedio: %lf Desviacion Estandar: %lf\n", docente->docente_id, docente->aprobacion, docente->reprobacion, docente->promedio, docente->stddev);
    }

    estudiante = consultar_estudiante(1221);
    if (estudiante != NULL) {
        fprintf(stdout, "\nEstudiante id: %ld Aprobacion: %lf Reprobacion: %lf Promedio: %lf Mediana: %lf Desviacion Estandar: %lf\n", estudiante->estudiante_id, estudiante->aprobacion, estudiante->reprobacion, estudiante->promedio, estudiante->mediana, estudiante->stddev);
    }

    promedios = consultar_asignatura_por_estudiante(1221, &cant_ramos);
    if (promedios != NULL) {
        fprintf(stdout, "\n Cantidad de ramos: %ld", cant_ramos);
        for (i = 0; i < cant_ramos; i++) {
            fprintf(stdout, "\nAsignatura %s Estudiante id: %ld Nota: %lf Desviacion Estandar: %lf", promedios[i].asignatura, promedios[i].estudiante_id, promedios[i].nota, promedios[i].stddev);
        }
    } else {
        fprintf(stdout, "\nNo hay asignaturas");
    }

    fprintf(stdout, "\n\n\tFin del programa\t -\t Sebastian Salazar Molina.\t @sebastian_sm\n");

    return (EXIT_SUCCESS);
}

