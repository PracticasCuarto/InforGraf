#ifndef PHOTON_HPP
#define PHOTON_HPP

#include <iostream>
#include "../../PathTracing/src/Geometria.hpp"

using namespace std;

class Photon {
private:
    Punto photonPosition;
    Direccion wi;
    Material flux;

public:
    Photon();
    Photon(Punto position, Direccion wi, Material flux);

    Punto getPosition() const;
    Direccion getWi() const;
    Material getFlux() const;

    // Acceder a la posición del photon en la dimensión i
    double position(const int i) const;
};

#endif