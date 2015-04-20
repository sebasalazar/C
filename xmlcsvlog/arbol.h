/* 
 * File:   arbol.h
 * Author: Sebastián Salazar Molina <ssalazar@experti.cl>
 *
 * Created on April 20, 2015, 11:17 AM
 */

#ifndef ARBOL_H
#define	ARBOL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

    struct arbol_binario {
        unsigned long id;
        char * valor;
        struct arbol_binario * derecha, * izquierda;
    };
    typedef struct arbol_binario nodo_arbol;

    /**
     * 
     * @param arbol
     * @param indice
     * @param texto
     */
    void insertar_arbol(nodo_arbol ** arbol, unsigned long indice, char* texto);
    
    /**
     * 
     * @param arbol
     */
    void imprimir_arbol_preorden(nodo_arbol * arbol);
    
    /**
     * 
     * @param arbol
     */
    void imprimir_arbol_inorden(nodo_arbol * arbol);
    
    /**
     * 
     * @param arbol
     */
    void imprimir_arbol_postorden(nodo_arbol * arbol);
    
    /**
     * Elimina todo el arbol de la memora.
     * @param arbol
     */
    void eliminar_arbol(nodo_arbol * arbol);
    
    /**
     * Busca un nodo
     * @param arbol estructura completa
     * @param val indice a buscar
     * @return el nodo con el indice encontrado o nulo en caso contrario
     */
    nodo_arbol* buscar_arbol(nodo_arbol ** arbol, unsigned long val);


#ifdef	__cplusplus
}
#endif

#endif	/* ARBOL_H */

