#include "Punto.hpp"
#include <iostream>
#include <string> 


using namespace std;

// Implementación del constructor
Punto::Punto(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

// Sobrecarga del operador de resta
Direccion Punto::operator-(const Punto& otroPunto) const {
    return Direccion(x - otroPunto.x, y - otroPunto.y, z - otroPunto.z);
}

// Sobrecarga del operador de suma de una direccion con un punto
Punto Punto::operator+(const Direccion& otraDireccion) const {
    return Punto(x + otraDireccion.x, y + otraDireccion.y, z + otraDireccion.z);
}

// Sobrecarga del operador de salida por pantalla
ostream& operator<<(ostream& salida, const Punto& p) {
    salida << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return salida;
}
