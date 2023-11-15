#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>
#include "../Color.hpp"
#include "../Punto.hpp"
#include "../Direccion.hpp"

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
    virtual Color calcularMaterial(const Punto& puntoInterseccion, const Direccion& wi, const Direccion& wo, const Direccion& n) const {
        return Color(0, 0, 0);
    }

    virtual ~Material() {}
};




#endif