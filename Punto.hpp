#ifndef PUNTO_HPP
#define PUNTO_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include "Direccion.hpp"

using namespace std;

class Punto {
public:
    double x, y, z;
    Punto(double _x, double _y, double _z); // Constructor

    // Sobrecarga del operador de resta
    Direccion operator-(const Punto& otroPunto) const;

    // Sobrecarga del operador de suma de una direccion con un punto
    Punto operator+(const Direccion& otraDireccion) const;
};


// Sobrecarga del operador de salida por pantalla
ostream& operator<<(ostream& salida, const Punto& p);

#endif
