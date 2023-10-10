
#ifndef GEOMETRIA_HPP
#define GEOMETRIA_HPP

#include <iostream>
#include "Punto.hpp"
#include "Direccion.hpp"

using namespace std;

struct pixel {
    float r;
    float g;
    float b;
};

// Clase que permite aplicar operadores de Tone Mapping a una imagen HDR
class Geometria {
protected:
    pixel color;
public:
    // Constructor completo
    Geometria();
};

// Clase Esfera que hereda de Geometria
class Esfera : public Geometria {
private:
    Punto centro;

    // Valor del radio de la esfera
    double radio;
public:
    // Constructor de la esfera
    Esfera(Punto _centro, double _radio);

    // Getters de la esfera
    Punto getCentro() const;
    double getRadio() const;

};

// Clase Plano que hereda de Geometria
class Plano : public Geometria {
private:
    double distanciaOrigen;
    Direccion normal;
public:
    // Constructor del plano
    Plano(double _distanciaOrigen, Direccion _normal);

    // Getters del plano
    double getDistanciaOrigen() const;
    Direccion getNormal() const;
};

class rayo {
private:
    Punto origen;
    Direccion direccion;
public:
    // Constructor del rayo
    rayo(Punto _origen, Direccion _direccion);

    // Getters del rayo
    Punto getOrigen() const;
    Direccion getDireccion() const;

    // Calcular intersección con un plano
    Punto interseccion(const Plano& plano) const;

    // Calcular intersección con una esfera
    Punto interseccion(const Esfera& esfera) const;
};

#endif