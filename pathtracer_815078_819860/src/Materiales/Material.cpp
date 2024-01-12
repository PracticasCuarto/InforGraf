#include "Material.hpp"
#include <cassert>

// Constructor de Material
Material::Material() : difuso(0, 0, 0), especular(0, 0, 0), refraccion(0, 0, 0), coeficienteEmision(0, 0, 0) {
    tipo = NADA;
}

// Constructor de Material con colores
Material::Material(Color _difuso, Color _especular, Color _refraccion, Color _coeficienteEmision) : difuso(_difuso), especular(_especular), refraccion(_refraccion), coeficienteEmision(_coeficienteEmision) {
    // Comprobar que la suma de los coeficientes de reflexión, difusion y especular no supera 1
    assert(difuso.r + especular.r + refraccion.r <= 1);
    assert(difuso.g + especular.g + refraccion.g <= 1);
    assert(difuso.b + especular.b + refraccion.b <= 1);

    tipo = NADA;
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


// Ruleta rusa para decidir que componente hay que calcular
Componentes Material::ruletaRusa() const {
    double aleatorio = random_double();

    if (aleatorio <= pDifuso) {
        return DIFUSO;
    }
    else if (aleatorio <= pDifuso + pEspecular) {
        return ESPECULAR;
    }
    else if (aleatorio <= pDifuso + pEspecular + pRefraccion) {
        return REFRACCION;
    }
    else {
        return ABSORCION;
    }
}