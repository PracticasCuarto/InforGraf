
#include "Geometria.hpp"
#include <iostream>
#include <string> 

using namespace std;

// Constructor de Geometria
Geometria::Geometria() {}

// Constructor esfera
Esfera::Esfera(Punto _centro, double _radio) : Geometria(), centro(_centro), radio(_radio) {}

// Getters de la esfera
Punto Esfera::getCentro() const {
    return centro;
}

double Esfera::getRadio() const {
    return radio;
}

// Constructor plano
Plano::Plano(double _distanciaOrigen, Direccion _normal) : Geometria(), distanciaOrigen(_distanciaOrigen), normal(_normal) {}

// Getters del plano
double Plano::getDistanciaOrigen() const {
    return distanciaOrigen;
}

Direccion Plano::getNormal() const {
    return normal;
}

// Constructor Triangulo
Triangulo::Triangulo(Punto _p1, Punto _p2, Punto _p3) : vertice1(_p1), vertice2(_p2), vertice3(_p3) {}

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

// Constructor Rayo
Rayo::Rayo(Punto _origen, Direccion _direccion) : origen(_origen), direccion(_direccion) {}

// Getters del Rayo
Punto Rayo::getOrigen() const {
    return origen;
}

Direccion Rayo::getDireccion() const {
    return direccion;
}

// Calcular intersección con un plano
Punto Rayo::interseccion(const Plano& plano) const {
    Direccion normalPlano = plano.getNormal();
    double A = normalPlano.x;
    double B = normalPlano.y;
    double C = normalPlano.z;
    double D = plano.getDistanciaOrigen();

    Direccion direccionRayo = getDireccion();
    double dx = direccionRayo.x;
    double dy = direccionRayo.y;
    double dz = direccionRayo.z;

    Punto origenRayo = getOrigen();
    double xo = origenRayo.x;
    double yo = origenRayo.y;
    double zo = origenRayo.z;

    double denominador = A * dx + B * dy + C * dz;

    if (denominador == 0) {
        // El rayo es paralelo al plano, no hay intersección.
        // Puedes manejar este caso de acuerdo a tus necesidades.
        // Por ejemplo, lanzando una excepción o devolviendo un valor especial.
        // Aquí, se devuelve un punto fuera del mundo (-infinito) como indicador de no intersección.
        return Punto(-INFINITY, -INFINITY, -INFINITY);
    }

    double t = -(A * xo + B * yo + C * zo + D) / denominador;

    Punto puntoInterseccion(xo + t * dx, yo + t * dy, zo + t * dz);

    return puntoInterseccion;
}

// Calcular intersección de un Rayo con una esfera
Punto Rayo::interseccion(const Esfera& esfera) const {
    Punto centroEsfera = esfera.getCentro();
    double radioEsfera = esfera.getRadio();

    Direccion direccionRayo = getDireccion();
    double dx = direccionRayo.x;
    double dy = direccionRayo.y;
    double dz = direccionRayo.z;

    Punto origenRayo = getOrigen();
    double xo = origenRayo.x;
    double yo = origenRayo.y;
    double zo = origenRayo.z;

    double a = dx * dx + dy * dy + dz * dz;
    double b = 2 * (dx * (xo - centroEsfera.x) + dy * (yo - centroEsfera.y) + dz * (zo - centroEsfera.z));
    double c = (xo - centroEsfera.x) * (xo - centroEsfera.x) + (yo - centroEsfera.y) * (yo - centroEsfera.y) + (zo - centroEsfera.z) * (zo - centroEsfera.z) - radioEsfera * radioEsfera;

    double discriminante = b * b - 4 * a * c;

    if (discriminante < 0) {
        // El Rayo no intersecta la esfera.
        // Puedes manejar este caso de acuerdo a tus necesidades.
        // Por ejemplo, lanzando una excepción o devolviendo un valor especial.
        // Aquí, se devuelve un punto fuera del mundo (-infinito) como indicador de no intersección.
        return Punto(-INFINITY, -INFINITY, -INFINITY);
    }

    double t1 = (-b + sqrt(discriminante)) / (2 * a);
    double t2 = (-b - sqrt(discriminante)) / (2 * a);

    if (abs(t1) == abs(t2)) {
        Punto puntoInterseccion = origenRayo + direccionRayo * t1;
        return puntoInterseccion;
    }
    else {
        double t;
        if (abs(t1) > abs(t2)) {
            t = t2;
        }
        else {
            t = t1;
        }
        cout << "t: " << t << endl;

        // Calcular el punto de intersección
        Punto puntoInterseccion = origenRayo + direccionRayo * t;
        return puntoInterseccion;
    }
}

// Calcular intersección de un Rayo con un Triangulo
Punto Rayo::interseccion(const Triangulo& triangulo) const {
    // Obtener los vértices del triángulo
    Punto v1 = triangulo.getVertice1();
    Punto v2 = triangulo.getVertice2();
    Punto v3 = triangulo.getVertice3();

    // Calcular el vector normal del triángulo
    Direccion normal = (v2 - v1).cross(v3 - v1).normalizar();

    cout << "normal.x: " << normal.x << endl;
    cout << "normal.y: " << normal.y << endl;
    cout << "normal.z: " << normal.z << endl;

    // Calcular la distancia del plano del triángulo al origen del rayo
    double denominador = normal * direccion;

    if (denominador == 0) {
        // El rayo es paralelo al plano, no hay intersección.
        // Puedes manejar este caso de acuerdo a tus necesidades.
        // Por ejemplo, lanzando una excepción o devolviendo un valor especial.
        // Aquí, se devuelve un punto fuera del mundo (-infinito) como indicador de no intersección.
        return Punto(-INFINITY, -INFINITY, -INFINITY);
    }

    double distanciaPlano = (normal * (v1 - origen)) / denominador;


    cout << "distanciaPlano: " << distanciaPlano << endl;

    // Si la distancia es negativa, el rayo está apuntando en la dirección opuesta al plano del triángulo
    if (distanciaPlano < 0) {
        return Punto(-INFINITY, -INFINITY, -INFINITY); // Devolver un punto nulo si no hay intersección
    }

    // Calcular el punto de intersección con el plano del triángulo
    Punto puntoInterseccion = origen + direccion * distanciaPlano;

    // Calcular los vectores desde el punto de intersección hacia cada vértice del triángulo
    Direccion v1Interseccion = puntoInterseccion - v1;
    Direccion v2Interseccion = puntoInterseccion - v2;
    Direccion v3Interseccion = puntoInterseccion - v3;

    // Calcular los vectores normales de cada uno de los tres planos formados por el punto de intersección y dos vértices del triángulo
    Direccion normal1 = v1Interseccion.cross(v2Interseccion).normalizar();
    Direccion normal2 = v2Interseccion.cross(v3Interseccion).normalizar();
    Direccion normal3 = v3Interseccion.cross(v1Interseccion).normalizar();

    // Si los vectores normales tienen la misma dirección que la normal del triángulo, entonces el punto de intersección está dentro del triángulo
    if (normal1 * normal >= 0 && normal2 * normal >= 0 && normal3 * normal >= 0) {
        return puntoInterseccion; // Devolver el punto de intersección
    }

    return Punto(-INFINITY, -INFINITY, -INFINITY); // Devolver un punto nulo si no hay intersección
}
