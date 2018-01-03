/* 
 * File:   utils.h
 * Author: Sebastián Salazar Molina.
 *
 */

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <omp.h>

#include "Monomio.h"

using namespace std;


string quitar_espacio(string texto);

vector<Monomio> convertir(string polinomioStr);

vector<string> obtener_terminos(string polinomioStr);

Monomio str2Monomio(string str);

double integrar_evaluar(vector<Monomio> polinomio, int inferior, int superior);

#endif /* UTILS_H */

