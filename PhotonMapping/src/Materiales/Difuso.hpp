#pragma once

#include "Material.hpp"

// Clase difuso, sin reflexión especular ni refracción, que hereda de material
class Difuso : public Material {
public:
    // Constructor completo
    Difuso();

    // Constructor con colores
    Difuso(Color _difuso, Color _coeficienteEmision);
};
