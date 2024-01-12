
#ifndef GEOMETRIA_HPP
#define GEOMETRIA_HPP

#include <iostream>
#include "Punto.hpp"
#include "Direccion.hpp"
#include "Color.hpp"
#include "Materiales/Material.hpp"

using namespace std;

class Rayo;

// Clase que permite aplicar operadores de Tone Mapping a una imagen HDR
class Geometria {
protected:
    Material material;
    bool fuenteLuz;
public:
    // Constructor completo
    Geometria();

    // Constructor con material
    Geometria(Material _material);

    virtual Punto interseccion(const Rayo& rayo) const = 0;

    virtual Direccion getNormal(const Punto& punto) const = 0;

    bool esFuenteLuz() const;

    // Setters del material
    void setMaterial(Material _material);

    // Getters del color
    Material getMaterial() const;

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
    Esfera(Punto _centro, double _radio, Material _material);

    // Constructor de la esfera con color y fuente de luz
    Esfera(Punto _centro, double _radio, Material _material, bool _fuenteLuz);

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
    Plano(double _distanciaOrigen, Direccion _normal, Material _material);
    // Constructor plano con color y fuente de luz
    Plano(double _distanciaOrigen, Direccion _normal, Material _material, bool _fuenteLuz);

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
    Triangulo(Punto _vertice1, Punto _vertice2, Punto _vertice3, Material _material);
    // Constructor del triangulo con color y fuente de luz
    Triangulo(Punto _vertice1, Punto _vertice2, Punto _vertice3, Material _material, bool _fuenteLuz);

    // Getters del triangulo
    Punto getVertice1() const;
    Punto getVertice2() const;
    Punto getVertice3() const;

    Punto interseccion(const Rayo& rayo) const;

    // Dado un punto del triangulo devuelva la direccion normal (con respecto al origen)
    Direccion getNormal(const Punto& punto) const;

};

// Clase cilindro que hereda de Geometria
class Cilindro : public Geometria {
private:
    Punto centro;
    double radio;
    double altura;
public:
    // Constructor del cilindro
    Cilindro(Punto _centro, double _radio, double _altura);

    // Constructor del cilindro con color
    Cilindro(Punto _centro, double _radio, double _altura, Material _material);
    // Constructor del cilindro con color y fuente de luz
    Cilindro(Punto _centro, double _radio, double _altura, Material _material, bool _fuenteLuz);

    // Getters del cilindro
    Punto getCentro() const;
    double getRadio() const;
    double getAltura() const;

    Punto interseccion(const Rayo& rayo) const;

    // Dado un punto del cilindro devuelva la direccion normal (con respecto al origen)
    Direccion getNormal(const Punto& punto) const;
};

// Clase cubo que hereda de Geometria
class Cubo : public Geometria {
private:
    Punto centro;
    double lado; // Longitud de un lado del cubo
public:
    // Constructor del cubo
    Cubo(Punto _centro, double _lado);

    // Constructor del cubo con color
    Cubo(Punto _centro, double _lado, Material _material);

    // Getters del cubo
    Punto getCentro() const;
    double getLado() const;

    // Implementaciones de los métodos virtuales heredados
    Punto interseccion(const Rayo& rayo) const override;
    Direccion getNormal(const Punto& punto) const override;
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