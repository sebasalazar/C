/** 
 * File:   grafico.c
 * Author: Sebastián Salazar Molina <sebasalazar@gmail.com>
 *
 */

#include "grafico.h"

void graficar(ventas_mensuales* ventas) {

    gdImagePtr imagen;
    FILE *archivo;
    char titulo[513];
    int blanco, negro, color;
    gdFontPtr fuente = gdFontGetSmall();

    imagen = gdImageCreateTrueColor(IMG_WIDTH, IMG_HEIGHT);

    int x = 0;
    int y = 0;
    int mes = 0;
    int alto = 50;
    int ancho = 70;
    long maximo = 0;
    long paso = 0;
    double porcentaje = 0.0;

    if (imagen) {
        blanco = gdImageColorAllocate(imagen, 255, 255, 255);
        negro = gdImageColorAllocate(imagen, 0, 0, 0);


        // Pintamos el fondo Blanco
        gdImageFill(imagen, 0, 0, blanco);

        // Coloco el título
        memset(titulo, 0, 513);
        snprintf(titulo, 512, "Ventas Anuales tienda %s", ventas[0].tienda);
        gdImageString(imagen, fuente, (int) IMG_WIDTH * 0.4, 25, (unsigned char *) titulo, negro);

        // Buscamos el máximo
        for (mes = 0; mes < 12; mes++) {
            // Busco el valor máximo, este me permitira calcular cuanto es el alto máximo
            if (ventas[mes].monto >= maximo) {
                maximo = ventas[mes].monto;
            }
        }

        // Coloco la etiqueta al costado del gráfico
        for (y=BORDE_ALTO; y <= (BORDE_ALTO + 500); y = y + 50) {
            // Etiqueta
            gdImageString(imagen, fuente, 5, IMG_HEIGHT - y, (unsigned char *) longStr(paso), negro);
            paso += (maximo / 10);
        }
        
        for (mes = 0; mes < 12; mes++) {
            // Color
            color = gdImageColorAllocate(imagen, color_aleatoreo(), color_aleatoreo(), color_aleatoreo());
            porcentaje = ((double) ventas[mes].monto / maximo);

            // El alto máximo serán 500px que será el 100%
            alto = (int) (450 * porcentaje);

            // Barra
            gdImageFilledRectangle(imagen, ancho, IMG_HEIGHT - BORDE_ALTO, ancho + 55, IMG_HEIGHT - (BORDE_ALTO + alto), color);
            // Etiqueta del Mes
            gdImageString(imagen, fuente, ancho + 15, IMG_HEIGHT - BORDE_ALTO + 5, (unsigned char *) etiquetaMes(ventas[mes].mes), color);
            // Monto
            gdImageString(imagen, fuente, ancho, IMG_HEIGHT - (BORDE_ALTO + alto + 20), (unsigned char *) longStr(ventas[mes].monto), color);
            ancho += 55;
        }


        // Pintamos Borde
        gdImageLine(imagen, BORDE_ANCHO, BORDE_ALTO, (IMG_WIDTH - BORDE_ANCHO), BORDE_ALTO, negro);
        gdImageLine(imagen, BORDE_ANCHO, (IMG_HEIGHT - BORDE_ALTO), (IMG_WIDTH - BORDE_ANCHO), (IMG_HEIGHT - BORDE_ALTO), negro);
        gdImageLine(imagen, BORDE_ANCHO, BORDE_ALTO, BORDE_ANCHO, (IMG_HEIGHT - BORDE_ALTO), negro);
        gdImageLine(imagen, (IMG_WIDTH - BORDE_ANCHO), BORDE_ALTO, (IMG_WIDTH - BORDE_ANCHO), (IMG_HEIGHT - BORDE_ALTO), negro);


        // Guardar imagen
        archivo = fopen("grafico.jpg", "w");
        gdImageJpeg(imagen, archivo, 100);
        fclose(archivo);
        gdImageDestroy(imagen);
    }
}

