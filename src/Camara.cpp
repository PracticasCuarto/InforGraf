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

    // Normalizar vectores left y up
    left = left.normalizar();
    up = up.normalizar();
}


// Función para renderizar una escena
ImagenHDR Camara::renderizar(vector<Geometria*> objetos) {
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
        for (int j = 0; j < width; j++) {
            // Calcular i y j normalizados en el rango [-1, 1]
            double y = (2.0 * i / height) - 1.0;
            double x = 1.0 - (2.0 * j / width);

            // Calcular la direccion del rayo
            Direccion direccionRayo = Direccion(x, y, 1);

            // Cambiar a la base del mundo la direccion del rayo
            Direccion direccionRayoBase = direccionRayo.cambioBase(base);

            Rayo rayo = Rayo(origin, direccionRayoBase);

            // color del objeto con el que colisiona el rayo
            pixel color;
            color.r = 0;
            color.g = 0;
            color.b = 0;
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
            // Agregar el punto a la matriz el color del objeto (si no tiene valor ponerlo a negro)
            colorPixelFila.push_back(color.r);
            colorPixelFila.push_back(color.g);
            colorPixelFila.push_back(color.b);

        }
        // Mostrar por pantalla los elementos de colorPixelFila
        for (int i = 0; i < colorPixelFila.size(); i += 3) {
            cout << colorPixelFila[i] << " " << colorPixelFila[i + 1] << " " << colorPixelFila[i + 2] << endl;
        }
        matrizImagen.insert(matrizImagen.begin(), colorPixelFila);
    }

    // Crear la imagenHDR 
    ImagenHDR imagen = ImagenHDR(matrizImagen, width, height, 0, 255);
    return imagen;
}