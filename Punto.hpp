#ifndef PUNTO_HPP
#define PUNTO_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include "Direccion.hpp"
#include "Matriz.hpp"

using namespace std;

class Punto {
public:
    double x, y, z, w;
    Punto(double _x, double _y, double _z); // Constructor
    Punto(double _x, double _y, double _z, double homogenea); // Constructor


    // Sobrecarga del operador de resta
    Direccion operator-(const Punto& otroPunto) const;

    // Sobrecarga del operador de suma de una direccion con un punto
    Punto operator+(const Direccion& otraDireccion) const;

    // Obtener la distancia entre dos puntos
    double distancia(const Punto& otroPunto) const;

    // Operaciones con matrices
    // Operación de tranlación de un punto con una matriz
    Punto translacion(double tx, double ty, double tz) const;

    // Operación de rotación en el eje X de un punto con una matriz
    Punto rotacionX(double angulo) const;

    // Operación de rotación en el eje Y de un punto con una matriz
    Punto rotacionY(double angulo) const;

    // Operación de rotación en el eje Z de un punto con una matriz
    Punto rotacionZ(double angulo) const;

    // Operación de cambio de base de un punto con una matriz
    Punto cambioBase(const Matriz matriz) const;

    Punto multiplicarMatriz(const Matriz matriz) const;

};


// Sobrecarga del operador de salida por pantalla
ostream& operator<<(ostream& salida, const Punto& p);

#endif
