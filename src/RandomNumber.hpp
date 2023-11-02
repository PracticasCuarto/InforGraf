#ifndef RANDOM_NUMBER_HPP
#define RANDOM_NUMBER_HPP

#include <random>
#include <math.h>
#include "Geometria.hpp"


// Función para generar un número aleatorio en el rango [0, 1)
double random_double() {
    static std::random_device rd;
    static std::mt19937 generator(rd()); // Inicializa el generador con una semilla aleatoria
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

// Función para generar un rayo aleatorio en base a coordenadas esféricas
Rayo generarRayoAleatorio(const Punto& puntoInterseccion, const Direccion& normal) {
    double r1 = random_double();
    double r2 = random_double();
    double theta = 2.0 * M_PI * r1; // Ángulo azimut
    double phi = acos(sqrt(1.0 - r2)); // Ángulo polar

    // Convertir a coordenadas esféricas
    double x = cos(theta) * sin(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(phi);

    Direccion direccionAleatoria = Direccion(x, y, z);

    // Cambiar de base utilizando una matriz generada 
    Direccion aux = normal.rotacionX(10.0);
    aux = aux.rotacionY(10.0);
    aux = aux.rotacionZ(10.0);
    Direccion eje1 = normal.cross(aux);
    Direccion eje2 = normal.cross(eje1);
    Matriz matrizBase = Matriz(
        eje1.x, eje2.x, normal.x, 0,
        eje1.y, eje2.y, normal.y, 0,
        eje1.z, eje2.z, normal.z, 0,
        0, 0, 0, 1
    );

    // Cambiar a la base del mundo la dirección del rayo
    Direccion direccionRayo = direccionAleatoria.multiplicarMatriz(matrizBase);
    return Rayo(puntoInterseccion, direccionRayo);
}

#endif