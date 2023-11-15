
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>
#include "Color.hpp"
#include "Punto.hpp"
#include "Direccion.hpp"


using namespace std;

// Clase que almacena los colores de un material
class Material {
protected:
    Color difuso;
    Color especular;
    Color refraccion;
    Color coeficienteEmision;
public:

    // Constructor completo
    Material();

    // Constructor con colores
    Material(Color _difuso, Color _especular, Color _reflectante, Color coeficienteEmision);

    // Getters del color
    Color getDifuso() const;
    Color getEspecular() const;
    Color getRefraccion() const;

    // Setters del color
    void setDifuso(Color _difuso);
    void setEspecular(Color _especular);
    void setRefraccion(Color _refraccion);

    // Funcion virtual calcularMaterial para calcular el color del material
    virtual Color calcularMaterial(const Punto& puntoInterseccion, const Direccion& wi, const Direccion& wo) const;

    virtual ~Material() {}

};

// Clase difuso, sin reflexión especular ni refracción, que hereda de material
class Difuso : public Material {
public:
    // Constructor completo
    Difuso();

    // Constructor con colores
    Difuso(Color _difuso, Color _coeficienteEmision);

    // Funcion calcularMaterial para calcular el color del material
    Color calcularMaterial(const Punto& puntoInterseccion, const Direccion& wi, const Direccion& wo) const;

    ~Difuso() {}
};

// Clase plástico, con reflexión difusa y especular (sin refracción), que hereda de material
class Plastico : public Material {
public:
    // Constructor completo
    Plastico();

    // Constructor con colores
    Plastico(Color _difuso, Color _especular, Color _coeficienteEmision);

    // Funcion calcularMaterial para calcular el color del material
    Color calcularMaterial(const Punto& puntoInterseccion, const Direccion& wi, const Direccion& wo) const;

    ~Plastico() {}
};

// Clase dielectrico, con reflexión especular y refracción (sin difusión), que hereda de material
class Dielectrico : public Material {
public:
    // Constructor completo
    Dielectrico();

    // Constructor con colores
    Dielectrico(Color _especular, Color _reflectante, Color _coeficienteEmision);

    // Funcion calcularMaterial para calcular el color del material
    Color calcularMaterial(const Punto& puntoInterseccion, const Direccion& wi, const Direccion& wo) const;

    ~Dielectrico() {}
};



#endif