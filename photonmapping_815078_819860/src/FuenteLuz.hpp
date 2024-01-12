#ifndef FUENTE_LUZ_HPP
#define FUENTE_LUZ_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include "Direccion.hpp"
#include "Punto.hpp"
#include "Color.hpp"

using namespace std;

class FuenteLuz {
protected:
    Punto origen;
    Color energia;
public:
    // Constructor completo
    FuenteLuz(Punto _origen, Color _energia);

    // Getters de la fuente de luz
    Punto getOrigen() const;
    Color getEnergia() const;

};

#endif