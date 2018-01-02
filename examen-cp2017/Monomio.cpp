/* 
 * File:   Monomio.cpp
 * Author: Sebastián Salazar Molina.
 * 
 */
#include "Monomio.h"

using namespace std;

Monomio::Monomio() {
    this->coeficiente = (double) 0;
    this->grado = 0;
}

Monomio::Monomio(const Monomio& orig) {
    this->coeficiente = orig.GetCoeficiente();
    this->grado = orig.GetGrado();
}

Monomio::~Monomio() {
}


double Monomio::GetCoeficiente() const {
    return coeficiente;
}

void Monomio::SetCoeficiente(double coeficiente) {
    this->coeficiente = coeficiente;
}

int Monomio::GetGrado() const {
    return grado;
}

void Monomio::SetGrado(int grado) {
    this->grado = grado;
}
