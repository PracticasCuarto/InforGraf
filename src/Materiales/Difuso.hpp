#pragma once

#include "Material.hpp"

// Clase difuso, sin reflexión especular ni refracción, que hereda de material
class Difuso : public Material {
public:
    // Constructor completo
    Difuso() {}

    // Constructor con colores
    Difuso(Color _difuso, Color _coeficienteEmision) : Material(_difuso, Color(0, 0, 0), Color(0, 0, 0), _coeficienteEmision) {
        tipo = DIFUSO_PURO;
        pDifuso = 0.7;
        pEspecular = 0;
        pRefraccion = 0;
    }

};
