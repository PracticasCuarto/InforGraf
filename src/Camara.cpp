#include "Camara.hpp"
#include <iostream>
#include <string> 
#include <thread>
#include "Matriz.hpp"

using namespace std;

// Constructor por defecto de la camara
Camara::Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin)
    : up(_up), left(_left), forward(_forward), origin(_origin) {
    // Resto del código del constructor
    width = 256;
    height = 256;

    // Normalizar vectores left y up
    left = left.normalizar();
    up = up.normalizar();
}


// Función para renderizar una escena
ImagenHDR Camara::renderizar(vector<Geometria*> objetos) {
    unsigned int numCores = thread::hardware_concurrency();
    if (numCores == 0) {
        // No se puede determinar el número de cores
        numCores = 1;
    }
    vector<vector<double>> matrizImagen;

    // Definir matriz cambio de base
    Matriz base = Matriz(left.x, up.x, forward.x, origin.x,
        left.y, up.y, forward.y, origin.y,
        left.z, up.z, forward.z, origin.z,
        0, 0, 0, 1);

    // Recorrer el alto del plano de la camara
    for (int i = 0; i < height; i++) {
        // Recorrer el alto del plano de la cámara
        vector<double> colorPixelFila;
        double y = 1.0 - (2.0 * i / height);
        int inicio = 0;
        int fin = width;
        for (int j = inicio; j < fin; j++) {
            // Calcular i y j normalizados en el rango [-1, 1]
            double x = 1.0 - (2.0 * j / width);
            CalcularPixel(objetos, base, colorPixelFila, y, x);

        }
        matrizImagen.push_back(colorPixelFila);
    }

    // Crear la imagenHDR 
    ImagenHDR imagen = ImagenHDR(matrizImagen, width, height, 0, 255);
    return imagen;
}

void Camara::CalcularPixel(const vector<Geometria*>& objetos, const Matriz& base, vector<double>& colorPixelFila, double y,
    double x) const {// Calcular la direccion del rayo
    Direccion direccionRayo = Direccion(x, y, 1);

    // Cambiar a la base del mundo la direccion del rayo
    Direccion direccionRayoBase = direccionRayo.cambioBase(base);

    Rayo rayo = Rayo(origin, direccionRayoBase);
    pixel color = calcularColorPixel(objetos, rayo);

    // Agregar el punto a la matriz el color del objeto (si no tiene valor ponerlo a negro)
    colorPixelFila.push_back(color.r);
    colorPixelFila.push_back(color.g);
    colorPixelFila.push_back(color.b);
}

pixel Camara::calcularColorPixel(const vector<Geometria *> &objetos,
                                 const Rayo &rayo) const {// color del objeto con el que colisiona el rayo
    pixel color = Pixel(0,0,0);
    float distancia = INFINITY;

    // Para todos los objetos de la escena calcular la interseccion y devolver la que mas cerca este
// de la camara
    for (int k = 0; k < objetos.size(); k++) {
        // cout << "Calculando interseccion con un objeto" << endl;
        Punto puntoInterseccion = objetos[k]->interseccion(rayo);
        if (puntoInterseccion.x != -INFINITY) {
            // Calcular la distancia entre el origen de la camara y el punto de interseccion
            float distanciaInterseccion = origin.distancia(puntoInterseccion);
            if (distanciaInterseccion <= distancia) {
                // cout << "colision" << endl;
                distancia = distanciaInterseccion;
                color = objetos[k]->getColor();

            }
        }
    }
    return color;
}
