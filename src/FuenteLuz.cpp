#include <iostream>
#include "FuenteLuz.hpp"

using namespace std;

// Constructor completo
FuenteLuz::FuenteLuz(Punto _origen, pixel _energia) : origen(_origen), energia(_energia) {}

// Getters de la fuente de luz
Punto FuenteLuz::getOrigen() const {
    return origen;
}

pixel FuenteLuz::getEnergia() const {
    return energia;
}