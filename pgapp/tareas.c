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
    return p;
}

alumno *consultar_estudiante(long estudiante_id) {
    alumno *a = NULL;
    return a;
}
