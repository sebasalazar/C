#include <string.h>

#include "db.h"

PGconn* dbconnect(char* servidor, int puerto, char* nombredb, char* usuario, char* password) {
    PGconn* conexion = NULL;

    char info[128];
    memset(info, 0, sizeof (info));
    sprintf(info, "host='%s' port='%d' dbname='%s' user='%s' password='%s'", servidor, puerto, nombredb, usuario, password);

    conexion = PQconnectdb(info);
    if (PQstatus(conexion) == CONNECTION_BAD) {
        fprintf(stderr, "\nError al conectar al servidor: %s", PQerrorMessage(conexion));
        conexion = NULL;
    }

    return conexion;
}

void dbclose(PGconn* conexion) {
    PQfinish(conexion);
}

PGresult* dbquery(PGconn* conexion, char* sql) {
    PGresult* resultado = NULL;

    if (strlen(sql) > 10) {
        resultado = PQexec(conexion, sql);
    }

    return resultado;
}

long dbnumrows(PGresult *res) {
    long resultado = 0;
    char *tuplas = NULL;
    if (res != NULL) {
        tuplas = PQcmdTuples(res);
        resultado = getLong(tuplas);
    }
    return resultado;
}

char* dbresult(PGresult *res, int fila, int columna) {
    char* resultado = NULL;

    if (res != NULL) {
        resultado = PQgetvalue(res, fila, columna);
    }

    return resultado;
}

void dbfree(PGresult *res) {
    PQclear(res);
}

char* getString(char *texto) {
    char* resultado = NULL;

    int tamano = strlen(texto) + 1;
    resultado = (char *) calloc(tamano, sizeof (char));

    sprintf(resultado, "%s", texto);

    return resultado;
}

long getLong(char *texto) {
    long resultado = 0;
    sscanf(texto, "%ld", &resultado);
    return resultado;
}

int getInt(char *texto) {
    int resultado = 0;
    sscanf(texto, "%d", &resultado);
    return resultado;
}

double getDouble(char *texto) {
    double resultado = 0.0;
    sscanf(texto, "%lf", &resultado);
    return resultado;
}
