#ifndef PATH_TRACER_HPP
#define PATH_TRACER_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "RandomNumber.hpp"
#include "Geometria.hpp"
#include "FuenteLuz.hpp"
#include "Materiales/Material.hpp"


using namespace std;

class PathTracer {
private:
    vector<Geometria*> objetos;
    vector<FuenteLuz*> fuentes;

public:

    PathTracer();

    // Constructor
    PathTracer(const vector<Geometria*>& _objetos, const vector<FuenteLuz*>& _fuentes);

    // Función para calcular la luz incidente de una fuente en un punto de intersección
    Color calcularLuzIncidente(const FuenteLuz& fuente, const Punto& puntoInterseccion) const;

    // Calcular si el rayo que une un punto y la luz tiene alguna colision en su camino
    bool interseccionaObjetoAntesLuz(const Punto& puntoInterseccion, const Direccion& direccion, const Punto& origenFuente) const;

    // Función para calcular la luz directa de una fuente en un punto de intersección
    Color luzDirecta(const Punto& puntoInterseccion, const Color& BRDF, const Direccion& normal) const;

    // Función para calcular la luz de un objeto en un punto de intersección
    Color nextEventEstimation(const Punto puntoInterseccion, const Material& materialObjeto, const Direccion& normal, const Direccion& wi, const Punto& origin) const;

    // Función para calcular el color de un píxel
    Color calcularColorPixel(const Rayo& rayo, const Punto& origin) const;

    // Función para calcular la componente difusa de un material
    Color calcularComponenteDifusa(const Material& material, const Punto& puntoInterseccion, const Direccion& normal, const Punto& origin) const;

    // Calcular componente especular de un material
    Color calcularComponenteEspecular(const Material& material, const Punto& puntoInterseccion, const Direccion& wo, const Direccion& n) const;

    // Calcular componente refractante de un material
    Color calcularComponenteRefractante(const Material& material, const Punto& puntoInterseccion, const Direccion& wo, const Direccion& n) const;

    // Calcular la interseccion del rayo con todos los objetos de la escena y guardar la interseccion más cercana, junto con su informacion
    bool interseccionRayoEscena(const Rayo& rayo, const Punto& origin, Material& material, Punto& puntoInterseccion, Direccion& normal, int& indiceResultado) const;
};

#endif