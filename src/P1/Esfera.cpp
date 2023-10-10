#include "Esfera.hpp"
#include <iostream>
#include <string> 

using namespace std;

// Constructor de la esfera
Esfera::Esfera(Punto _centro, Punto _ciudad, Direccion _eje) : centro(_centro), ciudad(_ciudad), eje(_eje) {
    centro = _centro;
    ciudad = _ciudad;
    eje = _eje;

    // hacer una doble verificación para asegurar que el radio definido por
    // el eje y la distancia entre el centro y la ciudad de referencia tengan el mismo valor, con un
    // margen de error máximo de 10−6
    double _radio = centro.distancia(ciudad);
    double modulo = eje.modulo();
    if (fabs(_radio - modulo) > 0.000001) {
        cout << "Error: El radio definido por el eje y la distancia entre el centro y la ciudad de referencia no tienen el mismo valor" << endl;
        cout << "El radio definido por el eje es: " << modulo << endl;
        cout << "La distancia entre el centro y la ciudad de referencia es: " << _radio << endl;
        radio = 0;
    }
    else {
        // Dar valor al radio
        radio = _radio;
    }
}

// Getters de la esfera
Punto Esfera::getCentro() const {
    return centro;
}

Punto Esfera::getCiudad() const {
    return ciudad;
}

Direccion Esfera::getEje() const {
    return eje;
}

double Esfera::getRadio() const {
    return radio;
}