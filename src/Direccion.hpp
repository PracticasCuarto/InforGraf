#ifndef DIRECCION_HPP
#define DIRECCION_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include <math.h>
#include "Matriz.hpp"

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

    // Operaciones con matrices
    // Operación de tranlación de un punto con una matriz
    Direccion escala(double sx, double sy, double sz) const;

    // Operación de rotación en el eje X de un punto con una matriz
    Direccion rotacionX(double angulo) const;

    // Operación de rotación en el eje Y de un punto con una matriz
    Direccion rotacionY(double angulo) const;

    // Operación de rotación en el eje Z de un punto con una matriz
    Direccion rotacionZ(double angulo) const;

    // Operación de cambio de base de un punto con una matriz
    Direccion cambioBase(const Matriz matriz) const;

    // Multiplicación de una direccion por una matriz
    Direccion multiplicarMatriz(const Matriz matriz) const;

    // Devuelve el angulo que forman dos vectores
    double angulo(const Direccion& otroDireccion) const;

};

// Sobrecarga del operador de salida por pantalla
ostream& operator<<(ostream& salida, const Direccion& p);

#endif
