#include "Difuso.hpp"


// Constructor completo
Difuso::Difuso() {}

// Constructor con colores
Difuso::Difuso(Color _difuso, Color _coeficienteEmision) : Material(_difuso, Color(0, 0, 0), Color(0, 0, 0), _coeficienteEmision) {
    tipo = DIFUSO_PURO;
    pDifuso = 0.7;
    pEspecular = 0;
    pRefraccion = 0;
}
