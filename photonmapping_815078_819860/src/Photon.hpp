#ifndef PHOTON_HPP
#define PHOTON_HPP

#include <iostream>
#include "Geometria.hpp"

using namespace std;

class Photon {
private:
    Punto photonPosition;
    Direccion wi;
    Color flux;

public:
    Photon();
    Photon(Punto position, Direccion wi, Color flux);

    Punto getPosition() const;
    Direccion getWi() const;
    Color getFlux() const;

    // Acceder a la posición del photon en la dimensión i
    double position(const int i) const;
};

#endif