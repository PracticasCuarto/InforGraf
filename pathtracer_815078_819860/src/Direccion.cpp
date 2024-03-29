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

// Sobre carga del operador de resta para direccion y entero
Direccion Direccion::operator-(const int& entero) const {
    return Direccion(entero - x, entero - y, entero - z);
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

// Sobrecarga del operador de igualdad
bool Direccion::operator==(const Direccion& otroDireccion) const {
    return (x == otroDireccion.x && y == otroDireccion.y && z == otroDireccion.z);
}

// Sobrecarga del operador de acceso con corchetes
double Direccion::operator[](const int& i) const {
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
        cout << "Error: Direccion::operator[]: i must be 0, 1 or 2" << endl;
        exit(1);
    }
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

// 

// Multiplicación de una direccion por una matriz
Direccion Direccion::multiplicarMatriz(const Matriz matriz) const {
    return Direccion((x * matriz(0, 0) + y * matriz(0, 1) + z * matriz(0, 2)),
        (x * matriz(1, 0) + y * matriz(1, 1) + z * matriz(1, 2)),
        (x * matriz(2, 0) + y * matriz(2, 1) + z * matriz(2, 2)));
}

// // Multiplicación de una direccion por una matriz
// Direccion Direccion::multiplicarMatriz(const Matriz matriz) const {
//     return Direccion((x * matriz(0, 0) + x * matriz(0, 1) + x * matriz(0, 2) + matriz(0, 3)),
//         (y * matriz(1, 0) + y * matriz(1, 1) + y * matriz(1, 2) + matriz(1, 3)),
//         (z * matriz(2, 0) + z * matriz(2, 1) + z * matriz(2, 2) + matriz(2, 3)));
// }

// Multiplicación de una direccion por una matriz
// Direccion Direccion::multiplicarMatriz(const Matriz matriz) const {
//     return Direccion((x * matriz(0, 0) + x * matriz(1, 0) + x * matriz(2, 0) + x * matriz(3, 0)),
//         (y * matriz(0, 1) + y * matriz(1, 1) + y * matriz(2, 1) + y * matriz(3, 1)),
//         (z * matriz(0, 2) + z * matriz(1, 2) + z * matriz(2, 2) + z * matriz(3, 2)));
// }


// Operaciones con matrices
// Operación de tranlación de un punto con una matriz
Direccion Direccion::escala(double sx, double sy, double sz) const {
    // Crear objetos de matriz para las pruebas
    Matriz matriz(sx, 0.0, 0.0, 0.0,
        0.0, sy, 0.0, 0.0,
        0.0, 0.0, sz, 0.0,
        0.0, 0.0, 0.0, 1.0);
    return multiplicarMatriz(matriz);
}

// Operación de rotación en el eje X de un punto con una matriz
Direccion Direccion::rotacionX(double angulo) const {
    // Crear objetos de matriz para las pruebas
    Matriz matriz(1.0, 0.0, 0.0, 0.0,
        0.0, cos(angulo), -sin(angulo), 0.0,
        0.0, sin(angulo), cos(angulo), 0.0,
        0.0, 0.0, 0.0, 1.0);
    return multiplicarMatriz(matriz);
}

// Operación de rotación en el eje Y de un punto con una matriz
Direccion Direccion::rotacionY(double angulo) const {
    // Crear objetos de matriz para las pruebas
    Matriz matriz(cos(angulo), 0.0, sin(angulo), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(angulo), 0.0, cos(angulo), 0.0,
        0.0, 0.0, 0.0, 1.0);
    return multiplicarMatriz(matriz);
}

// Operación de rotación en el eje Z de un punto con una matriz
Direccion Direccion::rotacionZ(double angulo) const {
    // Crear objetos de matriz para las pruebas
    Matriz matriz(cos(angulo), -sin(angulo), 0.0, 0.0,
        sin(angulo), cos(angulo), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0);
    return multiplicarMatriz(matriz);
}

// Operación de cambio de base de un punto con una matriz
Direccion Direccion::cambioBase(const Matriz matriz) const {
    return multiplicarMatriz(matriz);
}

// Devuelve el angulo que forman dos vectores
// double Direccion::angulo(const Direccion& otroDireccion) const {
//     // Devolver el angulo en grados
//     return acos((*this * otroDireccion) / (modulo() * otroDireccion.modulo())) * 180 / M_PI;
// }

double Direccion::angulo(const Direccion& otroDireccion) const {
    // Calcular el ángulo en radianes
    double angulo_rad = acos((*this * otroDireccion) / (modulo() * otroDireccion.modulo()));

    // Convertir el ángulo de radianes a grados
    double angulo_grados = angulo_rad * 180.0 / M_PI;

    // Determinar el cuadrante
    if (otroDireccion.y < 0) {
        // Si el otro vector está en el tercer o cuarto cuadrante, ajustar el ángulo
        angulo_grados = 360.0 - angulo_grados;
    }

    return angulo_grados;
}

// Sobrecarga del operador de salida por pantalla
ostream& operator<<(ostream& salida, const Direccion& d) {
    salida << "(" << d.x << ", " << d.y << ", " << d.z << ")";
    return salida;

}
