#include <iostream>
#include <cassert>

#include "Direccion.hpp"
#include "Punto.hpp"


int main() {
    // Crear objetos de dirección para las pruebas
    Direccion dir1(1.0, 2.0, 3.0);
    Direccion dir2(2.0, 3.0, 4.0);

    // Prueba de la sobrecarga del operador de salida por pantalla
    std::cout << "Dir1: " << dir1 << std::endl;

    // Prueba de la sobrecarga del operador de resta
    Direccion resta = dir1 - dir2;
    assert(resta.x == -1.0 && resta.y == -1.0 && resta.z == -1.0);

    // Prueba de la sobrecarga del operador de suma
    Direccion suma = dir1 + dir2;
    assert(suma.x == 3.0 && suma.y == 5.0 && suma.z == 7.0);

    // Prueba de la sobrecarga del operador de multiplicación escalar (dot product)
    double productoPunto = dir1 * dir2;
    assert(productoPunto == 20.0);

    // Prueba de la sobrecarga del operador de multiplicación escalar
    Direccion productoEscalar = dir1 * 2.0;
    assert(productoEscalar.x == 2.0 && productoEscalar.y == 4.0 && productoEscalar.z == 6.0);

    // Prueba de la sobrecarga del operador de división por escalar
    Direccion divisionEscalar = dir1 / 2.0;
    assert(divisionEscalar.x == 0.5 && divisionEscalar.y == 1.0 && divisionEscalar.z == 1.5);

    // Prueba de la sobrecarga del operador de producto cruzado
    Direccion cruz = dir1.cross(dir2);
    assert(cruz.x == -1.0 && cruz.y == 2.0 && cruz.z == -1.0);

    // Prueba del cálculo del módulo
    double mod = dir1.modulo();
    assert(mod == sqrt(14)); // Aproximadamente igual a la raíz cuadrada de 14

    // Prueba de la normalización
    Direccion normalizada = dir1.normalizar();
    const double tolerancia = 0.00001; // Define una tolerancia adecuada

    assert(std::abs(normalizada.x - (dir1.x / mod)) < tolerancia &&
        std::abs(normalizada.y - (dir1.y / mod)) < tolerancia &&
        std::abs(normalizada.z - (dir1.z / mod)) < tolerancia);

    std::cout << "Todas las pruebas de direcciones pasaron con éxito." << std::endl;

    std::cout << "----------------------------------------------------" << std::endl;

    // Crear objetos de punto para las pruebas
    Punto punto1(1.0, 2.0, 3.0);
    Punto punto2(2.0, 3.0, 4.0);
    Direccion direccion(1.0, 1.0, 1.0);

    // Prueba de la sobrecarga del operador de resta
    Direccion restaDir = punto1 - punto2;
    assert(restaDir.x == -1.0 && restaDir.y == -1.0 && restaDir.z == -1.0);

    // Prueba de la sobrecarga del operador de suma de un punto con una dirección
    Punto sumaDir = punto1 + direccion;
    assert(sumaDir.x == 2.0 && sumaDir.y == 3.0 && sumaDir.z == 4.0);

    // Prueba de la sobrecarga del operador de salida por pantalla
    std::cout << "Punto1: " << punto1 << std::endl;

    std::cout << "Todas las pruebas de puntos pasaron con éxito." << std::endl;

    std::cout << "----------------------------------------------------" << std::endl;


    return 0;
}
