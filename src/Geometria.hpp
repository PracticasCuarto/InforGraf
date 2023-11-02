
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

// Constructor para pixel
pixel Pixel(float r, float g, float b);

class Rayo;

// Clase que permite aplicar operadores de Tone Mapping a una imagen HDR
class Geometria {
protected:
    pixel color;
    bool fuenteLuz = false;
public:
    // Constructor completo
    Geometria();

    virtual Punto interseccion(const Rayo& rayo) const = 0;

    virtual Direccion getNormal(const Punto& punto) const = 0;

    // Getters del color
    pixel getColor() const;
    bool esFuenteLuz() const;

    // Setters del color
    void setColor(pixel _color);

    virtual ~Geometria() {}
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

    // Constructor de la esfera con color
    Esfera(Punto _centro, double _radio, pixel _color);

    // Getters de la esfera
    Punto getCentro() const;
    double getRadio() const;

    Punto interseccion(const Rayo& rayo) const;
    Direccion getNormal(const Punto& punto) const;
};

// Clase Plano que hereda de Geometria
class Plano : public Geometria {
private:
    double distanciaOrigen;
    Direccion normal;
public:
    // Constructor del plano
    Plano(double _distanciaOrigen, Direccion _normal);
    // Constructor plano con color
    Plano(double _distanciaOrigen, Direccion _normal, pixel _color);

    // Getters del plano
    double getDistanciaOrigen() const;
    Direccion getNormal() const;

    Direccion getNormal(const Punto& punto) const;

    Punto interseccion(const Rayo& rayo) const;
};

class Triangulo : public Geometria {
private:
    Punto vertice1;
    Punto vertice2;
    Punto vertice3;
public:
    // Constructor del triangulo
    Triangulo(Punto _vertice1, Punto _vertice2, Punto _vertice3);

    // Constructor del triangulo con color
    Triangulo(Punto _vertice1, Punto _vertice2, Punto _vertice3, pixel _color);

    // Getters del triangulo
    Punto getVertice1() const;
    Punto getVertice2() const;
    Punto getVertice3() const;

    Punto interseccion(const Rayo& rayo) const;

    // Dado un punto del triangulo devuelva la direccion normal (con respecto al origen)
    Direccion getNormal(const Punto& punto) const;

};

class Rayo {
private:
    Punto origen;
    Direccion direccion;
public:
    // Constructor del rayo
    Rayo(Punto _origen, Direccion _direccion);

    // Getters del rayo
    Punto getOrigen() const;
    Direccion getDireccion() const;
};

#endif