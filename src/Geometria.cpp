
#include "Geometria.hpp"
#include <iostream>
#include <string> 

using namespace std;

// Constructor de Geometria
Geometria::Geometria() : color(0, 0, 0) {
    fuenteLuz = false;
}

// Getters del color
Color Geometria::getColor() const {
    return color;
}

bool Geometria::esFuenteLuz() const {
    return fuenteLuz;
}

// Setters del color
void Geometria::setColor(Color _color) {
    color = _color;
}

// --------------------- ESFERA ---------------------

// Constructor esfera
Esfera::Esfera(Punto _centro, double _radio) : Geometria(), centro(_centro), radio(_radio) {}

// Constructor esfera con color 
Esfera::Esfera(Punto _centro, double _radio, Color _color) : Geometria(), centro(_centro), radio(_radio) {
    setColor(_color);
}

// Getters de la esfera
Punto Esfera::getCentro() const {
    return centro;
}

double Esfera::getRadio() const {
    return radio;
}

// Dado un punto de la esfera devuelva la direccion normal (con respecto al origen)
Direccion Esfera::getNormal(const Punto& punto) const {
    Direccion normal = punto - centro;
    return normal.normalizar();
}

// // --------------------- PLANO ---------------------

// Constructor plano
Plano::Plano(double _distanciaOrigen, Direccion _normal) : Geometria(), distanciaOrigen(_distanciaOrigen), normal(_normal) {}

// Constructor plano con color
Plano::Plano(double _distanciaOrigen, Direccion _normal, Color _color) : Geometria(), distanciaOrigen(_distanciaOrigen), normal(_normal) {
    setColor(_color);
}

// Getters del plano
double Plano::getDistanciaOrigen() const {
    return distanciaOrigen;
}

Direccion Plano::getNormal() const {
    return normal;
}

Direccion Plano::getNormal(const Punto& punto) const {
    return normal;
}


// --------------------- TRIANGULO ---------------------

// Constructor Triangulo
Triangulo::Triangulo(Punto _p1, Punto _p2, Punto _p3) : vertice1(_p1), vertice2(_p2), vertice3(_p3) {}

// Constructor Triangulo con color
Triangulo::Triangulo(Punto _p1, Punto _p2, Punto _p3, Color _color) : vertice1(_p1), vertice2(_p2), vertice3(_p3) {
    setColor(_color);
}

// Getters del Triangulo
Punto Triangulo::getVertice1() const {
    return vertice1;
}

Punto Triangulo::getVertice2() const {
    return vertice2;
}

Punto Triangulo::getVertice3() const {
    return vertice3;
}

// Dado un punto del triangulo devuelva la direccion normal (con respecto al origen)
Direccion Triangulo::getNormal(const Punto& punto) const {
    Direccion normal = (vertice2 - vertice1).cross(vertice3 - vertice1);
    return normal.normalizar();
}

// --------------------- RAYO ---------------------

// Constructor Rayo
Rayo::Rayo(Punto _origen, Direccion _direccion) : origen(_origen), direccion(_direccion) {}

// Getters del Rayo
Punto Rayo::getOrigen() const {
    return origen;
}

Direccion Rayo::getDireccion() const {
    return direccion;
}

// --------------------- INTERSECCIONES ---------------------

// Calcular intersección con un plano
Punto Plano::interseccion(const Rayo& rayo) const {
    Direccion normalPlano = getNormal();
    Direccion direccionRayo = rayo.getDireccion();
    Punto origenRayo = rayo.getOrigen();

    double denominador = normalPlano * direccionRayo;

    if (denominador == 0) {
        // El rayo es paralelo al plano, no hay intersección.
        return Punto(-INFINITY, -INFINITY, -INFINITY);
    }

    double t = -(normalPlano.x * origenRayo.x + normalPlano.y * origenRayo.y + normalPlano.z * origenRayo.z + getDistanciaOrigen()) / denominador;

    // Si t es negativo, la intersección ocurre detrás del origen del rayo.
    if (t < 0) {
        return Punto(-INFINITY, -INFINITY, -INFINITY);
    }

    Punto puntoInterseccion(origenRayo.x + t * direccionRayo.x, origenRayo.y + t * direccionRayo.y, origenRayo.z + t * direccionRayo.z);
    return puntoInterseccion;
}

