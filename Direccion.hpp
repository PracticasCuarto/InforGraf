#ifndef DIRECCION_HPP
#define DIRECCION_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include <math.h>

using namespace std;

class Direccion {
public:
    double x, y, z;
    Direccion(double _x, double _y, double _z); // Constructor

    // Sobrecarga del operador de resta para direcciones
    Direccion operator-(const Direccion& otroDireccion) const;

    // Sobre carga del operador de suma para direcciones
    Direccion operator+(const Direccion& otroDireccion) const;

    // Sobrecarga del operador de multiplicación escalar
    double operator*(const Direccion& otroDireccion) const;

    // Sobrecarga del operador de mmultiplicacion de un escalar por una direccion
    Direccion operator*(const float& escalar) const;

    // Sobrecarga del operador de division de una direccion por un escalar
    Direccion operator/(const float& escalar) const;

    // Sobrecarga del operador de multiplicación vectorial
    Direccion cross(const Direccion& otroDireccion) const;

    // Sobrecarga del operador modulo
    double modulo() const;

    // Función para normalizar un vector
    Direccion normalizar() const;

};

// Sobrecarga del operador de salida por pantalla
ostream& operator<<(ostream& salida, const Direccion& p);

#endif
