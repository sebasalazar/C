/* 
 * File:   main.c
 * Author: seba
 *
 * Created on November 11, 2013, 6:52 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "comun.h"
#include "db.h"
#include "utils.h"
#include "tareas.h"
#include "grafico.h"

void prueba();

/*
 * 
 */
int main(int argc, char** argv) {
    ventas_anuales* ventas_anuales = NULL;
    ventas_horarias* ventas_horarias = NULL;
    ventas_mensuales* ventas_mensuales = NULL;
    char *tienda = NULL;
    int i = 0;
    int num_ventas = 0;
    int opcion = 2;

#ifdef FREEIMAGE_LIB
    FreeImage_Initialise();
#endif // FREEIMAGE_LIB

    srand (time(NULL));
    
    fprintf(stdout, "Tarea de 03 de Ingenieria de Software\n");

    switch (opcion) {
        case 1:
            // Opción "-r"
            limpiar();
            ventas_anuales = getVentasAnuales(&num_ventas);
            for (i = 0; i < num_ventas; i++) {
                fprintf(stdout, "Tienda: %10s \t Monto: %ld\n", ventas_anuales[i].tienda, ventas_anuales[i].monto);
            }
            free(ventas_anuales);
            break;

        case 2:
            // Opción -g tienda
//            tienda = leer_string("Ingrese la tienda: ");
            ventas_mensuales = getVentasMensuales("Porahi", &num_ventas);
            for (i = 0; i < num_ventas; i++) {
                fprintf(stdout, "Tienda: %10s \t Mes: %02d \t Monto: %ld\n", ventas_mensuales[i].tienda, ventas_mensuales[i].mes, ventas_mensuales[i].monto);
            }
            graficar(ventas_mensuales);
            free(ventas_mensuales);
            break;

        case 3:
            // Opción -bh
            limpiar();
            ventas_horarias = getVentasHorarias(&num_ventas);
            for (i = 0; i < num_ventas; i++) {
                fprintf(stdout, "Tienda: %10s \t Hora: %02d \t Monto: %ld\n", ventas_horarias[i].tienda, ventas_horarias[i].hora, ventas_horarias[i].monto);
            }
            free(ventas_horarias);
            break;

        case 4:
            // Opción -v
            limpiar();
            fprintf(stdout, "Fecha de Compilacion: %s %s\n", __DATE__, __TIME__);
            fprintf(stdout, "Fecha Actual: %s\n", ahora());
            fprintf(stdout, "Version: 1.0.0\n");
            fprintf(stdout, "\n\tSebastian Salazar Molina\n");
            break;

        default:
            limpiar();
            fprintf(stdout, "Forma de uso: '%s -opcion', donde opcion:\n", argv[0]);
            fprintf(stdout, "Opcion: -r \t\t Entrega la sumatoria total de las ventas de cada una de las tiendas\n");
            fprintf(stdout, "Opcion: -g tienda \t Entrega un grafico con las ventas mensuales de la tienda pasada por parametro\n");
            fprintf(stdout, "Opcion: -bh \t\t Entrega la hora de mejores ventas de cada una da las tiendas\n");
            fprintf(stdout, "Opcion: -v \t\t Entrega informacion acerca del programa\n");
            return EXIT_FAILURE;
            break;
    }

#ifdef FREEIMAGE_LIB
    FreeImage_DeInitialise();
#endif // FREEIMAGE_LIB

    return EXIT_SUCCESS;
}