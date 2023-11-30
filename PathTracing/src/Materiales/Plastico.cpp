#include "Plastico.hpp"

// Constructor completo
Plastico::Plastico() {
    tipo = PLASTICO;
}

// Constructor con colores
Plastico::Plastico(Color _difuso, Color _especular, Color _coeficienteEmision) : Material(_difuso, _especular, Color(0, 0, 0), _coeficienteEmision) {
    tipo = PLASTICO;

    double maximoDifuso = max(_difuso.r, max(_difuso.g, _difuso.b));
    double maximoEspecular = max(_especular.r, max(_especular.g, _especular.b));
    pDifuso = maximoDifuso / (maximoDifuso + maximoEspecular);
    pEspecular = 1 - pDifuso;
    cout << "pDifuso: " << pDifuso << " pEspecular: " << pEspecular << endl;
    pRefraccion = 0;

    pDifuso *= 0.7;
    pEspecular *= 0.7;
}
