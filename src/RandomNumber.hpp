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

void crearSistemaCoordenadas(const Direccion& N, Direccion& Nt, Direccion& Nb) {
    if (std::fabs(N.x) > std::fabs(N.y))
        Nt = Direccion(N.z, 0, -N.x) / sqrtf(N.x * N.x + N.z * N.z);
    else
        Nt = Direccion(0, -N.z, N.y) / sqrtf(N.y * N.y + N.z * N.z);
    Nb = N.cross(Nt);
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

    // Generar la base local

    Direccion eje1 = Direccion(-INFINITY, -INFINITY, -INFINITY);
    Direccion eje2 = Direccion(-INFINITY, -INFINITY, -INFINITY);

    crearSistemaCoordenadas(normal, eje1, eje2);

    eje1 = eje1.normalizar();
    eje2 = eje2.normalizar();

    // Cambiar de base utilizando una matriz generada 
    Matriz matrizBase = Matriz(
        eje1.x, eje2.x, normal.x, 0,
        eje1.y, eje2.y, normal.y, 0,
        eje1.z, eje2.z, normal.z, 0,
        0, 0, 0, 1
    );

    // Cambiar a la base del mundo la dirección del rayo
    Direccion direccionRayo = direccionAleatoria.multiplicarMatriz(matrizBase).normalizar();
    return Rayo(puntoInterseccion, direccionRayo);
}

#endif