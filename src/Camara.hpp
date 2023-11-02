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
    Punto origin;
    Matriz base;
    int numMuestras, resolucion;
public:
    int width, height;

    // Constructor
    Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin);

    // Constructor completo incluyendo anchura, altura y muestras por pixel
    Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin, int _width, int _height, int _numMuestras, int resolucion);

    // setters
    void setLeft(Direccion _left);
    void setUp(Direccion _up);
    void setForward(Direccion _forward);
    void setOrigin(Punto _origin);
    void setWidth(int _width);
    void setHeight(int _height);

    // getters
    Direccion getLeft() const;
    Direccion getUp() const;
    Direccion getForward() const;
    Punto getOrigin() const;
    int getWidth() const;
    int getHeight() const;
    int getNumMuestras() const;

    // Función para calcular la interseccion de todos los objetos de la imagen con la camara
    ImagenHDR renderizar(vector<Geometria*> objetos, vector<FuenteLuz*> fuentes);

    // Función para calcular el color de un píxel
    pixel calcularColorPixel(const vector<Geometria*>& objetos, const vector<FuenteLuz*>& fuentes, const Rayo& rayo, const int& iteracion) const;

    // Función para calcular el color de un píxel con anti-aliasing
    pixel calcularColorPixelAA(const vector<Geometria*>& objetos, const vector<FuenteLuz*>& fuentes, int i, int j) const;

    // Función para calcular una región de píxeles utilizando múltiples hilos
    void calcularRegionDePixeles(const vector<Geometria*>& objetos, const vector<FuenteLuz*>& fuentes, vector<vector<double>>& matrizImagen, int inicioFila, int finFila) const;

    // Función para calcular el color de un píxel con anti-aliasing y múltiples hilos
    pixel luzIndirecta(const vector<Geometria*>& objetos, const vector<FuenteLuz*>& fuentes, const Punto& puntoInterseccion, const pixel& colorObjeto, const Direccion& normal, int indice, int iteracion) const;
};

#endif
