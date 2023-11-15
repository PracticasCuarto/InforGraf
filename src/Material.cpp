#include "Material.hpp"

// Constructor de Material
Material::Material() : difuso(0, 0, 0), especular(0, 0, 0), refraccion(0, 0, 0) {}

// Constructor de Material con colores
Material::Material(Color _difuso, Color _especular, Color _refraccion) : difuso(_difuso), especular(_especular), refraccion(_refraccion) {}

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

