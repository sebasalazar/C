#include "tareas.h"
#include "utils.h"

ramo *consultar_asignatura(char* asignatura) {
    ramo *r = NULL;
    char sql[512];
    int num = 0;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;

    if (strlen(asignatura) > 0) {
        r = (ramo *) malloc(sizeof (ramo));
        r->asignatura = (char *) calloc(strlen(asignatura) + 1, sizeof (asignatura));
        r->aprobacion = 0.0;
        r->reprobacion = 0.0;
        r->promedio = 0.0;
        r->stddev = 0.0;
        sprintf(r->asignatura, "%s", asignatura);

        // Busco Reprobados
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT AVG(nota) FROM asignaturas_cursadas WHERE curso_id IN (SELECT curso_id FROM cursos WHERE UPPER(asignatura) = UPPER('%s')) AND nota < 4", asignatura);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                r->reprobacion = getDouble(dbresult(resultado, 0, 0));
                dbfree(resultado);
            }
            dbclose(conexion);
        }

        // Busco Aprobados
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT AVG(nota) FROM asignaturas_cursadas WHERE curso_id IN (SELECT curso_id FROM cursos WHERE UPPER(asignatura) = UPPER('%s')) AND nota >= 4", asignatura);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                r->aprobacion = getDouble(dbresult(resultado, 0, 0));
                dbfree(resultado);
            }
            dbclose(conexion);
        }

        // Busco Promedio
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT AVG(nota), STDDEV(nota) FROM asignaturas_cursadas WHERE curso_id IN (SELECT curso_id FROM cursos WHERE UPPER(asignatura) = UPPER('%s'))", asignatura);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                r->promedio = getDouble(dbresult(resultado, 0, 0));
                r->stddev = getDouble(dbresult(resultado, 0, 1));
                dbfree(resultado);
            }
            dbclose(conexion);
        }
    }

    return r;
}

profesor *consultar_docente(long docente_id) {
    profesor *p = NULL;
    char sql[512];
    int num = 0;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;

    if (docente_id > 0) {
        p = (profesor *) malloc(sizeof (profesor));
        p->docente_id = docente_id;
        p->aprobacion = 0.0;
        p->promedio = 0.0;
        p->reprobacion = 0.0;
        p->stddev = 0.0;

        // Busco Reprobados
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT AVG(asignaturas_cursadas.nota) FROM cursos INNER JOIN asignaturas_cursadas ON cursos.curso_id=asignaturas_cursadas.curso_id WHERE cursos.docente_id = '%ld' AND asignaturas_cursadas.nota < 4 GROUP BY cursos.docente_id", docente_id);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                p->reprobacion = getDouble(dbresult(resultado, 0, 0));
                dbfree(resultado);
            }
            dbclose(conexion);
        }

        // Busco Aprobados
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT AVG(asignaturas_cursadas.nota) FROM cursos INNER JOIN asignaturas_cursadas ON cursos.curso_id=asignaturas_cursadas.curso_id WHERE cursos.docente_id = '%ld' AND asignaturas_cursadas.nota >= 4 GROUP BY cursos.docente_id", docente_id);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                p->aprobacion = getDouble(dbresult(resultado, 0, 0));
                dbfree(resultado);
            }
            dbclose(conexion);
        }

        // Busco Promedio
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT AVG(asignaturas_cursadas.nota) AS promedio, STDDEV(asignaturas_cursadas.nota) FROM cursos INNER JOIN asignaturas_cursadas ON cursos.curso_id=asignaturas_cursadas.curso_id WHERE cursos.docente_id = '%ld' GROUP BY cursos.docente_id ORDER BY promedio DESC", docente_id);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                p->promedio = getDouble(dbresult(resultado, 0, 0));
                p->stddev = getDouble(dbresult(resultado, 0, 1));
                dbfree(resultado);
            }
            dbclose(conexion);
        }
    }
    return p;
}

