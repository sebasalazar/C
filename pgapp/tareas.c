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
    return a;
}
