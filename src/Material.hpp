
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>
#include "Color.hpp"

using namespace std;

// Clase que almacena los colores de un material
class Material {
protected:
    Color difuso;
    Color especular;
    Color refraccion;
public:

    // Constructor completo
    Material();

    // Constructor con colores
    Material(Color _difuso, Color _especular, Color _reflectante);

    // Getters del color
    Color getDifuso() const;
    Color getEspecular() const;
    Color getRefraccion() const;

    // Setters del color
    void setDifuso(Color _difuso);
    void setEspecular(Color _especular);
    void setRefraccion(Color _refraccion);

    virtual ~Material() {}

};

#endif