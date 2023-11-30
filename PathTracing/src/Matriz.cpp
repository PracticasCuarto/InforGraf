#include "Matriz.hpp"
#include <iostream>
#include <string> 
#include <iomanip> // Necesario para std::fixed y std::setprecision


using namespace std;

// Constructor de la matriz
Matriz::Matriz(double m00, double m01, double m02, double m03,
    double m10, double m11, double m12, double m13,
    double m20, double m21, double m22, double m23,
    double m30, double m31, double m32, double m33) {
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;
    m[3][0] = m30;
    m[3][1] = m31;
    m[3][2] = m32;
    m[3][3] = m33;
}

// Función para acceder a los elementos de la matriz
double Matriz::operator()(int fila, int columna) const {
    if (fila >= 0 && fila < tamanyo && columna >= 0 && columna < tamanyo) {
        return m[fila][columna];
    }
    else {
        // Manejar el error aquí, por ejemplo, lanzar una excepción
        throw out_of_range("Índices de matriz fuera de rango");
    }
}

// Función para calcular la matriz inversa
Matriz Matriz::transformadaInversa() const {
    Matriz resultado(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    // Calcula el determinante de la matriz original
    double det = calcularDeterminante();

    // Comprueba si el determinante es igual a cero (matriz no invertible)
    if (fabs(det) < 1e-6) {
        throw runtime_error("La matriz no tiene inversa.");
    }

    // Calcula la matriz adjunta
    for (int fila = 0; fila < tamanyo; fila++) {
        for (int columna = 0; columna < tamanyo; columna++) {
            // Calcula el cofactor
            double cofactor = calcularCofactor(fila, columna);

            // Ajusta el signo del cofactor
            int signo = (fila + columna) % 2 == 0 ? 1 : -1;
            // Divide el cofactor por el determinante y ajusta el signo
            resultado.m[columna][fila] = (signo * cofactor) / det;
        }
    }

    return resultado;
}

// Función para calcular el determinante de la matriz
double Matriz::calcularDeterminante() const {
    double det = 0.0;

    // Expansión por cofactores a lo largo de la primera fila
    for (int columna = 0; columna < tamanyo; columna++) {
        // Calcula el cofactor y suma (resta alternadamente) al determinante
        double cofactor = calcularCofactor(0, columna);
        if (columna % 2 == 0) {
            det += m[0][columna] * cofactor;
        }
        else {
            det -= m[0][columna] * cofactor;
        }
    }

    return det;
}

// Función para calcular el cofactor de un elemento
double Matriz::calcularCofactor(int fila, int columna) const {
    // Calcula el determinante de la submatriz 3x3 eliminando la fila y columna dadas
    int subfila = 0;
    int subcolumna = 0;
    double submatriz[3][3];

    for (int i = 0; i < tamanyo; i++) {
        if (i == fila) continue; // Saltar la fila dada
        subcolumna = 0;
        for (int j = 0; j < tamanyo; j++) {
            if (j == columna) continue; // Saltar la columna dada
            submatriz[subfila][subcolumna] = m[i][j];
            subcolumna++;
        }
        subfila++;
    }

    // Calcula el determinante de la submatriz
    double cofactor = submatriz[0][0] * (submatriz[1][1] * submatriz[2][2] - submatriz[1][2] * submatriz[2][1])
        - submatriz[0][1] * (submatriz[1][0] * submatriz[2][2] - submatriz[1][2] * submatriz[2][0])
        + submatriz[0][2] * (submatriz[1][0] * submatriz[2][1] - submatriz[1][1] * submatriz[2][0]);

    return cofactor;
}



// Sobrecarga del operador de salida por pantalla
ostream& operator<<(ostream& salida, const Matriz& m) {
    salida << std::fixed << std::setprecision(2); // Establece 2 decimales

    salida << "/" << setw(6) << m(0, 0) << " " << setw(6) << m(0, 1) << " " << setw(6) << m(0, 2) << " " << setw(6) << m(0, 3) << " \\" << endl;
    salida << "|" << setw(6) << m(1, 0) << " " << setw(6) << m(1, 1) << " " << setw(6) << m(1, 2) << " " << setw(6) << m(1, 3) << " |" << endl;
    salida << "|" << setw(6) << m(2, 0) << " " << setw(6) << m(2, 1) << " " << setw(6) << m(2, 2) << " " << setw(6) << m(2, 3) << " |" << endl;
    salida << "\\" << setw(6) << m(3, 0) << " " << setw(6) << m(3, 1) << " " << setw(6) << m(3, 2) << " " << setw(6) << m(3, 3) << " /" << endl;

    return salida;
}