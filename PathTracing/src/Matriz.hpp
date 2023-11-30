#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include <math.h>

using namespace std;

const int tamanyo = 4;

class Matriz {
public:
    double m[tamanyo][tamanyo];

    // Constructor de la matriz
    Matriz(double m00, double m01, double m02, double m03,
        double m10, double m11, double m12, double m13,
        double m20, double m21, double m22, double m23,
        double m30, double m31, double m32, double m33);

    // Función para acceder a los elementos de la matriz
    double operator()(int fila, int columna) const;

    Matriz transformadaInversa() const;

    // Función para calcular el determinante de la matriz
    double calcularDeterminante() const;

    // Función para calcular el cofactor de un elemento
    double calcularCofactor(int fila, int columna) const;
};

// Sobrecarga operador de salida por pantalla
ostream& operator<<(ostream& salida, const Matriz& m);

#endif