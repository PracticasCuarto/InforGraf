#include "Camara.hpp"
#include <iostream>
#include <string> 
#include <thread>
#include <mutex>

#include "Matriz.hpp"
#include "RandomNumber.hpp"

using namespace std;

// Mutex para proteger la matriz de imagen compartida
std::mutex mtx;

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

// Constructor completo incluyendo anchura, altura y muestras por pixel
Camara::Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin, int _width, int _height, int _numMuestras, int _resolucion)
    : up(_up), left(_left), forward(_forward), origin(_origin), base(
        left.x, up.x, forward.x, origin.x,
        left.y, up.y, forward.y, origin.y,
        left.z, up.z, forward.z, origin.z,
        0, 0, 0, 1
    ) {
    // Resto del código del constructor
    width = _width;
    height = _height;
    numMuestras = _numMuestras;
    resolucion = _resolucion;

    // Normalizar vectores left y up
    left = left.normalizar();
    up = up.normalizar();
}

// Setters
void Camara::setObjetos(const vector<Geometria*>& _objetos) {
    objetos = _objetos;
}

void Camara::setFuentes(const vector<FuenteLuz*>& _fuentes) {
    fuentes = _fuentes;
}

void Camara::setPathTracer() {
    pathTracerLocal = PathTracer(objetos, fuentes);
}

// Función para calcular el color de un píxel con anti-aliasing
Color Camara::calcularColorPixelAA(int i, int j) const {
    Color colorSum = Color(0, 0, 0);

    for (int n = 0; n < numMuestras; n++) {
        // Lanzar rayos a lugares aleatorios dentro del píxel
        double y = 1.0 - (2.0 * i / height - (random_double() / height));
        double x = 1.0 - (2.0 * j / width - (random_double() / width));
        Direccion direccionRayo = Direccion(x, y, 1);

        // Cambiar a la base del mundo la dirección del rayo
        Direccion direccionRayoBase = direccionRayo.cambioBase(base);

        Rayo rayo = Rayo(origin, direccionRayoBase);
        Color color = pathTracerLocal.calcularColorPixel(rayo, origin);

        // Sumar el color al resultado
        colorSum += color;
    }

    // Calcular el promedio de los colores
    colorSum /= numMuestras;

    return colorSum;
}


// Función para calcular una región de píxeles utilizando múltiples hilos con anti-aliasing
void Camara::calcularRegionDePixeles(vector<vector<double>>& matrizImagen, int inicioFila, int finFila) const {
    for (int i = inicioFila; i < finFila; i++) {
        for (int j = 0; j < width; j++) {
            Color color = calcularColorPixelAA(i, j);

            // Agregar el color del objeto a la matriz
            int index = 3 * j;
            matrizImagen[i][index] = color.r;
            matrizImagen[i][index + 1] = color.g;
            matrizImagen[i][index + 2] = color.b;
        }
    }
}

ImagenHDR Camara::renderizar(vector<Geometria*> objetos, vector<FuenteLuz*> fuentes, const int resolucion) {
    unsigned int numCores = std::thread::hardware_concurrency();
    if (numCores == 0) {
        // No se puede determinar el número de cores
        numCores = 1;
    }
    // numCores = 1;

    // Asignar los objetos y las fuentes de luz
    setObjetos(objetos);
    setFuentes(fuentes);

    // Crear el path tracer
    setPathTracer();

    vector<vector<double>> matrizImagen(height, vector<double>(3 * width)); // Inicializar matriz de imagen
    vector<thread> threads;

    int filasPorHilo = height / numCores;
    for (int i = 0; i < numCores; i++) {
        int inicioFila = i * filasPorHilo;
        int finFila = (i == numCores - 1) ? height : (i + 1) * filasPorHilo;
        threads.emplace_back(&Camara::calcularRegionDePixeles, this, std::ref(matrizImagen), inicioFila, finFila);
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    // Crear la imagenHDR
    ImagenHDR imagen = ImagenHDR(matrizImagen, width, height, 0, resolucion);
    return imagen;
}