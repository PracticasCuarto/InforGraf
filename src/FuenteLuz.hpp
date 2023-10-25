#ifndef FUENTE_LUZ_HPP
#define FUENTE_LUZ_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include "Direccion.hpp"
#include "Punto.hpp"
#include "Geometria.hpp"

using namespace std;

class FuenteLuz {
protected:
    Punto origen;
    pixel energia;
public:
    // Constructor completo
    FuenteLuz(Punto _origen, pixel _energia);

    // Getters de la fuente de luz
    Punto getOrigen() const;
    pixel getEnergia() const;
};

#endif