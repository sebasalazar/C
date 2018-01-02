/* 
 * File:   Monomio.h
 * Author: Sebastián Salazar Molina.
 *
 */

#ifndef MONOMIO_H
#define MONOMIO_H

class Monomio {
public:
    Monomio();
    Monomio(const Monomio& orig);
    ~Monomio();
    double GetCoeficiente() const;
    void SetCoeficiente(double coeficiente);
    int GetGrado() const;
    void SetGrado(int grado);
private:
    double coeficiente;
    int grado;
};

#endif /* MONOMIO_H */

