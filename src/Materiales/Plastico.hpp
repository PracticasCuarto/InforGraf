#pragma once

#include "Material.hpp"

// Clase plástico, con reflexión difusa y especular (sin refracción), que hereda de material
class Plastico : public Material {
public:
    // Constructor completo
    Plastico();

    // Constructor con colores
    Plastico(Color _difuso, Color _especular, Color _coeficienteEmision) : Material(_difuso, _especular, Color(0, 0, 0), _coeficienteEmision) {}

    // Funcion calcularMaterial para calcular el color del material
    Color CalcularMaterial(const Punto& puntoInterseccion, const Direccion& wi, const Direccion& wo, const Direccion& n) const {
        // Implementation of the calcularMaterial function for Plastico class
        // ...
        // Return the calculated color
        return Color(0, 0, 0);
    };

};
