#ifndef ESFERA_HPP
#define ESFERA_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include <math.h>
#include "Punto.hpp"
#include "Direccion.hpp"

using namespace std;

class Esfera {
private:
    Punto centro;
    Punto ciudad;
    Direccion eje;

    // Valor del radio de la esfera
    double radio;
public:
    // Constructor de la esfera
    Esfera(Punto _centro, Punto _ciudad, Direccion _eje);

    // Getters de la esfera
    Punto getCentro() const;
    Punto getCiudad() const;
    Direccion getEje() const;
    double getRadio() const;

};

#endif