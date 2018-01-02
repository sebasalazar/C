#include "utils.h"

string quitar_espacio(string texto) {
    string str = texto;

    std::string::iterator it = std::remove(str.begin(), str.end(), ' ');
    str.erase(it, str.end());

    return str;
}

vector<Monomio> convertir(string polinomioStr) {
    vector<Monomio> polinomio;
    if (!polinomioStr.empty()) {
        string resultado = quitar_espacio(polinomioStr);
        vector<string> terminos = obtener_terminos(resultado);
        for (std::vector<int>::size_type i = 0; i < terminos.size(); i++) {
            string valor = terminos[i];
            cout << valor << endl;
            Monomio monomio = str2Monomio(valor);
            cout << monomio.GetCoeficiente() << "x^" << monomio.GetGrado() << endl;
            polinomio.push_back(monomio);
        }
    }
    return polinomio;
}

vector<string> obtener_terminos(string polinomioStr) {
    vector<string> elementos;

    char* str = (char *) polinomioStr.c_str();
    char* token;

    token = strtok(str, "+-");
    while (token != NULL) {
        string elemento = token;
        elementos.push_back(elemento);
        token = strtok(NULL, "+-");
    }

    return elementos;
}

Monomio str2Monomio(string str) {
    Monomio mono;

    if (!str.empty()) {
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