// Función para resolver una ecuación cuadrática
bool resolverCuadratica(const float& a, const float& b, const float& c, float& x0, float& x1) {
    float discr = (b * b) - (4 * a * c);
    if (discr < 0) {
        return false;
    }
    double sqrt_discr = sqrt(discr);
    x0 = (-b + sqrt_discr) / (2 * a);
    x1 = (-b - sqrt_discr) / (2 * a);
    return true;
}

// Calcular intersección de un Rayo con una esfera
Punto Esfera::interseccion(const Rayo& rayo) const {
    float t0, t1; // soluciones para t si el rayo intersecta
    Direccion L = rayo.getOrigen() - centro; // L será el vector que apunta del centro de la esfera al origen de la camara
    Direccion direccionRayo = rayo.getDireccion();

    // Calcula el coseno del ángulo entre L y direccionRayo
    float coseno_angulo = (L * direccionRayo) / (L.modulo() * direccionRayo.modulo());

    // Convierte el coseno del ángulo a grados
    float angulo = acos(coseno_angulo) * (180.0 / M_PI);

    // Si el ángulo es menor a 90 grados, el rayo va hacia atrás
    if (angulo < 90) {
        return Punto(-INFINITY, -INFINITY, -INFINITY);
    }

    // Calcula el discriminante de la ecuación cuadrática
    float a = direccionRayo * direccionRayo;
    float b = 2 * (direccionRayo * L);
    float c = (L * L) - (radio * radio);

    // Usa la función resolverCuadratica para calcular las soluciones
    if (!resolverCuadratica(a, b, c, t0, t1)) {
        // No hay intersección
        return Punto(-INFINITY, -INFINITY, -INFINITY);
    }

    // Devolver la solución más cercana al origen del rayo
    float t = (t0 < t1) ? t0 : t1;

    Punto puntoInterseccion = rayo.getOrigen() + direccionRayo * t;

    return puntoInterseccion;
}

Punto Triangulo::interseccion(const Rayo& rayo) const {
    Punto v1 = getVertice1();
    Punto v2 = getVertice2();
    Punto v3 = getVertice3();

    // Calcular el vector de dirección del rayo y su origen
    Direccion rayDirection = rayo.getDireccion();
    Punto rayOrigin = rayo.getOrigen();

    const float EPSILON = 0.0000001;
    Direccion edge1 = v2 - v1;
    Direccion edge2 = v3 - v1;

    Direccion h = rayDirection.cross(edge2);
    double a = edge1 * h;

    if (a > -EPSILON && a < EPSILON) {
        // Este rayo es paralelo a este triángulo.
        return Punto(-INFINITY, -INFINITY, -INFINITY); // Devolver un punto nulo si no hay intersección
    }

    double f = 1.0 / a;
    Direccion s = rayOrigin - v1;
    double u = f * (s * h);

    if (u < 0.0 || u > 1.0) {
        return Punto(-INFINITY, -INFINITY, -INFINITY); // Devolver un punto nulo si no hay intersección
    }

    Direccion q = s.cross(edge1);
    double v = f * (rayDirection * q);

    if (v < 0.0 || u + v > 1.0) {
        return Punto(-INFINITY, -INFINITY, -INFINITY); // Devolver un punto nulo si no hay intersección
    }

    double t = f * (edge2 * q);

    if (t > EPSILON) {
        Punto puntoInterseccion = rayOrigin + (rayDirection * t);
        return puntoInterseccion;
    }
    else {
        return Punto(-INFINITY, -INFINITY, -INFINITY); // Devolver un punto nulo si no hay intersección
    }
}