alumno *consultar_estudiante(long estudiante_id) {
    alumno *a = NULL;
    char sql[512];
    int num = 0;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;

    if (estudiante_id > 0) {
        a = (alumno *) malloc(sizeof (alumno));
        a->estudiante_id = estudiante_id;
        a->aprobacion = 0.0;
        a->mediana = 0.0;
        a->promedio = 0.0;
        a->reprobacion = 0.0;
        a->stddev = 0.0;

        // Busco Reprobados
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT AVG(nota) FROM asignaturas_cursadas WHERE estudiante_id='%ld' AND nota < 4", estudiante_id);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                a->reprobacion = getDouble(dbresult(resultado, 0, 0));
                dbfree(resultado);
            }
            dbclose(conexion);
        }

        // Busco Aprobados
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT AVG(nota) FROM asignaturas_cursadas WHERE estudiante_id='%ld' AND nota >= 4", estudiante_id);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                a->aprobacion = getDouble(dbresult(resultado, 0, 0));
                dbfree(resultado);
            }
            dbclose(conexion);
        }

        // Busco Promedio
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT AVG(nota), median(nota), STDDEV(nota) FROM asignaturas_cursadas WHERE estudiante_id='%ld'", estudiante_id);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                a->promedio = getDouble(dbresult(resultado, 0, 0));
                a->mediana = getDouble(dbresult(resultado, 0, 1));
                a->stddev = getDouble(dbresult(resultado, 0, 2));
                dbfree(resultado);
            }
            dbclose(conexion);
        }
    }

    return a;
}

alumno_ramo *consultar_asignatura_por_estudiante(long estudiante_id, long *tamano) {
    alumno_ramo *arreglo = NULL;
    char sql[512];
    char asignatura[128];
    int i = 0;
    int num = 0;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;

    if (estudiante_id > 0) {
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT cursos.asignatura, AVG(asignaturas_cursadas.nota), STDDEV(asignaturas_cursadas.nota) FROM cursos INNER JOIN asignaturas_cursadas ON cursos.curso_id=asignaturas_cursadas.curso_id WHERE estudiante_id='%ld' GROUP BY cursos.asignatura", estudiante_id);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                arreglo = (alumno_ramo *) malloc(num * sizeof (alumno_ramo));
                for (i = 0; i < num; i++) {
                    memset(asignatura, 0, sizeof (asignatura));
                    sprintf(asignatura, "%s", getString(dbresult(resultado, i, 0)));

                    arreglo[i].asignatura = (char *) calloc(strlen(asignatura) + 1, sizeof (char));
                    sprintf(arreglo[i].asignatura, "%s", asignatura);
                    arreglo[i].estudiante_id = estudiante_id;
                    arreglo[i].nota = getDouble(dbresult(resultado, i, 1));
                    arreglo[i].stddev = getDouble(dbresult(resultado, i, 2));
                }
                dbfree(resultado);
            }
            dbclose(conexion);
        }
    }


    *tamano = (long) num;
    return arreglo;
}

alumno_ramo *consultar_notas_por_estudiante(long estudiante_id, long *tamano) {
    alumno_ramo *arreglo = NULL;
    char sql[512];
    char asignatura[128];
    int i = 0;
    int num = 0;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;

    if (estudiante_id > 0) {
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT cursos.asignatura, asignaturas_cursadas.nota FROM cursos INNER JOIN asignaturas_cursadas ON cursos.curso_id=asignaturas_cursadas.curso_id WHERE estudiante_id='%ld' ORDER BY cursos.anio ASC, cursos.semestre ASC", estudiante_id);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                arreglo = (alumno_ramo *) malloc(num * sizeof (alumno_ramo));
                for (i = 0; i < num; i++) {
                    memset(asignatura, 0, sizeof (asignatura));
                    sprintf(asignatura, "%s", getString(dbresult(resultado, i, 0)));

                    arreglo[i].asignatura = (char *) calloc(strlen(asignatura) + 1, sizeof (char));
                    sprintf(arreglo[i].asignatura, "%s", asignatura);
                    arreglo[i].estudiante_id = estudiante_id;
                    arreglo[i].nota = getDouble(dbresult(resultado, i, 1));
                    arreglo[i].stddev = 0.0;
                }
                dbfree(resultado);
            }
            dbclose(conexion);
        }
    }


    *tamano = (long) num;
    return arreglo;
}

