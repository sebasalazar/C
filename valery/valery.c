#include "valery.h"

int obtener_par(int limite_inferior, int limite_superior) {
    int numero = ((rand() % limite_superior) + (limite_inferior));
    while (numero % 2 != 0) {
        numero = ((rand() % limite_superior) + (limite_inferior));
    }
    return numero;
}

int obtener_impar(int limite_inferior, int limite_superior) {
    int numero = ((rand() % limite_superior) + (limite_inferior));
    while (numero % 2 == 0) {
        numero = ((rand() % limite_superior) + (limite_inferior));
    }
    return numero;
}

void lleno_pares(int* arreglo, int cantidad) {
    int valor = cantidad;
    int numero, tamano = 0;
    while (valor > 0) {
        numero = obtener_par(0, 20);
        if (!existe(numero,arreglo,tamano)) {
            arreglo[tamano] = numero;
            tamano += 1;
            valor -= 1;
        }
    }
}

void lleno_impares(int* arreglo, int cantidad) {
    int valor = cantidad;
    int numero, tamano = 0;
    while (valor > 0) {
        numero = obtener_impar(0, 20);
        if (!existe(numero,arreglo,tamano)) {
            arreglo[tamano] = numero;
            tamano += 1;
            valor -= 1;
        }
    }
}

int existe(int numero, int* arreglo, int tamano) {
    int i, valor = 0;
    if (tamano > 0) {
        for (i = 0; i < tamano; i++) {
            if (arreglo[i] == numero)
                valor = 1;
        }
    }
    return valor;
}


