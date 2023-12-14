#include "Punto.hpp"
#include <iostream>
#include <string> 


using namespace std;

// Implementación del constructor
Punto::Punto(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
    w = 1;
}

// Implementación del constructor
Punto::Punto(double _x, double _y, double _z, double homogenea) {
    x = _x;
    y = _y;
    z = _z;
    w = homogenea;
}

// Sobrecarga del operador de resta
Direccion Punto::operator-(const Punto& otroPunto) const {
    return Direccion(x - otroPunto.x, y - otroPunto.y, z - otroPunto.z);
}

// Sobrecarga del operador de suma de una direccion con un punto
Punto Punto::operator+(const Direccion& otraDireccion) const {
    return Punto(x + otraDireccion.x, y + otraDireccion.y, z + otraDireccion.z);
}

// Sobrecarga del operador de resta de una direccion con un punto
Punto Punto::operator-(const Direccion& otraDireccion) const {
    return Punto(x - otraDireccion.x, y - otraDireccion.y, z - otraDireccion.z);
}

// Sobrecarga del operador de suma igual de una direccion con un punto
Punto Punto::operator+=(const Direccion& otraDireccion) const {
    return Punto(x + otraDireccion.x, y + otraDireccion.y, z + otraDireccion.z);
}

// Sobrecarga del operador de acceso con corchetes
double Punto::operator[](int i) const {
    if (i == 0) {
        return x;
    }
    else if (i == 1) {
        return y;
    }
    else if (i == 2) {
        return z;
    }
    else {
        return w;
    }
}

// Obtener la distancia entre dos puntos
double Punto::distancia(const Punto& otroPunto) const {
    return sqrt((x - otroPunto.x) * (x - otroPunto.x) + (y - otroPunto.y) * (y - otroPunto.y) + (z - otroPunto.z) * (z - otroPunto.z));
}

// Operaciones con matrices
// Operación de tranlación de un punto con una matriz 
Punto Punto::translacion(double tx, double ty, double tz) const {
    // Crear objetos de matriz para las pruebas
    Matriz matriz(1.0, 0.0, 0.0, tx,
        0.0, 1.0, 0.0, ty,
        0.0, 0.0, 1.0, tz,
        0.0, 0.0, 0.0, 1.0);
    return multiplicarMatriz(matriz);
}

// Operación de rotación en el eje X de un punto con una matriz
Punto Punto::rotacionX(double angulo) const {
    Matriz matriz(1.0, 0.0, 0.0, 0.0,
        0.0, cos(angulo), -sin(angulo), 0.0,
        0.0, sin(angulo), cos(angulo), 0.0,
        0.0, 0.0, 0.0, 1.0);
    return multiplicarMatriz(matriz);
}

// Operación de rotación en el eje Y de un punto con una matriz
Punto Punto::rotacionY(double angulo) const {
    Matriz matriz(cos(angulo), 0.0, sin(angulo), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(angulo), 0.0, cos(angulo), 0.0,
        0.0, 0.0, 0.0, 1.0);
    return multiplicarMatriz(matriz);
}

// Operación de rotación en el eje Z de un punto con una matriz
Punto Punto::rotacionZ(double angulo) const {
    Matriz matriz(cos(angulo), -sin(angulo), 0.0, 0.0,
        sin(angulo), cos(angulo), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0);
    return multiplicarMatriz(matriz);
}

// Operación de cambio de base de un punto con una matriz
Punto Punto::cambioBase(const Matriz matriz) const {
    return multiplicarMatriz(matriz);
}


// Sobrecarga del operador de salida por pantalla
ostream& operator<<(ostream& salida, const Punto& p) {
    salida << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return salida;
}

Punto Punto::multiplicarMatriz(const Matriz matriz) const {
    double vw = w * matriz(3, 0) + w * matriz(3, 1) + w * matriz(3, 2) + w * matriz(3, 3);
    return Punto((x * matriz(0, 0) + y * matriz(0, 1) + z * matriz(0, 2) + matriz(0, 3)) / vw,
        (x * matriz(1, 0) + y * matriz(1, 1) + z * matriz(1, 2) + matriz(1, 3)) / vw,
        (x * matriz(2, 0) + y * matriz(2, 1) + z * matriz(2, 2) + matriz(2, 3)) / vw);
}

