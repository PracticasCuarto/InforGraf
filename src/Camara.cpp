#include "Camara.hpp"
#include <iostream>
#include <string> 
#include <thread>
#include <mutex>
#include "Matriz.hpp"

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
    width = 256;
    height = 256;

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
// Función para calcular una fila de píxeles utilizando múltiples hilos
void Camara::calcularFilaDePixeles(const vector<Geometria*>& objetos, vector<vector<double>>& matrizImagen, double y, int fila) const {
    int inicio = 0;
    int fin = width;
    vector<double> colorPixelFila;

    for (int j = inicio; j < fin; j++) {
        double x = 1.0 - (2.0 * j / width);
        Direccion direccionRayo = Direccion(x, y, 1);

        // Cambiar a la base del mundo la dirección del rayo
        Direccion direccionRayoBase = direccionRayo.cambioBase(base);

        Rayo rayo = Rayo(origin, direccionRayoBase);
        pixel color = calcularColorPixel(objetos, rayo);

        // Agregar el color del objeto a la fila
        colorPixelFila.push_back(color.r);
        colorPixelFila.push_back(color.g);
        colorPixelFila.push_back(color.b);
    }

    // Bloquear el mutex antes de añadir la fila a la matriz de imagen
    std::lock_guard<std::mutex> lock(mtx);
    matrizImagen[fila] = colorPixelFila;
}

// Función para renderizar una escena utilizando hilos
ImagenHDR Camara::renderizar(vector<Geometria*> objetos) {
    unsigned int numCores = std::thread::hardware_concurrency();
    if (numCores == 0) {
        // No se puede determinar el número de cores
        numCores = 1;
    }

    vector<vector<double>> matrizImagen(height, vector<double>(3 * width)); // Inicializar matriz de imagen

    vector<thread> threads;

    for (int i = 0; i < height; i++) {
        double y = 1.0 - (2.0 * i / height);
        // Iniciar un hilo para calcular una fila de píxeles
        threads.emplace_back(&Camara::calcularFilaDePixeles, this, std::ref(objetos), std::ref(matrizImagen), y, i);
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    // Crear la imagenHDR
    ImagenHDR imagen = ImagenHDR(matrizImagen, width, height, 0, 255);
    return imagen;
}