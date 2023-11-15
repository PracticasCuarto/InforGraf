#pragma once

#include "Material.hpp"

// Clase difuso, sin reflexión especular ni refracción, que hereda de material
class Difuso : public Material {
public:
    // Constructor completo
    Difuso() {}

    // Constructor con colores
    Difuso(Color _difuso, Color _coeficienteEmision) : Material(_difuso, Color(0, 0, 0), Color(0, 0, 0), _coeficienteEmision) {}

    // Funcion calcularMaterial para calcular el color del material
    Color calcularMaterial(const Punto& puntoInterseccion, const Direccion& wi, const Direccion& wo, const Direccion& n) const {
        return calcularComponenteDifusa(*this);
    }

};
