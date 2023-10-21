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
using namespace std;

class Camara {
private:
    Direccion left, up, forward;
    Punto origin;
public:

    int width, height;

    // Constructor
    Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin);

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

    // Función para calcular la interseccion de todos los objetos de la imagen con la camara
    ImagenHDR renderizar(vector<Geometria*> objetos);


    void CalcularPixel(const vector<Geometria *> &objetos, const Matriz &base, vector<double> &colorPixelFila, double y,
                       double x) const;

    pixel calcularColorPixel(const vector<Geometria *> &objetos, const Rayo &rayo) const;
};

#endif
