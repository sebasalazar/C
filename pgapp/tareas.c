#include "tareas.h"

ramo *consultar_asignatura(char* asignatura) {
    ramo *r = NULL;
    char sql[512];
    int num = 0;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;

    r = (ramo *) malloc(sizeof (ramo));
    r->asignatura = (char *) calloc(strlen(asignatura) + 1, sizeof (asignatura));
    r->aprobacion = 0.0;
    r->reprobacion = 0.0;
    r->promedio = 0.0;
    r->stddev = 0.0;
    sprintf(r->asignatura, "%s", asignatura);

    // Busco Reprobados
    memset(sql, 0, sizeof (sql));
    sprintf(sql, "SELECT AVG(nota) FROM asignaturas_cursadas WHERE curso_id IN (SELECT curso_id FROM cursos WHERE asignatura = '%s') AND nota < 4", asignatura);
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
    sprintf(sql, "SELECT AVG(nota) FROM asignaturas_cursadas WHERE curso_id IN (SELECT curso_id FROM cursos WHERE asignatura = '%s') AND nota >= 4", asignatura);
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
    sprintf(sql, "SELECT AVG(nota), STDDEV(nota) FROM asignaturas_cursadas WHERE curso_id IN (SELECT curso_id FROM cursos WHERE asignatura = '%s')", asignatura);
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
                    //                    arreglo = (alumno_ramo *) realloc(arreglo, (i + 1) * sizeof (alumno_ramo));

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
