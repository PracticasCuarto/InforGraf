#include "Direccion.hpp"
#include <iostream>
#include <string> 

using namespace std;


// Implementación del constructor
Direccion::Direccion(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

// Sobre carga del operador de resta para direcciones
Direccion Direccion::operator-(const Direccion& otroDireccion) const {
    return Direccion(x - otroDireccion.x, y - otroDireccion.y, z - otroDireccion.z);
}

// Sobre carga del operador de suma para direcciones
Direccion Direccion::operator+(const Direccion& otroDireccion) const {
    return Direccion(x + otroDireccion.x, y + otroDireccion.y, z + otroDireccion.z);
}

// Sobrecarga del operador de multiplicación escalar
double Direccion::operator*(const Direccion& otroDireccion) const {
    return x * otroDireccion.x + y * otroDireccion.y + z * otroDireccion.z;
}

// Sobrecarga del operador de multiplicación escalar (dot product)
Direccion Direccion::operator*(const float& escalar) const {
    return Direccion(x * escalar, y * escalar, z * escalar);
}

// Sobrecarga del operador de division de una direccion por un escalar
Direccion Direccion::operator/(const float& escalar) const {
    return Direccion(x / escalar, y / escalar, z / escalar);
}

// Sobrecarga del operador de multiplicación vectorial (producto cruzado)
Direccion Direccion::cross(const Direccion& otroDireccion) const {
    double nuevoX = (y * otroDireccion.z) - (z * otroDireccion.y);
    double nuevoY = (z * otroDireccion.x) - (x * otroDireccion.z);
    double nuevoZ = (x * otroDireccion.y) - (y * otroDireccion.x);

    return Direccion(nuevoX, nuevoY, nuevoZ);
}

// Sobrecarga del operador modulo
double Direccion::modulo() const {
    return sqrt(x * x + y * y + z * z);
}

// Función para normalizar un vector
Direccion Direccion::normalizar() const {
    float mod = modulo();
    return Direccion(x / mod, y / mod, z / mod);
}

// Sobrecarga del operador de salida por pantalla
ostream& operator<<(ostream& salida, const Direccion& d) {
    salida << "(" << d.x << ", " << d.y << ", " << d.z << ")";
    return salida;
}