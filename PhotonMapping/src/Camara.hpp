#ifndef CAMARA_HPP
#define CAMARA_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include <math.h>
#include <vector>
#include "Punto.hpp"
#include "ImagenHDR/ImagenHDR.hpp"
#include "Geometria.hpp"
#include "Matriz.hpp"
#include "FuenteLuz.hpp"
#include "PhotonMapping.hpp"
using namespace std;

class Material;

class Camara {
private:
    Direccion left, up, forward;
    int numMuestras, resolucion;
    Punto origin;
    Matriz base;

    // Vectores de la escena
    vector<Geometria*> objetos;
    vector<FuenteLuz*> fuentes;

    PhotonMapping photonMappingLocal;
public:
    int width, height;

    // Constructor
    Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin);

    // Constructor completo incluyendo anchura, altura y muestras por pixel
    Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin, int _width, int _height, int _numMuestras, int resolucion);

    // setters
    void setObjetos(const vector<Geometria*>& _objetos);
    void setFuentes(const vector<FuenteLuz*>& _fuentes);



    void setPhotonMapping(const int numPhotons, const int maxBounces, const double nphotons_estimate, const double radius_estimate);

    // Función para calcular la interseccion de todos los objetos de la imagen con la camara
    ImagenHDR renderizar(vector<Geometria*> objetos, vector<FuenteLuz*> fuentes, const int resolucion, const int numPhotons, const int maxBounces, const double nphotons_estimate, const double radius_estimate);

    // Función para calcular el color de un píxel con anti-aliasing
    Color calcularColorPixelAA(int i, int j) const;

    // Función para calcular una región de píxeles utilizando múltiples hilos
    void calcularRegionDePixeles(vector<vector<double>>& matrizImagen, int inicioFila, int finFila) const;

};

#endif
