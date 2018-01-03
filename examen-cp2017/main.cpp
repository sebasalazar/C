/* 
 * File:   main.cpp
 * Author: Sebastián Salazar Molina.
 */
#include <iostream>
#include <string>
#include <cstdlib>

#include "utils.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    if (argc != 4) {
        cout << "Argumentos inválidos, ejecute el programa de la siguiente forma:" << endl;
        cout << argv[0] << " \"[integral polinomica]\" [limite inferior] [limite superior]" << endl;
        return EXIT_FAILURE;
    }

    string polinomio = argv[1];
    int inferior = atoi(argv[2]);
    int superior = atoi(argv[3]);
    cout << "polinomio: " << polinomio << endl;
    cout << "Limite inferior: " << inferior << endl;
    cout << "Limite superior: " << superior << endl;

    vector<Monomio> monomios = convertir(polinomio);
    cout << endl;
    vector<Monomio>::size_type i = 0;
    for (i = 0; i < monomios.size(); i++) {
        Monomio monomio = monomios[i];
        cout << monomio.GetCoeficiente() << "x^" << monomio.GetGrado() << " ";
    }
    cout << endl;

    double resultado = integrar_evaluar(monomios, inferior, superior);
    cout << endl << "Resultado: " << resultado << endl;

    return EXIT_SUCCESS;
}

