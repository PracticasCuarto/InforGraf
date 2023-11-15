// Funciones para calcular las componentes de los materiales

#include "Material.hpp"
#include "Camara.hpp"

// Funcion para calcular la componente difusa de un material
Color calcularComponenteDifusa(const Material& material) {
    // Dividir cada componente del color entre pi
    Color difuso = material.getDifuso();
    double r = (difuso.r / M_PI);
    double g = (difuso.g / M_PI);
    double b = (difuso.b / M_PI);
    return Color(r, g, b);
}

// Calcular componente especular de un material
Color calcularComponenteEspecular(const Material& material, const Punto& puntoInterseccion, const Direccion& wi, const Direccion& wo, const Direccion& n) {
    // wr = wo - 2 * (wo * n) * n
    // ks * wr / (n * wi)
    Direccion wr = wo - (n * (2 * (wo * n)));

    Rayo rayo = Rayo(puntoInterseccion, wr.normalizar());

    Color especular = material.getEspecular();
    //double r = (especular.r * wr) / (n * wi);
    //double g = (especular.g * wr) / (n * wi);
    //double b = (especular.b * wr) / (n * wi);
}