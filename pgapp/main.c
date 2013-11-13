/* 
 * File:   main.c
 * Author: seba
 *
 * Created on November 11, 2013, 6:52 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "db.h"
#include "utils.h"
#include "tareas.h"

void prueba();

/*
 * 
 */
int main(int argc, char** argv) {
    ramo *asignatura = NULL;
    profesor *docente = NULL;
    alumno *estudiante = NULL;
    alumno_ramo *promedios = NULL;
    ranking_ramo *rkg_ramos = NULL;
    ranking_alumno *rkg_alumnos = NULL;
    int opcion = 0;
    int semestre = 0;
    int anio = 0;
    long i = 0;
    long cant_ramos = 0;
    long docente_id = 0;
    long estudiante_id = 0;
    char *cadena = NULL;

    do {
        limpiar();
        fprintf(stdout, "\n\t OPCIONES");
        fprintf(stdout, "\n1)\t Obtener nota de aprobacion y reprobacion por asignatura");
        fprintf(stdout, "\n2)\t Obtener promedio y desviacion estandar por asignatura");
        fprintf(stdout, "\n3)\t Obtener nota de aprobacion y reprobacion por docente");
        fprintf(stdout, "\n4)\t Obtener promedio y desviacion estandar por docente");
        fprintf(stdout, "\n5)\t Obtener nota de aprobacion y reprobacion por estudiante por asignatura");
        fprintf(stdout, "\n6)\t Obtener promedio y desviacion estandar por estudiante por asignatura");
        fprintf(stdout, "\n7)\t Obtener promedio, mediana y desviacion estandar por estudiante");
        fprintf(stdout, "\n8)\t Rankear Asignaturas por semestre y anio");
        fprintf(stdout, "\n9)\t Rankear Estudiantes por semestre y anio");
        fprintf(stdout, "\n10)\t Datos de Prueba");
        fprintf(stdout, "\n0)\t SALIR");

        fprintf(stdout, "\n Escojer opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                limpiar();
                cadena = leer_string("\nIngrese la asignatura: ");
                asignatura = consultar_asignatura(cadena);
                if (asignatura != NULL) {
                    if (asignatura->promedio >= 1) {
                        fprintf(stdout, "\nAsignatura: %s\t Aprobacion: %lf\t Reprobacion: %lf", asignatura->asignatura, asignatura->aprobacion, asignatura->reprobacion);
                    } else {
                        fprintf(stdout, "\nAsignatura %s no encontrada", cadena);
                    }
                    free(asignatura);
                } else {
                    fprintf(stdout, "\nSin datos");
                }
                free(cadena);
                pausa();
                break;

            case 2:
                limpiar();
                cadena = leer_string("\nIngrese la asignatura: ");
                asignatura = consultar_asignatura(cadena);
                if (asignatura != NULL) {
                    if (asignatura->promedio >= 1) {
                        fprintf(stdout, "\nAsignatura: %s\t Promedio: %lf\t Desviacion Estandar: %lf", asignatura->asignatura, asignatura->promedio, asignatura->stddev);
                    } else {
                        fprintf(stdout, "\nAsignatura %s no encontrada", cadena);
                    }
                    free(asignatura);
                } else {
                    fprintf(stdout, "\nSin datos");
                }
                free(cadena);
                pausa();
                break;

            case 3:
                limpiar();
                docente_id = leer_long("\nIngrese el id de Docente: ");
                docente = consultar_docente(docente_id);
                if (docente != NULL) {
                    if (docente->promedio >= 1) {
                        fprintf(stdout, "\nDocente id: %ld\t Aprobacion: %lf\t Reprobacion: %lf", docente->docente_id, docente->aprobacion, docente->reprobacion);
                    } else {
                        fprintf(stdout, "\nDocente %ld no tiene ramos", docente_id);
                    }
                    free(docente);
                } else {
                    fprintf(stdout, "\nSin datos");
                }
                pausa();
                break;

            case 4:
                limpiar();
                docente_id = leer_long("\nIngrese el id de Docente: ");
                docente = consultar_docente(docente_id);
                if (docente != NULL) {
                    if (docente->promedio >= 1) {
                        fprintf(stdout, "\nDocente id: %ld\t Promedio: %lf\t Desviacion Estandar: %lf", docente->docente_id, docente->promedio, docente->stddev);
                    } else {
                        fprintf(stdout, "\nDocente %ld no tiene ramos", docente_id);
                    }
                    free(docente);
                } else {
                    fprintf(stdout, "\nSin datos");
                }
                pausa();
                break;

            case 5:
                limpiar();
                estudiante_id = leer_long("\nIngrese el id de Estudiante: ");
                promedios = consultar_notas_por_estudiante(estudiante_id, &cant_ramos);
                if (promedios != NULL) {
                    for (i = 0; i < cant_ramos; i++) {
                        fprintf(stdout, "\nEstudiante id: %ld\t Asignatura: %s\t Nota: %lf", promedios[i].estudiante_id, promedios[i].asignatura, promedios[i].nota);
                    }
                    free(promedios);
                } else {
                    fprintf(stdout, "\nSin datos");
                }
                pausa();
                break;

            case 6:
                limpiar();
                estudiante_id = leer_long("\nIngrese el id de Estudiante: ");
                promedios = consultar_asignatura_por_estudiante(estudiante_id, &cant_ramos);
                if (promedios != NULL) {
                    for (i = 0; i < cant_ramos; i++) {
                        fprintf(stdout, "\nEstudiante id: %ld\t Asignatura: %s\t Promedio: %lf\t Desviacion Estandar: %lf", promedios[i].estudiante_id, promedios[i].asignatura, promedios[i].nota, promedios[i].stddev);
                    }
                    free(promedios);
                } else {
                    fprintf(stdout, "\nSin datos");
                }
                pausa();
                break;

            case 7:
                limpiar();
                estudiante_id = leer_long("\nIngrese el id de Estudiante: ");
                estudiante = consultar_estudiante(estudiante_id);
                if (estudiante != NULL) {
                    if (estudiante->promedio >= 1) {
                        fprintf(stdout, "\nEstudiante id: %ld\t Promedio: %lf\t Mediana: %lf\t Desviacion Estandar: %lf", estudiante->estudiante_id, estudiante->promedio, estudiante->mediana, estudiante->stddev);
                    } else {
                        fprintf(stdout, "\Estudiante %ld no tiene ramos", estudiante_id);
                    }
                    free(docente);
                } else {
                    fprintf(stdout, "\nSin datos");
                }
                pausa();
                break;

            case 8:
                limpiar();
                semestre = leer_int("\nIngrese el numero de semestre: ");
                anio = leer_int("\nIngrese el anio: ");
                rkg_ramos = ranking_asignaturas(semestre, anio, &cant_ramos);
                if (rkg_ramos) {
                    for (i = 0; i < cant_ramos; i++) {
                        fprintf(stdout, "\n Lugar: %ld\t Asignatura: %s\t Promedio: %lf\t Desviacion Estandar: %lf\t Semestre: %d\t Anio: %d", rkg_ramos[i].lugar, rkg_ramos[i].asignatura, rkg_ramos[i].nota, rkg_ramos[i].stddev, rkg_ramos[i].semestre, rkg_ramos[i].anio);
                    }
                    free(rkg_ramos);
                }
                pausa();
                break;

            case 9:
                limpiar();
                semestre = leer_int("\nIngrese el numero de semestre: ");
                anio = leer_int("\nIngrese el anio: ");
                rkg_alumnos = ranking_estudiantes(semestre, anio, &cant_ramos);
                if (rkg_alumnos) {
                    for (i = 0; i < cant_ramos; i++) {
                        fprintf(stdout, "\n Lugar: %ld\t Estudiante id: %d\t Promedio: %lf\t Desviacion Estandar: %lf\t Semestre: %d\t Anio: %d", rkg_alumnos[i].lugar, rkg_alumnos[i].estudiante_id, rkg_alumnos[i].nota, rkg_alumnos[i].stddev, rkg_alumnos[i].semestre, rkg_alumnos[i].anio);
                    }
                    free(rkg_alumnos);
                }
                pausa();
                break;

            case 10:
                limpiar();
                prueba();
                pausa();
                break;

            default:
                opcion = 0;
                break;
        }

    } while (opcion != 0);

    limpiar();
    fprintf(stdout, "\n\n\tSebastian Salazar Molina.\t @sebastian_sm \n");
    pausa();
    return (EXIT_SUCCESS);
}

