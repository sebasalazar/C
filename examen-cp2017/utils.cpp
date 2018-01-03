#include "utils.h"

string quitar_espacio(string texto) {
    string str = texto;

    std::string::iterator it = std::remove(str.begin(), str.end(), ' ');
    str.erase(it, str.end());

    return str;
}

vector<Monomio> convertir(string polinomioStr) {
    vector<Monomio> listado;
    if (!polinomioStr.empty()) {
        string resultado = quitar_espacio(polinomioStr);
        vector<string> terminos = obtener_terminos(resultado);

#pragma omp parallel
        {
            std::vector<int>::size_type i = 0;
            vector<Monomio> polinomio;

#pragma omp parallel for private(i)
            for (i = 0; i < terminos.size(); i++) {

                string valor = terminos[i];
                Monomio monomio = str2Monomio(valor);
                polinomio.push_back(monomio);
            }

#pragma omp critical
            listado = polinomio;
        }

    }
    return listado;
}

vector<string> obtener_terminos(string polinomioStr) {
    vector<string> elementos;
    if (!polinomioStr.empty()) {

        char* str = new char[polinomioStr.size() + 1];
        strncpy(str, polinomioStr.c_str(), polinomioStr.size());

        char* token = strtok(str, "+-");
        while (token != NULL) {
            string elemento = token;
            elementos.push_back(elemento);
            token = strtok(NULL, "+-");
        }
        delete str;
    }
    return elementos;
}

Monomio str2Monomio(string texto) {
    Monomio mono;

    if (!texto.empty()) {
        string str = texto;
        unsigned int pos = str.find("x**");
        if (pos > 0) {
            string coefStr = str.substr(0, pos);
            mono.SetCoeficiente(atof(coefStr.c_str()));

            unsigned int resto = pos + 3;
            if (str.size() >= resto) {
                string gradoStr = str.substr(resto, str.size() - 1);
                mono.SetGrado(atoi(gradoStr.c_str()));
            } else {
                mono.SetGrado(0);
            }
        } else {
            mono.SetCoeficiente((double) 1);
            string gradoStr = str.substr(pos + 3, str.size() - 1);
            mono.SetGrado(atoi(gradoStr.c_str()));
        }
    }

    return mono;
}

double integrar_evaluar(vector<Monomio> polinomio, int inferior, int superior) {
    double resultado;

#pragma omp parallel
    {
        vector<Monomio>::size_type i;
        double suma = (double) 0;
#pragma omp parallel for private(i)
        for (i = 0; i < polinomio.size(); i++) {
            Monomio monomio = polinomio[i];
            Monomio integrada;
            integrada.SetCoeficiente(monomio.GetCoeficiente() / (monomio.GetGrado() + 1));
            integrada.SetGrado(monomio.GetGrado() + 1);

#pragma omp atomic
            suma += ((integrada.GetCoeficiente() * pow(superior, integrada.GetGrado()))-(integrada.GetCoeficiente() * pow(inferior, integrada.GetGrado())));
        }

#pragma omp critical
        resultado = suma;
    }

    return resultado;
}
