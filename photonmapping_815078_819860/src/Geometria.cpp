
#include "Geometria.hpp"
#include <iostream>
#include <string> 

using namespace std;

// Constructor de Geometria
Geometria::Geometria() : material(Material()), fuenteLuz(false) {}

// Constructor de Geometria con material
Geometria::Geometria(Material _material) : material(_material), fuenteLuz(false) {}

// Getters del material
Material Geometria::getMaterial() const {
    return material;
}

bool Geometria::esFuenteLuz() const {
    return fuenteLuz;
}

// Setters del material
void Geometria::setMaterial(Material _material) {
    material = _material;
}

// --------------------- ESFERA ---------------------

// Constructor esfera
Esfera::Esfera(Punto _centro, double _radio) : Geometria(), centro(_centro), radio(_radio) {}

// Constructor esfera con color 
Esfera::Esfera(Punto _centro, double _radio, Material _material) : Geometria(), centro(_centro), radio(_radio) {
    setMaterial(_material);
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
Plano::Plano(double _distanciaOrigen, Direccion _normal, Material _material) : Geometria(), distanciaOrigen(_distanciaOrigen), normal(_normal) {
    setMaterial(_material);
}

// Constructor plano con color y fuente de luz
Plano::Plano(double _distanciaOrigen, Direccion _normal, Material _material, bool _fuenteLuz) : Geometria(), distanciaOrigen(_distanciaOrigen), normal(_normal) {
    setMaterial(_material);
    fuenteLuz = _fuenteLuz;
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
Triangulo::Triangulo(Punto _p1, Punto _p2, Punto _p3, Material _material) : vertice1(_p1), vertice2(_p2), vertice3(_p3) {
    setMaterial(_material);
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

// --------------------- CILINDRO ---------------------

// Constructor Cilindro
Cilindro::Cilindro(Punto _centro, double _radio, double _altura) : Geometria(), centro(_centro), radio(_radio), altura(_altura) {}

// Constructor Cilindro con color
Cilindro::Cilindro(Punto _centro, double _radio, double _altura, Material _material) : Geometria(), centro(_centro), radio(_radio), altura(_altura) {
    setMaterial(_material);
}

// Getters del Cilindro
Punto Cilindro::getCentro() const {
    return centro;
}

double Cilindro::getRadio() const {
    return radio;
}

double Cilindro::getAltura() const {
    return altura;
}

// Dado un punto del cilindro devuelva la direccion normal (con respecto al origen)
Direccion Cilindro::getNormal(const Punto& punto) const {
    Direccion normal = punto - centro;
    return normal.normalizar();
}

// --------------------- CUBO ---------------------

// Constructor del cubo
Cubo::Cubo(Punto _centro, double _lado) : Geometria(), centro(_centro), lado(_lado) {}

// Constructor del cubo con color
Cubo::Cubo(Punto _centro, double _lado, Material _material) : Geometria(), centro(_centro), lado(_lado) {
    setMaterial(_material);
}

// Getters del cubo
Punto Cubo::getCentro() const {
    return centro;
}

double Cubo::getLado() const {
    return lado;
}

// Dado un punto del cubo devuelva la direccion normal (con respecto al origen)
Direccion Cubo::getNormal(const Punto& punto) const {
    Direccion normal = punto - centro;
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
        // cout << "No hay interseccion" << endl;
        return Punto(-INFINITY, -INFINITY, -INFINITY);
    }

    bool dentro = false;

    // Comprobar que son iguales
    if (L.modulo() <= radio) {
        dentro = true;
    }

    Punto puntoInterseccion = Punto(-INFINITY, -INFINITY, -INFINITY);

    // Devolver la solución más cercana al origen del rayo
    if (t0 < t1) {
        if (!dentro) {
            puntoInterseccion = rayo.getOrigen() + direccionRayo * t0;
        }
        else {
            puntoInterseccion = rayo.getOrigen() + direccionRayo * t1;
        }
    }
    else {
        if (!dentro) {
            puntoInterseccion = rayo.getOrigen() + direccionRayo * t1;
        }
        else {
            puntoInterseccion = rayo.getOrigen() + direccionRayo * t0;
        }
    }

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
    // t = -t;

    if (t > EPSILON) {
        Punto puntoInterseccion = rayOrigin + (rayDirection * t);
        return puntoInterseccion;
    }
    else {
        return Punto(-INFINITY, -INFINITY, -INFINITY); // Devolver un punto nulo si no hay intersección
    }
}


// Calcular intersección de un Rayo con un cilindro
Punto Cilindro::interseccion(const Rayo& rayo) const {
    float t0, t1; // soluciones para t si el rayo intersecta
    Direccion L = rayo.getOrigen() - centro; // L será el vector que apunta del centro del cilindro al origen de la camara
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
    float a = direccionRayo.x * direccionRayo.x + direccionRayo.z * direccionRayo.z;
    float b = 2 * (direccionRayo.x * L.x + direccionRayo.z * L.z);
    float c = L.x * L.x + L.z * L.z - radio * radio;

    // Usa la función resolverCuadratica para calcular las soluciones
    if (!resolverCuadratica(a, b, c, t0, t1)) {
        // No hay intersección
        return Punto(-INFINITY, -INFINITY, -INFINITY);
    }

    bool dentro = false;

    // Comprobar que son iguales
    if (L.modulo() <= radio) {
        dentro = true;
    }

    Punto puntoInterseccion = Punto(-INFINITY, -INFINITY, -INFINITY);

    // Devolver la solución más cercana al origen del rayo
    if (t0 < t1) {
        if (!dentro) {
            puntoInterseccion = rayo.getOrigen() + direccionRayo * t0;
        }
        else {
            puntoInterseccion = rayo.getOrigen() + direccionRayo * t1;
        }
    }
    else {
        if (!dentro) {
            puntoInterseccion = rayo.getOrigen() + direccionRayo * t1;
        }
        else {
            puntoInterseccion = rayo.getOrigen() + direccionRayo * t0;
        }
    }

    // Comprobar que el punto de intersección está dentro de la altura del cilindro
    if (puntoInterseccion.y < centro.y || puntoInterseccion.y > centro.y + altura) {
        return Punto(-INFINITY, -INFINITY, -INFINITY);
    }

    return puntoInterseccion;
}

// Calcular intersección de un Rayo con un cubo
Punto Cubo::interseccion(const Rayo& rayo) const {
    // Transformar el rayo al espacio local del cubo
    Direccion direccionRayo = rayo.getDireccion();
    Punto origenRayo = rayo.getOrigen();
    
    Punto origenLocal = Punto(
        origenRayo.x - centro.x,
        origenRayo.y - centro.y,
        origenRayo.z - centro.z
    );

    Direccion direccionLocal = Direccion(
        direccionRayo.x / lado,
        direccionRayo.y / lado,
        direccionRayo.z / lado
    );
    
    // Calcular intersección con el cubo en el espacio local
    double tmin = -INFINITY, tmax = INFINITY;
    
    for (int i = 0; i < 3; ++i) {
        if (fabs(direccionLocal[i]) < 1e-6) {
            if (origenLocal[i] < -lado / 2.0 || origenLocal[i] > lado / 2.0) {
                // El rayo es paralelo a una cara del cubo y está fuera del cubo
                return Punto(-INFINITY, -INFINITY, -INFINITY);
            }
        } else {
            double ood = 1.0 / direccionLocal[i];
            double t1 = (-lado / 2.0 - origenLocal[i]) * ood;
            double t2 = (lado / 2.0 - origenLocal[i]) * ood;
            
            if (t1 > t2) {
                std::swap(t1, t2);
            }
            
            tmin = std::max(tmin, t1);
            tmax = std::min(tmax, t2);
            
            if (tmin > tmax) {
                // El rayo no intersecta con el cubo
                return Punto(-INFINITY, -INFINITY, -INFINITY);
            }
        }
    }
    
    // Calcular el punto de intersección en el espacio local
    Punto puntoInterseccionLocal = origenLocal + direccionLocal * tmin;
    
    // Transformar el punto de intersección al espacio global
    Punto puntoInterseccionGlobal = Punto(
        puntoInterseccionLocal.x + centro.x,
        puntoInterseccionLocal.y + centro.y,
        puntoInterseccionLocal.z + centro.z
    );
    
    return puntoInterseccionGlobal;
}


// // Calcular intersección de un Rayo con un cubo
// Punto Cubo::interseccion(const Rayo& rayo) const {
//     Direccion direccionRayo = rayo.getDireccion();
//     Punto origenRayo = rayo.getOrigen();

//     double tNear = -INFINITY;
//     double tFar = INFINITY;

//     // Verificar cada plano del cubo
//     for (int i = 0; i < 3; ++i) {
//         double invD = 1.0 / direccionRayo[i];
//         double t0 = (getCentro()[i] - getLado() / 2.0 - origenRayo[i]) * invD;
//         double t1 = (getCentro()[i] + getLado() / 2.0 - origenRayo[i]) * invD;

//         if (t0 > t1) {
//             std::swap(t0, t1);
//         }

//         tNear = std::max(tNear, t0);
//         tFar = std::min(tFar, t1);

//         if (tNear > tFar) {
//             // No hay intersección con este plano
//             return Punto(-INFINITY, -INFINITY, -INFINITY);
//         }
//     }

//     // Verificar si el punto de intersección está dentro del rango del cubo en todas las dimensiones
//     if (tNear > 0) {
//         Punto puntoInterseccion = origenRayo + direccionRayo * tNear;

//         if (puntoInterseccion.x < getCentro().x - getLado() / 2.0 || puntoInterseccion.x > getCentro().x + getLado() / 2.0) {
//             // El punto de intersección está fuera del rango del cubo
//             return Punto(-INFINITY, -INFINITY, -INFINITY);
//         }

//         if (puntoInterseccion.y < getCentro().y - getLado() / 2.0 || puntoInterseccion.y > getCentro().y + getLado() / 2.0) {
//             // El punto de intersección está fuera del rango del cubo
//             return Punto(-INFINITY, -INFINITY, -INFINITY);
//         }

//         if (puntoInterseccion.z < getCentro().z - getLado() / 2.0 || puntoInterseccion.z > getCentro().z + getLado() / 2.0) {
//             // El punto de intersección está fuera del rango del cubo
//             return Punto(-INFINITY, -INFINITY, -INFINITY);
//         }
        

//         return puntoInterseccion;
//     }

//     // El rayo no intersecta el cubo
//     return Punto(-INFINITY, -INFINITY, -INFINITY);
// }
