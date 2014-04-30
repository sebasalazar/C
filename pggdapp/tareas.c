/* 
 * File:   tareas.h
 * Author: Sebastián Salazar Molina <sebasalazar@gmail.com>
 *
 */

#include "tareas.h"

char** getTiendas(int* num_tiendas) {
    char** tiendas = NULL;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;
    int i = 0;
    int num = 0;

    conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
    if (conexion != NULL) {
        resultado = dbquery(conexion, "SELECT DISTINCT tienda FROM ventas");
        num = dbnumrows(resultado);
        if (num > 0) {
            tiendas = malloc(num * sizeof (char *));
            for (i = 0; i < num; i++) {
                tiendas[i] = getString(dbresult(resultado, i, 0));
            }
            dbfree(resultado);
        }
        dbclose(conexion);
    }

    *num_tiendas = num;
    return tiendas;
}

ventas_anuales* getVentasAnuales(int* cantidades_ventas) {
    ventas_anuales* ventas = NULL;
    int i = 0;
    int num = 0;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;

    conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
    if (conexion != NULL) {
        resultado = dbquery(conexion, "SELECT tienda, SUM(monto) FROM ventas GROUP BY tienda");
        num = dbnumrows(resultado);
        if (num > 0) {
            ventas = (ventas_anuales *) malloc(num * sizeof (ventas_anuales));
            for (i = 0; i < num; i++) {
                ventas[i].tienda = getString(dbresult(resultado, i, 0));
                ventas[i].monto = getLong(dbresult(resultado, i, 1));
            }
            dbfree(resultado);
        }
        dbclose(conexion);
    }

    *cantidades_ventas = num;

    return ventas;
}

ventas_mensuales* getVentasMensuales(char* tienda, int* cantidades_ventas) {
    ventas_mensuales* ventas = NULL;
    int i = 0;
    int num = 0;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;
    char sql[513];

    if (tienda != NULL) {
        conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
        if (conexion != NULL) {
            memset(sql, 0, sizeof (sql));
            snprintf(sql, 512, "SELECT tienda, EXTRACT(month FROM fecha) AS mes,SUM(monto) AS total FROM ventas WHERE tienda = '%s' GROUP BY tienda, mes ORDER BY mes", tienda);
            resultado = dbquery(conexion, sql);
            num = dbnumrows(resultado);
            if (num > 0) {
                ventas = (ventas_mensuales *) malloc(num * sizeof (ventas_mensuales));
                for (i = 0; i < num; i++) {
                    ventas[i].tienda = getString(dbresult(resultado, i, 0));
                    ventas[i].mes = getInt(dbresult(resultado, i, 1));
                    ventas[i].monto = getLong(dbresult(resultado, i, 2));
                }
                dbfree(resultado);
            }
            dbclose(conexion);
        }
    }
    *cantidades_ventas = num;

    return ventas;
}

ventas_horarias* getVentasHorarias(int* cantidades_ventas) {
    ventas_horarias* ventas = NULL;
    int i = 0;
    int num = 0;
    PGconn *conexion = NULL;
    PGresult *resultado = NULL;

    conexion = dbconnect(SERVIDOR, PUERTO, NOMBREDB, USUARIODB, PASSDB);
    if (conexion != NULL) {
        resultado = dbquery(conexion, "SELECT DISTINCT ON (tienda) tienda, EXTRACT(hour FROM fecha) AS hora,SUM(monto) AS total FROM ventas GROUP BY tienda, hora ORDER BY tienda, SUM(monto) DESC");
        num = dbnumrows(resultado);
        if (num > 0) {
            ventas = (ventas_horarias *) malloc(num * sizeof (ventas_horarias));
            for (i = 0; i < num; i++) {
                ventas[i].tienda = getString(dbresult(resultado, i, 0));
                ventas[i].hora = getInt(dbresult(resultado, i, 1));
                ventas[i].monto = getLong(dbresult(resultado, i, 2));
            }
            dbfree(resultado);
        }
        dbclose(conexion);
    }

    *cantidades_ventas = num;

    return ventas;
}
