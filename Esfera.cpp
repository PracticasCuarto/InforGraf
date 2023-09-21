#include "Esfera.hpp"
#include <iostream>
#include <string> 

using namespace std;

// Constructor de la esfera
Esfera::Esfera(Punto _centro, Punto _ciudad, Direccion _eje) {
    centro = _centro;
    ciudad = _ciudad;
    eje = _eje;
}