#ifndef ESTACION_HPP
#define ESTACION_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include <math.h>
#include "Esfera.hpp"
#include "Punto.hpp"
#include "Direccion.hpp"

using namespace std;

class Estacion {
private:

    // Datos necesarios para la estación 
    Esfera planeta;
    double inclinacion;
    double azimut;

    // Datos que se pueden calcular a partir de los datos necesarios
    Punto posicion;
    Direccion normal;
    Direccion tangenteLongitud;
    Direccion tangenteLatitud;
public:
    // Constructor de la Estacion
    Estacion(Esfera _planeta, double _inclinacion, double _azimut);

    // Getters
    Punto getPosicion() const { return posicion; }
    Direccion getNormal() const { return normal; }
    Direccion getTangenteLongitud() const { return tangenteLongitud; }
    Direccion getTangenteLatitud() const { return tangenteLatitud; }

    // Conexion con otra estación en otro planeta. Es importante que no atraviese la superficie de ninguno de los dos planetas
    Direccion conectar(Estacion otraEstacion);


};

#endif