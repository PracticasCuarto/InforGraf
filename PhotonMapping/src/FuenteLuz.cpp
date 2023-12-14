#include <iostream>
#include "FuenteLuz.hpp"

using namespace std;

// Constructor completo
FuenteLuz::FuenteLuz(Punto _origen, Color _energia) : origen(_origen), energia(_energia) {}

// Getters de la fuente de luz
Punto FuenteLuz::getOrigen() const {
    return origen;
}

Color FuenteLuz::getEnergia() const {
    return energia;
}