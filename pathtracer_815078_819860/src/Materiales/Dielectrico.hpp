#pragma once

#include "Material.hpp"

// Clase dielectrico, con reflexión especular y refracción (sin difusión), que hereda de material
class Dielectrico : public Material {
private:
    double medioRefraccion;
public:
    // Constructor completo
    Dielectrico();

    // Constructor con colores
    Dielectrico(Color _especular, Color _reflectante, Color _coeficienteEmision, double _medioRefraccion);

};


