#include "Camara.hpp"
#include <iostream>
#include <string> 
#include <thread>
#include <mutex>
#include <random>
#include "Matriz.hpp"

using namespace std;

// Mutex para proteger la matriz de imagen compartida
std::mutex mtx;

// Función para generar un número aleatorio en el rango [0, 1)
double random_double() {
    static std::random_device rd;
    static std::mt19937 generator(rd()); // Inicializa el generador con una semilla aleatoria
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

Camara::Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin)
    : up(_up), left(_left), forward(_forward), origin(_origin), base(
        left.x, up.x, forward.x, origin.x,
        left.y, up.y, forward.y, origin.y,
        left.z, up.z, forward.z, origin.z,
        0, 0, 0, 1
    ) {
    // Resto del código del constructor
    width = 512;
    height = 512;

    // Normalizar vectores left y up
    left = left.normalizar();
    up = up.normalizar();
}

// Función para calcular el color de un píxel
pixel Camara::calcularColorPixel(const vector<Geometria*>& objetos, const Rayo& rayo) const {
    pixel color = Pixel(0, 0, 0);
    float distancia = INFINITY;

    for (int k = 0; k < objetos.size(); k++) {
        Punto puntoInterseccion = objetos[k]->interseccion(rayo);
        if (puntoInterseccion.x != -INFINITY) {
            float distanciaInterseccion = origin.distancia(puntoInterseccion);
            if (distanciaInterseccion <= distancia) {
                distancia = distanciaInterseccion;
                color = objetos[k]->getColor();
            }
        }
    }
    return color;
}


// Función para calcular el color de un píxel con anti-aliasing
pixel Camara::calcularColorPixelAA(const vector<Geometria*>& objetos, int i, int j) const {
    pixel colorSum = Pixel(0, 0, 0);

    for (int n = 0; n < numRayos; n++) {
        // Lanzar rayos a lugares aleatorios dentro del píxel
        // double y = 1.0 - (2.0 * (i + random_double()) / height);
        // double x = 1.0 - (2.0 * (j + random_double()) / width);
        double y = 1.0 - (2.0 * i / height - (random_double() / height));
        double x = 1.0 - (2.0 * j / width - (random_double() / width));
        Direccion direccionRayo = Direccion(x, y, 1);

        // Cambiar a la base del mundo la dirección del rayo
        Direccion direccionRayoBase = direccionRayo.cambioBase(base);

        Rayo rayo = Rayo(origin, direccionRayoBase);
        pixel color = calcularColorPixel(objetos, rayo);

        // Sumar el color al resultado
        colorSum.r += color.r;
        colorSum.g += color.g;
        colorSum.b += color.b;
    }

    // Calcular el promedio de los colores
    colorSum.r /= numRayos;
    colorSum.g /= numRayos;
    colorSum.b /= numRayos;

    return colorSum;
}


// Función para calcular una región de píxeles utilizando múltiples hilos con anti-aliasing
void Camara::calcularRegionDePixeles(const vector<Geometria*>& objetos, vector<vector<double>>& matrizImagen, int inicioFila, int finFila) const {
    for (int i = inicioFila; i < finFila; i++) {
        for (int j = 0; j < width; j++) {
            pixel color = calcularColorPixelAA(objetos, i, j);

            // Agregar el color del objeto a la matriz
            int index = 3 * j;
            matrizImagen[i][index] = color.r / 255;
            matrizImagen[i][index + 1] = color.g / 255;
            matrizImagen[i][index + 2] = color.b / 255;
        }
    }
}


ImagenHDR Camara::renderizar(vector<Geometria*> objetos) {
    unsigned int numCores = std::thread::hardware_concurrency();
    if (numCores == 0) {
        // No se puede determinar el número de cores
        numCores = 1;
    }

    vector<vector<double>> matrizImagen(height, vector<double>(3 * width)); // Inicializar matriz de imagen
    vector<thread> threads;

    int filasPorHilo = height / numCores;
    for (int i = 0; i < numCores; i++) {
        int inicioFila = i * filasPorHilo;
        int finFila = (i == numCores - 1) ? height : (i + 1) * filasPorHilo;
        threads.emplace_back(&Camara::calcularRegionDePixeles, this, std::ref(objetos), std::ref(matrizImagen), inicioFila, finFila);
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    // Crear la imagenHDR
    ImagenHDR imagen = ImagenHDR(matrizImagen, width, height, 0, 255);
    return imagen;
}