#ifndef CAMARA_HPP
#define CAMARA_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include <math.h>
#include <vector>
#include "Punto.hpp"
#include "ImagenHDR.hpp"
#include "Geometria.hpp"
#include "Matriz.hpp"
#include "FuenteLuz.hpp"
using namespace std;

const int numRayos = 64;
const int maxIter = 8;

class Camara {
private:
    Direccion left, up, forward;
    int numMuestras, resolucion;
    Punto origin;
    Matriz base;

    // Vectores de la escena
    vector<Geometria*> objetos;
    vector<FuenteLuz*> fuentes;
public:
    int width, height;

    // Constructor
    Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin);

    // Constructor completo incluyendo anchura, altura y muestras por pixel
    Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin, int _width, int _height, int _numMuestras, int resolucion);

    // setters
    void setObjetos(const vector<Geometria*>& _objetos);
    void setFuentes(const vector<FuenteLuz*>& _fuentes);


    // Función para calcular la interseccion de todos los objetos de la imagen con la camara
    ImagenHDR renderizar(vector<Geometria*> objetos, vector<FuenteLuz*> fuentes);

    // Función para calcular el color de un píxel
    Color calcularColorPixel(const Rayo& rayo, const int& iteracion) const;

    // Función para calcular el color de un píxel con anti-aliasing
    Color calcularColorPixelAA(int i, int j) const;

    // Función para calcular una región de píxeles utilizando múltiples hilos
    void calcularRegionDePixeles(vector<vector<double>>& matrizImagen, int inicioFila, int finFila) const;

    // Función para calcular el color de un píxel con anti-aliasing y múltiples hilos
    Color luzIndirecta(const Punto& puntoInterseccion, const Color& colorObjeto, const Direccion& normal, int indice, int iteracion) const;
};

#endif
