
#include "Geometria.hpp"
#include <iostream>
#include <string> 

using namespace std;

// Constructor de Geometria
Geometria::Geometria() {}

// Constructor esfera
Esfera::Esfera(Punto _centro, double _radio) : Geometria(), centro(_centro), radio(_radio) {}

// Getters de la esfera
Punto Esfera::getCentro() const {
    return centro;
}

double Esfera::getRadio() const {
    return radio;
}

// Constructor plano
Plano::Plano(double _distanciaOrigen, Direccion _normal) : Geometria(), distanciaOrigen(_distanciaOrigen), normal(_normal) {}

// Getters del plano
double Plano::getDistanciaOrigen() const {
    return distanciaOrigen;
}

Direccion Plano::getNormal() const {
    return normal;
}

// Constructor rayo
rayo::rayo(Punto _origen, Direccion _direccion) : origen(_origen), direccion(_direccion) {}

// Getters del rayo
Punto rayo::getOrigen() const {
    return origen;
}

Direccion rayo::getDireccion() const {
    return direccion;
}

// Calcular intersección con un plano
Punto rayo::interseccion(const Plano& plano) const {
    Direccion normalPlano = plano.getNormal();
    double A = normalPlano.x;
    double B = normalPlano.y;
    double C = normalPlano.z;
    double D = plano.getDistanciaOrigen();

    Direccion direccionRayo = getDireccion();
    double dx = direccionRayo.x;
    double dy = direccionRayo.y;
    double dz = direccionRayo.z;

    Punto origenRayo = getOrigen();
    double xo = origenRayo.x;
    double yo = origenRayo.y;
    double zo = origenRayo.z;

    double denominador = A * dx + B * dy + C * dz;

    if (denominador == 0) {
        // El rayo es paralelo al plano, no hay intersección.
        // Puedes manejar este caso de acuerdo a tus necesidades.
        // Por ejemplo, lanzando una excepción o devolviendo un valor especial.
        // Aquí, se devuelve un punto fuera del mundo (-infinito) como indicador de no intersección.
        return Punto(-INFINITY, -INFINITY, -INFINITY);
    }

    double t = -(A * xo + B * yo + C * zo + D) / denominador;

    Punto puntoInterseccion(xo + t * dx, yo + t * dy, zo + t * dz);

    return puntoInterseccion;
}

// Calcular intersección de un rayo con una esfera
Punto rayo::interseccion(const Esfera& esfera) const {
    Punto centroEsfera = esfera.getCentro();
    double radioEsfera = esfera.getRadio();

    Direccion direccionRayo = getDireccion();
    double dx = direccionRayo.x;
    double dy = direccionRayo.y;
    double dz = direccionRayo.z;

    Punto origenRayo = getOrigen();
    double xo = origenRayo.x;
    double yo = origenRayo.y;
    double zo = origenRayo.z;

    double a = dx * dx + dy * dy + dz * dz;
    double b = 2 * (dx * (xo - centroEsfera.x) + dy * (yo - centroEsfera.y) + dz * (zo - centroEsfera.z));
    double c = (xo - centroEsfera.x) * (xo - centroEsfera.x) + (yo - centroEsfera.y) * (yo - centroEsfera.y) + (zo - centroEsfera.z) * (zo - centroEsfera.z) - radioEsfera * radioEsfera;

    double discriminante = b * b - 4 * a * c;

    if (discriminante < 0) {
        // El rayo no intersecta la esfera.
        // Puedes manejar este caso de acuerdo a tus necesidades.
        // Por ejemplo, lanzando una excepción o devolviendo un valor especial.
        // Aquí, se devuelve un punto fuera del mundo (-infinito) como indicador de no intersección.
        return Punto(-INFINITY, -INFINITY, -INFINITY);
    }

    double t1 = (-b + sqrt(discriminante)) / (2 * a);
    double t2 = (-b - sqrt(discriminante)) / (2 * a);

    cout << "t1: " << t1 << endl;
    cout << "t2: " << t2 << endl;


    if (abs(t1) == abs(t2)) {
        cout << "t1 == t2 == " << t1 << endl;
        Punto puntoInterseccion = origenRayo + direccionRayo * t1;
        return puntoInterseccion;
    }
    else {
        double t;
        if (abs(t1) > abs(t2)) {
            t = t2;
        }
        else {
            t = t1;
        }
        cout << "t: " << t << endl;

        // Calcular el punto de intersección
        Punto puntoInterseccion = origenRayo + direccionRayo * t;
        return puntoInterseccion;
    }
}

