#pragma once

#include "Material.hpp"

// Clase dielectrico, con reflexión especular y refracción (sin difusión), que hereda de material
class Dielectrico : public Material {
public:
    // Constructor completo
    Dielectrico();

    // Constructor con colores
    Dielectrico(Color _especular, Color _reflectante, Color _coeficienteEmision) : Material(Color(0, 0, 0), _especular, _reflectante, _coeficienteEmision) {
        tipo = DIELECTRICO;
    }

};


