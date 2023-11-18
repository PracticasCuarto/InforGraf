#include "PathTracer.hpp"

using namespace std;

void crearSistemaCoordenadas(const Direccion& N, Direccion& Nt, Direccion& Nb) {
    if (std::fabs(N.x) > std::fabs(N.y))
        Nt = Direccion(N.z, 0, -N.x) / sqrtf(N.x * N.x + N.z * N.z);
    else
        Nt = Direccion(0, -N.z, N.y) / sqrtf(N.y * N.y + N.z * N.z);
    Nb = N.cross(Nt);
}

// Función para generar un rayo aleatorio en base a coordenadas esféricas
Rayo generarRayoAleatorio(const Punto& puntoInterseccion, const Direccion& normal) {
    double r1 = random_double();
    double r2 = random_double();
    double theta = 2.0 * M_PI * r1; // Ángulo azimut
    double phi = acos(sqrt(1.0 - r2)); // Ángulo polar

    // Convertir a coordenadas esféricas
    double x = cos(theta) * sin(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(phi);

    Direccion direccionAleatoria = Direccion(x, y, z);

    // Generar la base local

    Direccion eje1 = Direccion(-INFINITY, -INFINITY, -INFINITY);
    Direccion eje2 = Direccion(-INFINITY, -INFINITY, -INFINITY);

    crearSistemaCoordenadas(normal, eje1, eje2);

    eje1 = eje1.normalizar();
    eje2 = eje2.normalizar();

    // Cambiar de base utilizando una matriz generada 
    Matriz matrizBase = Matriz(
        eje1.x, eje2.x, normal.x, 0,
        eje1.y, eje2.y, normal.y, 0,
        eje1.z, eje2.z, normal.z, 0,
        0, 0, 0, 1
    );

    // Cambiar a la base del mundo la dirección del rayo
    Direccion direccionRayo = direccionAleatoria.multiplicarMatriz(matrizBase).normalizar();
    return Rayo(puntoInterseccion, direccionRayo);
}

Color calcularMaterialDifuso(const Color& color, const Punto& puntoInterseccion) {
    // Dividir cada componente del color entre pi
    double r = (color.r / M_PI);
    double g = (color.g / M_PI);
    double b = (color.b / M_PI);

    return Color(r, g, b);
}

// Constructor vacio
PathTracer::PathTracer() {}

// Constructor
PathTracer::PathTracer(const vector<Geometria*>& _objetos, const vector<FuenteLuz*>& _fuentes) {
    // Copiar los objetos
    for (const auto& objeto : _objetos) {
        objetos.push_back(objeto); // Asumiendo que Geometria tiene un constructor de copia
    }

    // Copiar las fuentes
    for (const auto& fuente : _fuentes) {
        fuentes.push_back(fuente); // Asumiendo que FuenteLuz tiene un constructor de copia
    }
}

// Función para calcular la luz incidente de una fuente en un punto de intersección
Color PathTracer::calcularLuzIncidente(const FuenteLuz& fuente, const Punto& puntoInterseccion) const {
    double wi = (fuente.getOrigen() - puntoInterseccion).modulo();
    return (fuente.getEnergia() / (wi * wi));
}

// Calcular si el rayo que une un punto y la luz tiene alguna colision en su camino
bool PathTracer::interseccionaObjetoAntesLuz(const Punto& puntoInterseccion, const Direccion& direccion, const Punto& origenFuente) const {
    // Calcular la distancia entre el punto y el origen de la fuente de luz
    double distancia = puntoInterseccion.distancia(origenFuente);
    Rayo rayo = Rayo(puntoInterseccion, direccion);

    for (int k = 0; k < objetos.size(); k++) {
        // Comprobar el punto de interseccion con el objeto
        Punto puntoInterseccionObjeto = objetos[k]->interseccion(rayo);

        // Comprobar si la interseccion es válida
        bool interseccion = puntoInterseccionObjeto.x != -INFINITY;
        bool interseccionValida = puntoInterseccionObjeto.distancia(puntoInterseccion) < distancia;
        if (interseccion && interseccionValida) {
            return true;
        }
    }
    return false;
}

// Función para calcular la luz directa de una fuente en un punto de intersección
Color PathTracer::luzDirecta(const Punto& puntoInterseccion, const Color& BRDF, const Direccion& normal) const {
    Color resultado = Color(0, 0, 0);
    // Calcular la luz directa a partir de las fuentes de luz
    for (FuenteLuz* fuente : fuentes) {
        Punto origenFuente = fuente->getOrigen();
        Direccion wi = (origenFuente - (puntoInterseccion)).normalizar();

        if (interseccionaObjetoAntesLuz(puntoInterseccion, wi, origenFuente)) {
            continue;
        }

        Color luzIncidente = calcularLuzIncidente(*fuente, puntoInterseccion);
        double coseno = abs(normal * wi);
        Color material = luzIncidente * BRDF * coseno;

        // Calcular el color del pixel
        resultado += material;
    }
    return resultado;
}

// Función para calcular la luz de un objeto en un punto de intersección
Color PathTracer::nextEventEstimation(const Punto puntoInterseccion, const Material& materialObjeto, const Direccion& normal, const Direccion& wo, const Punto& origin, const int& iteracion) const {
    Color resultado = Color(0, 0, 0);

    // Comprobar a que clase pertenece el material y en funcion de su clase calcular
    // la luz directa
    TipoMaterial tipo = materialObjeto.tipo;
    if (tipo == DIFUSO) {
        resultado = calcularComponenteDifusa(materialObjeto, puntoInterseccion, normal, origin, iteracion);
    }
    else if (tipo == PLASTICO) {
        resultado = calcularComponenteEspecular(materialObjeto, puntoInterseccion, wo, normal, iteracion);
    }
    else if (tipo == DIELECTRICO) {
        // resultado = calcularComponenteEspecular(materialObjeto, puntoInterseccion, wi, normal, normal);
    }
    else {
        cout << "Error: tipo de material no reconocido" << endl;
    }
    return resultado;
}

// Función para calcular el color de un píxel
Color PathTracer::calcularColorPixel(const Rayo& rayo, const Punto& origin, const int& iteracion) const {
    // Definir valores iniciales
    Material material = Material();
    float distancia = INFINITY;
    Punto puntoInterseccion = Punto(-INFINITY, -INFINITY, -INFINITY);
    Direccion normal = Direccion(-INFINITY, -INFINITY, -INFINITY);
    int indice = -1;
    int indiceResultado = -1;

    // Calcular la interseccion del rayo con todos los objetos de la escena
    // y guardar la interseccion más cercana
    for (Geometria* objeto : objetos) {
        indice++;
        Punto puntoInterseccionObjeto = objeto->interseccion(rayo);
        if (puntoInterseccionObjeto.x == -INFINITY) {
            continue;
        }

        // Calcular la distancia entre el origen del rayo y el punto de interseccion
        float distanciaInterseccion = origin.distancia(puntoInterseccionObjeto);
        if (distanciaInterseccion <= distancia) {
            distancia = distanciaInterseccion;
            material = objeto->getMaterial();
            puntoInterseccion = puntoInterseccionObjeto;
            normal = objeto->getNormal(puntoInterseccion);
            puntoInterseccion = puntoInterseccion + normal * 0.0001;
            indiceResultado = indice;
        }
    }

    if (distancia == INFINITY) {
        // No hay interseccion
        return Color(0, 0, 0);
    }
    else if (objetos[indiceResultado]->esFuenteLuz()) {
        // Es una fuente de luz directa
        return objetos[indiceResultado]->getMaterial().getDifuso();
    }
    else if (iteracion >= 10) {
        return Color(0, 0, 0);
    }
    else {
        return nextEventEstimation(puntoInterseccion, material, normal, rayo.getDireccion(), origin, iteracion);
    }
}

// Función para calcular la componente difusa de un material
Color PathTracer::calcularComponenteDifusa(const Material& material, const Punto& puntoInterseccion, const Direccion& normal, const Punto& origin, const int& iteracion) const {
    // Dividir cada componente del color entre pi
    Color difuso = material.getDifuso();
    Color BRDF = calcularMaterialDifuso(difuso, puntoInterseccion);

    Direccion wo = (origin - puntoInterseccion).normalizar();

    // Calcular luz directa
    Color resultado = luzDirecta(puntoInterseccion, BRDF, normal);

    // Calcular luz indirecta
    Rayo rayo = generarRayoAleatorio(puntoInterseccion, normal);
    Color color = calcularColorPixel(rayo, puntoInterseccion, iteracion + 1);


    resultado += color * BRDF * M_PI;
    return resultado;
}

// Calcular componente especular de un material
Color PathTracer::calcularComponenteEspecular(const Material& material, const Punto& puntoInterseccion, const Direccion& wo, const Direccion& n, const int& iteracion) const {
    // Calcular la direccion del rayo reflejado
    Direccion wi = wo - (n * (2 * (wo * n)));
    wi = wi.normalizar();

    // Lanzar un rayo a la escena
    Rayo rayo = Rayo(puntoInterseccion, wi);
    Color color = calcularColorPixel(rayo, puntoInterseccion, iteracion + 1);

    Color especular = material.getEspecular();
    return especular * color;

}

// Calcular componente refractante de un material
Color PathTracer::calcularComponenteRefractante(const Material& material, const Punto& puntoInterseccion, const Direccion& wo, const Direccion& n, const int& iteracion) const {

    // int indiceRefraccion =
        // Diferenciar si estamos entrando o saliendo del objeto


        // Calcular la direccion del rayo reflejado

    Direccion wi = wo - (n * (2 * (wo * n)));
    wi = wi.normalizar();

    // Lanzar un rayo a la escena
    Rayo rayo = Rayo(puntoInterseccion, wi);
    Color color = calcularColorPixel(rayo, puntoInterseccion, iteracion + 1);

    Color especular = material.getEspecular();
    return especular * color;

}