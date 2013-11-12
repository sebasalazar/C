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
    ranking_ramo *rkg_ramos = NULL;
    ranking_alumno *rkg_alumnos = NULL;
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
        free(docente);
    }

    estudiante = consultar_estudiante(1221);
    if (estudiante != NULL) {
        fprintf(stdout, "\nEstudiante id: %ld Aprobacion: %lf Reprobacion: %lf Promedio: %lf Mediana: %lf Desviacion Estandar: %lf\n", estudiante->estudiante_id, estudiante->aprobacion, estudiante->reprobacion, estudiante->promedio, estudiante->mediana, estudiante->stddev);
        free(estudiante);
    }

    promedios = consultar_asignatura_por_estudiante(1221, &cant_ramos);
    if (promedios != NULL) {
        fprintf(stdout, "\n Cantidad de ramos: %ld", cant_ramos);
        for (i = 0; i < cant_ramos; i++) {
            fprintf(stdout, "\nAsignatura %s Estudiante id: %ld Nota: %lf Desviacion Estandar: %lf", promedios[i].asignatura, promedios[i].estudiante_id, promedios[i].nota, promedios[i].stddev);
        }
        free(promedios);
    }


    promedios = consultar_notas_por_estudiante(847, &cant_ramos);
    if (promedios != NULL) {
        fprintf(stdout, "\n Cantidad de ramos: %ld", cant_ramos);
        for (i = 0; i < cant_ramos; i++) {
            fprintf(stdout, "\nAsignatura %s Estudiante id: %ld Nota: %lf Desviacion Estandar: %lf", promedios[i].asignatura, promedios[i].estudiante_id, promedios[i].nota, promedios[i].stddev);
        }
        free(promedios);
    }

    rkg_ramos = ranking_asignaturas(1, 2010, &cant_ramos);
    if (rkg_ramos) {
        for (i = 0; i < cant_ramos; i++) {
            fprintf(stdout, "\n Lugar: %ld Asignatura: %s Promedio: %lf Desviacion Estandar: %lf Semestre: %d Anio: %d", rkg_ramos[i].lugar, rkg_ramos[i].asignatura, rkg_ramos[i].nota, rkg_ramos[i].stddev, rkg_ramos[i].semestre, rkg_ramos[i].anio);
        }
        free(rkg_ramos);
    }

    rkg_alumnos = ranking_estudiantes(1, 2011, &cant_ramos);
    if (rkg_alumnos) {
        for (i = 0; i < cant_ramos; i++) {
            fprintf(stdout, "\n Lugar: %ld\t Estudiante id: %d\t Promedio: %lf\t Desviacion Estandar: %lf\t Semestre: %d\t Anio: %d", rkg_alumnos[i].lugar, rkg_alumnos[i].estudiante_id, rkg_alumnos[i].nota, rkg_alumnos[i].stddev, rkg_alumnos[i].semestre, rkg_alumnos[i].anio);
        }
        free(rkg_alumnos);
    }

    fprintf(stdout, "\n\n\tFin del programa\t -\t Sebastian Salazar Molina.\t @sebastian_sm\n");

    return (EXIT_SUCCESS);
}

