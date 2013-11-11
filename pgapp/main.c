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

/*
 * 
 */
int main(int argc, char** argv) {

    PGconn *conexion = NULL;
    PGresult *resultado = NULL;

    conexion = dbconnect("146.83.181.4", 6432, "iswdb", "isw", "isw");
    resultado = dbquery(conexion, "SELECT NOW(), CAST(10 AS int)");
    fprintf(stdout, "\nAhora: %s # Diez: %d\n", getString(dbresult(resultado, 0, 0)), getInt(dbresult(resultado, 0, 1)));
    dbclose(conexion);

    return (EXIT_SUCCESS);
}

