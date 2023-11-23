#include "Dielectrico.hpp"

// Constructor completo
Dielectrico::Dielectrico() {
    tipo = DIELECTRICO;
}

// Constructor con colores
Dielectrico::Dielectrico(Color _especular, Color _reflectante, Color _coeficienteEmision, double _medioRefraccion) : Material(Color(0, 0, 0), _especular, _reflectante, _coeficienteEmision), medioRefraccion(_medioRefraccion) {
    tipo = DIELECTRICO;

    double maximoRefraccion = max(_reflectante.r, max(_reflectante.g, _reflectante.b));
    double maximoEspecular = max(_especular.r, max(_especular.g, _especular.b));
    pRefraccion = maximoRefraccion / (maximoRefraccion + maximoEspecular);
    pEspecular = 1 - pRefraccion;
    cout << "pEspecular: " << pEspecular << " pRefraccion: " << pRefraccion << endl;
    pDifuso = 0;

    pRefraccion *= 0.7;
    pEspecular *= 0.7;

    indiceRefraccion = _medioRefraccion;
}