ranking_ramo *ranking_asignaturas(int semestre, int anio, long *tamano) {
    ranking_ramo *ranking = NULL;
    char sql[512];
    char asignatura[128];
    int i = 0;
    int num = 0;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;

    if (semestre > 0 && anio > 0) {
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT cursos.asignatura, AVG(asignaturas_cursadas.nota) AS promedio, STDDEV(asignaturas_cursadas.nota) FROM cursos INNER JOIN asignaturas_cursadas ON cursos.curso_id=asignaturas_cursadas.curso_id WHERE cursos.semestre='%d' AND cursos.anio='%d' GROUP BY cursos.asignatura ORDER BY promedio DESC", semestre, anio);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                ranking = (ranking_ramo *) malloc(num * sizeof (ranking_ramo));
                for (i = 0; i < num; i++) {
                    memset(asignatura, 0, sizeof (asignatura));
                    sprintf(asignatura, "%s", getString(dbresult(resultado, i, 0)));

                    ranking[i].lugar = i + 1;
                    ranking[i].asignatura = (char *) calloc(strlen(asignatura) + 1, sizeof (char));
                    sprintf(ranking[i].asignatura, "%s", asignatura);
                    ranking[i].nota = getDouble(dbresult(resultado, i, 1));
                    ranking[i].stddev = getDouble(dbresult(resultado, i, 2));
                    ranking[i].semestre = semestre;
                    ranking[i].anio = anio;
                }
                dbfree(resultado);
            }
            dbclose(conexion);
        }
    }
    *tamano = num;

    return ranking;
}

ranking_alumno *ranking_estudiantes(int semestre, int anio, long *tamano) {
    ranking_alumno *ranking = NULL;
    char sql[512];
    int i = 0;
    int num = 0;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;

    if (semestre > 0 && anio > 0) {
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT asignaturas_cursadas.estudiante_id, AVG(asignaturas_cursadas.nota) AS promedio, STDDEV(asignaturas_cursadas.nota) FROM cursos INNER JOIN asignaturas_cursadas ON cursos.curso_id=asignaturas_cursadas.curso_id WHERE cursos.semestre='%d' AND cursos.anio='%d' GROUP BY asignaturas_cursadas.estudiante_id ORDER BY promedio DESC", semestre, anio);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                ranking = (ranking_alumno *) malloc(num * sizeof (ranking_alumno));
                for (i = 0; i < num; i++) {
                    ranking[i].lugar = i + 1;
                    ranking[i].estudiante_id = getLong(dbresult(resultado, i, 0));
                    ranking[i].nota = getDouble(dbresult(resultado, i, 1));
                    ranking[i].stddev = getDouble(dbresult(resultado, i, 2));
                    ranking[i].semestre = semestre;
                    ranking[i].anio = anio;
                }
                dbfree(resultado);
            }
            dbclose(conexion);
        }
    }
    *tamano = num;

    return ranking;
}

ranking_profesor *ranking_docentes(int semestre, int anio, long *tamano) {
    ranking_profesor *ranking = NULL;
    char sql[512];
    int i = 0;
    int num = 0;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;

    if (semestre > 0 && anio > 0) {
        memset(sql, 0, sizeof (sql));
        sprintf(sql, "SELECT cursos.docente_id, AVG(asignaturas_cursadas.nota) AS promedio, STDDEV(asignaturas_cursadas.nota) FROM cursos INNER JOIN asignaturas_cursadas ON cursos.curso_id=asignaturas_cursadas.curso_id WHERE cursos.semestre='%d' AND cursos.anio='%d' GROUP BY cursos.docente_id ORDER BY promedio DESC", semestre, anio);
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                ranking = (ranking_profesor *) malloc(num * sizeof (ranking_profesor));
                for (i = 0; i < num; i++) {
                    ranking[i].lugar = i + 1;
                    ranking[i].docente_id = getLong(dbresult(resultado, i, 0));
                    ranking[i].nota = getDouble(dbresult(resultado, i, 1));
                    ranking[i].stddev = getDouble(dbresult(resultado, i, 2));
                    ranking[i].semestre = semestre;
                    ranking[i].anio = anio;
                }
                dbfree(resultado);
            }
            dbclose(conexion);
        }
    }
    *tamano = num;

    return ranking;
}

