#include "Camara.hpp"
#include <iostream>
#include <string> 
#include "Matriz.hpp"

using namespace std;

// Constructor por defecto de la camara
Camara::Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin)
    : up(_up), left(_left), forward(_forward), origin(_origin) {
    // Resto del código del constructor
    width = 256;
    height = 256;
    fov = 60;

    // Normalizar vectores left y up
    left = left.normalizar();
    up = up.normalizar();
}


// Función para renderizar una escena
ImagenHDR Camara::renderizar(vector<Geometria> objetos) {
    vector<vector<double>> matrizImagen;

    // Definir matriz cambio de base
    Matriz base = Matriz(left.x, up.x, forward.x, origin.x,
        left.y, up.y, forward.y, origin.y,
        left.z, up.z, forward.z, origin.z,
        0, 0, 0, 1);

    // Recorrer el ancho del plano de la camara
    for (int i = -1; i < 1; i += 1 / width) {
        vector<vector<double>> fila;
        // Recorrer el alto del plano de la camara
        for (int j = 1; j > -1; j -= 1 / height) {
            // Calcular la direccion del rayo
            Direccion direccionRayo = Direccion(i, j, 1);

            // Cambiar a la base del mundo la direccion del rayo
            Direccion direccionRayoBase = direccionRayo.cambioBase(base);

            Rayo rayo = Rayo(origin, direccionRayoBase);

            // color del objeto con el que colisiona el rayo
            pixel color;
            float distancia = INFINITY;
            // Para todos los objetos de la escena calcular la interseccion y devolver la que mas cerca este
            // de la camara
            for (Geometria objeto : objetos) {
                Punto puntoInterseccion = rayo.interseccion(objeto);
                if (puntoInterseccion.x != -INFINITY) {
                    // Calcular la distancia entre el origen de la camara y el punto de interseccion
                    float distanciaInterseccion = puntoInterseccion.distancia(origin);
                    if (distanciaInterseccion < distancia) {
                        distancia = distanciaInterseccion;
                        color = objeto.getColor();
                    }
                }
            }

            // Agregar el punto a la matriz el color del objeto (si no tiene valor ponerlo a negro)
            vector<double> colorPixel = { color.r, color.g, color.b };
            matrizImagen.push_back(colorPixel);
        }
    }

    // Crear la imagenHDR 
    ImagenHDR imagen = ImagenHDR(matrizImagen, width, height, 0, 255);
    return imagen;
}