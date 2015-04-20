#include "arbol.h"

void insertar_arbol(nodo_arbol ** arbol, unsigned long indice, char* texto) {
    nodo_arbol *temp = NULL;
    if (!(*arbol)) {
        temp = (nodo_arbol *) malloc(sizeof (nodo_arbol));
        temp->izquierda = temp->derecha = NULL;
        temp->id = indice;

        int largo = strlen(texto) + 1;
        temp->valor = (char *) calloc(largo, sizeof(char));
        snprintf(temp->valor, largo, "%s", texto);
        
        *arbol = temp;
        return;
    }

    if (indice < (*arbol)->id) {
        insertar_arbol(&(*arbol)->izquierda, indice, texto);
    } else if (indice > (*arbol)->id) {
        insertar_arbol(&(*arbol)->derecha, indice, texto);
    }

}

void imprimir_arbol_preorden(nodo_arbol * arbol) {
    if (arbol) {
        printf("[id: %ld # valor %s]\n", arbol->id, arbol->valor);
        imprimir_arbol_preorden(arbol->izquierda);
        imprimir_arbol_preorden(arbol->derecha);
    }

}

void imprimir_arbol_inorden(nodo_arbol * arbol) {
    if (arbol) {
        imprimir_arbol_inorden(arbol->izquierda);
        printf("[id: %ld # valor %s]\n", arbol->id, arbol->valor);
        imprimir_arbol_inorden(arbol->derecha);
    }
}

void imprimir_arbol_postorden(nodo_arbol * arbol) {
    if (arbol) {
        imprimir_arbol_postorden(arbol->izquierda);
        imprimir_arbol_postorden(arbol->derecha);
        printf("[id: %ld # valor %s]\n", arbol->id, arbol->valor);
    }
}

void eliminar_arbol(nodo_arbol * arbol) {
    if (arbol) {
        eliminar_arbol(arbol->izquierda);
        eliminar_arbol(arbol->derecha);
        free(arbol);
    }
}

nodo_arbol* buscar_arbol(nodo_arbol ** arbol, unsigned long val) {
    if (!(*arbol)) {
        return NULL;
    }

    if (val < (*arbol)->id) {
        buscar_arbol(&((*arbol)->izquierda), val);
    } else if (val > (*arbol)->id) {
        buscar_arbol(&((*arbol)->derecha), val);
    } else if (val == (*arbol)->id) {
        return *arbol;
    }
}
