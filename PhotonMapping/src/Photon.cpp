#include "Photon.hpp"
#include <iostream>

using namespace std;

// Constructor 
Photon::Photon(Punto _position, Direccion _wi, Material _flux) : photonPosition(_position), wi(_wi), flux(_flux) {}

// Getters
Punto Photon::getPosition() const {
    return photonPosition;
}

Direccion Photon::getWi() const {
    return wi;
}

Material Photon::getFlux() const {
    return flux;
}

// Acceder a la posición del photon en la dimensión i
double Photon::position(const int i) const {
    if (i == 0) {
        return photonPosition.x;
    }
    else if (i == 1) {
        return photonPosition.y;
    }
    else if (i == 2) {
        return photonPosition.z;
    }
    else {
        cout << "Error: Photon::position: i must be 0, 1 or 2" << endl;
        exit(1);
    }
}
