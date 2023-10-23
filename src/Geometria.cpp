
#include "Geometria.hpp"
#include <iostream>
#include <string> 

using namespace std;

// --------------------- Pixel ---------------------

// Constructor para pixel
pixel Pixel(float r, float g, float b) {
    pixel p;
    p.r = r;
    p.g = g;
    p.b = b;
    return p;
}

// Constructor de Geometria
Geometria::Geometria() {}

// Getters del color
pixel Geometria::getColor() const {
    return color;
}

// Setters del color
void Geometria::setColor(pixel _color) {
    color = _color;
}

// --------------------- ESFERA ---------------------

// Constructor esfera
Esfera::Esfera(Punto _centro, double _radio) : Geometria(), centro(_centro), radio(_radio) {}

// Constructor esfera con color 
Esfera::Esfera(Punto _centro, double _radio, pixel _color) : Geometria(), centro(_centro), radio(_radio) {
    setColor(_color);
}

// Getters de la esfera
Punto Esfera::getCentro() const {
    return centro;
}

double Esfera::getRadio() const {
    return radio;
}

// // --------------------- PLANO ---------------------

// Constructor plano
Plano::Plano(double _distanciaOrigen, Direccion _normal) : Geometria(), distanciaOrigen(_distanciaOrigen), normal(_normal) {}

// Constructor plano con color
Plano::Plano(double _distanciaOrigen, Direccion _normal, pixel _color) : Geometria(), distanciaOrigen(_distanciaOrigen), normal(_normal) {
    setColor(_color);
}

// Getters del plano
double Plano::getDistanciaOrigen() const {
    return distanciaOrigen;
}

Direccion Plano::getNormal() const {
    return normal;
}

// --------------------- TRIANGULO ---------------------

// Constructor Triangulo
Triangulo::Triangulo(Punto _p1, Punto _p2, Punto _p3) : vertice1(_p1), vertice2(_p2), vertice3(_p3) {}

// Constructor Triangulo con color
Triangulo::Triangulo(Punto _p1, Punto _p2, Punto _p3, pixel _color) : vertice1(_p1), vertice2(_p2), vertice3(_p3) {
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

// // Calcular intersección de un Rayo con un Triangulo
// Punto Triangulo::interseccion(const Rayo& rayo) const {
//     // Obtener los vértices del triángulo
//     Punto v1 = getVertice1();
//     Punto v2 = getVertice2();
//     Punto v3 = getVertice3();

//     // Calcular el vector normal del triángulo
//     Direccion normal = (v2 - v1).cross(v3 - v1).normalizar();

//     cout << "normal.x: " << normal.x << endl;
//     cout << "normal.y: " << normal.y << endl;
//     cout << "normal.z: " << normal.z << endl;

//     // Calcular la distancia del plano del triángulo al origen del rayo
//     double denominador = normal * rayo.getDireccion();

//     if (denominador == 0) {
//         // El rayo es paralelo al plano, no hay intersección.
//         // Puedes manejar este caso de acuerdo a tus necesidades.
//         // Por ejemplo, lanzando una excepción o devolviendo un valor especial.
//         // Aquí, se devuelve un punto fuera del mundo (-infinito) como indicador de no intersección.
//         return Punto(-INFINITY, -INFINITY, -INFINITY);
//     }

//     double distanciaPlano = (normal * (v1 - rayo.getOrigen())) / denominador;


//     cout << "distanciaPlano: " << distanciaPlano << endl;

//     // Si la distancia es negativa, el rayo está apuntando en la dirección opuesta al plano del triángulo
//     if (distanciaPlano < 0) {
//         return Punto(-INFINITY, -INFINITY, -INFINITY); // Devolver un punto nulo si no hay intersección
//     }

//     // Calcular el punto de intersección con el plano del triángulo
//     Punto puntoInterseccion = rayo.getOrigen() + rayo.getDireccion() * distanciaPlano;

//     // Calcular los vectores desde el punto de intersección hacia cada vértice del triángulo
//     Direccion v1Interseccion = puntoInterseccion - v1;
//     Direccion v2Interseccion = puntoInterseccion - v2;
//     Direccion v3Interseccion = puntoInterseccion - v3;

//     // Calcular los vectores normales de cada uno de los tres planos formados por el punto de intersección y dos vértices del triángulo
//     Direccion normal1 = v1Interseccion.cross(v2Interseccion).normalizar();
//     Direccion normal2 = v2Interseccion.cross(v3Interseccion).normalizar();
//     Direccion normal3 = v3Interseccion.cross(v1Interseccion).normalizar();

//     // Si los vectores normales tienen la misma dirección que la normal del triángulo, entonces el punto de intersección está dentro del triángulo
//     if (normal1 * normal >= 0 && normal2 * normal >= 0 && normal3 * normal >= 0) {
//         return puntoInterseccion; // Devolver el punto de intersección
//     }

//     return Punto(-INFINITY, -INFINITY, -INFINITY); // Devolver un punto nulo si no hay intersección
// }


Punto Triangulo::interseccion(const Rayo& rayo) const {
    Punto v1 = getVertice1();
    Punto v2 = getVertice2();
    Punto v3 = getVertice3();

    // Calcular el vector normal del triángulo
    Direccion normal = (v2 - v1).cross(v3 - v1).normalizar();

    // Calcular el vector de dirección del rayo y su origen
    Direccion rayDirection = rayo.getDireccion();
    Punto rayOrigin = rayo.getOrigen();

    const float EPSILON = 0.0000001;
    Direccion vertex0 = v1 - rayOrigin;
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
