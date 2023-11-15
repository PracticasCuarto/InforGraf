#pragma once

#include "Material.hpp"

// Clase dielectrico, con reflexión especular y refracción (sin difusión), que hereda de material
class Dielectrico : public Material {
public:
    // Constructor completo
    Dielectrico();

    // Constructor con colores
    Dielectrico(Color _especular, Color _reflectante, Color _coeficienteEmision) : Material(Color(0, 0, 0), _especular, _reflectante, _coeficienteEmision) {}

    // Funcion calcularMaterial para calcular el color del material
    Color calcularMaterial(const Punto& puntoInterseccion, const Direccion& wi, const Direccion& wo, const Direccion& n) const {
        // Implementation of the calcularMaterial function for Dielectrico class
        // ...
        // Return the calculated color
        return Color(0, 0, 0);
    }

};


