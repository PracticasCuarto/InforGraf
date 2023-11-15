#include "Material.hpp"
#include <cassert>

// Constructor de Material
Material::Material() : difuso(0, 0, 0), especular(0, 0, 0), refraccion(0, 0, 0), coeficienteEmision(0, 0, 0) {}

// Constructor de Material con colores
Material::Material(Color _difuso, Color _especular, Color _refraccion, Color _coeficienteEmision) : difuso(_difuso), especular(_especular), refraccion(_refraccion), coeficienteEmision(_coeficienteEmision) {
    // Comprobar que la suma de los coeficientes de reflexión, difusion y especular no supera 1
    assert(difuso.r + especular.r + refraccion.r <= 1);
    assert(difuso.g + especular.g + refraccion.g <= 1);
    assert(difuso.b + especular.b + refraccion.b <= 1);
}

// Getters del color
Color Material::getDifuso() const {
    return difuso;
}

Color Material::getEspecular() const {
    return especular;
}

Color Material::getRefraccion() const {
    return refraccion;
}

// Setters del color
void Material::setDifuso(Color _difuso) {
    difuso = _difuso;
}

void Material::setEspecular(Color _especular) {
    especular = _especular;
}

void Material::setRefraccion(Color _refraccion) {
    refraccion = _refraccion;
}

// Difuso class implementation

Difuso::Difuso() {}

Difuso::Difuso(Color _difuso, Color _coeficienteEmision) : Material(_difuso, Color(0, 0, 0), Color(0, 0, 0), _coeficienteEmision) {}

Color Difuso::calcularMaterial(const Punto& puntoInterseccion, const Direccion& wi, const Direccion& wo) const {
    // Dividir cada componente del color entre pi
    double r = (difuso.r / M_PI);
    double g = (difuso.g / M_PI);
    double b = (difuso.b / M_PI);

    return Color(r, g, b);
}

// Plastico class implementation

Plastico::Plastico() {}

Plastico::Plastico(Color _difuso, Color _especular, Color _coeficienteEmision) : Material(_difuso, _especular, Color(0, 0, 0), _coeficienteEmision) {}

Color Plastico::calcularMaterial(const Punto& puntoInterseccion, const Direccion& wi, const Direccion& wo) const {
    // Implementation of the calcularMaterial function for Plastico class
    // ...
    // Return the calculated color
    return Color(0, 0, 0);
}

// Dielectrico class implementation

Dielectrico::Dielectrico() {}

Dielectrico::Dielectrico(Color _especular, Color _reflectante, Color _coeficienteEmision) : Material(Color(0, 0, 0), _especular, _reflectante, _coeficienteEmision) {}

Color Dielectrico::calcularMaterial(const Punto& puntoInterseccion, const Direccion& wi, const Direccion& wo) const {
    // Implementation of the calcularMaterial function for Dielectrico class
    // ...
    // Return the calculated color
    return Color(0, 0, 0);
}