void prueba() {
    ramo *asignatura = NULL;
    profesor *docente = NULL;
    alumno *estudiante = NULL;
    alumno_ramo *promedios = NULL;
    ranking_ramo *rkg_ramos = NULL;
    ranking_alumno *rkg_alumnos = NULL;
    ranking_profesor *rkg_profesores = NULL;
    long i = 0;
    long cant_ramos = 0;

    asignatura = consultar_asignatura("CALCULO I");
    if (asignatura != NULL) {
        fprintf(stdout, "\nAsignatura: %s Aprobacion: %lf Reprobacion: %lf Promedio: %lf Desviacion Estandar: %lf", asignatura->asignatura, asignatura->aprobacion, asignatura->reprobacion, asignatura->promedio, asignatura->stddev);
    }

    docente = consultar_docente(21);
    if (docente != NULL) {
        fprintf(stdout, "\nDocente id: %ld Aprobacion: %lf Reprobacion: %lf Promedio: %lf Desviacion Estandar: %lf", docente->docente_id, docente->aprobacion, docente->reprobacion, docente->promedio, docente->stddev);
        free(docente);
    }

    estudiante = consultar_estudiante(1221);
    if (estudiante != NULL) {
        fprintf(stdout, "\nEstudiante id: %ld Aprobacion: %lf Reprobacion: %lf Promedio: %lf Mediana: %lf Desviacion Estandar: %lf", estudiante->estudiante_id, estudiante->aprobacion, estudiante->reprobacion, estudiante->promedio, estudiante->mediana, estudiante->stddev);
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
            fprintf(stdout, "\n Lugar: %ld\t Asignatura: %s\t Promedio: %lf\t Desviacion Estandar: %lf\t Semestre: %d\t Anio: %d", rkg_ramos[i].lugar, rkg_ramos[i].asignatura, rkg_ramos[i].nota, rkg_ramos[i].stddev, rkg_ramos[i].semestre, rkg_ramos[i].anio);
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

    rkg_profesores = ranking_docentes(1, 2012, &cant_ramos);
    if (rkg_profesores) {
        for (i = 0; i < cant_ramos; i++) {
            fprintf(stdout, "\n Lugar: %ld\t Docente id: %d\t Promedio: %lf\t Desviacion Estandar: %lf\t Semestre: %d\t Anio: %d", rkg_profesores[i].lugar, rkg_profesores[i].docente_id, rkg_profesores[i].nota, rkg_profesores[i].stddev, rkg_profesores[i].semestre, rkg_profesores[i].anio);
        }
        free(rkg_profesores);
    }
}