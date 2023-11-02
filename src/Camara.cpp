#include "Camara.hpp"
#include <iostream>
#include <string> 
#include <thread>
#include <mutex>

#include "Matriz.hpp"
#include "RandomNumber.hpp"

using namespace std;

// Mutex para proteger la matriz de imagen compartida
std::mutex mtx;

Camara::Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin)
    : up(_up), left(_left), forward(_forward), origin(_origin), base(
        left.x, up.x, forward.x, origin.x,
        left.y, up.y, forward.y, origin.y,
        left.z, up.z, forward.z, origin.z,
        0, 0, 0, 1
    ) {
    // Resto del código del constructor
    width = 512;
    height = 512;

    // Normalizar vectores left y up
    left = left.normalizar();
    up = up.normalizar();
}

// Constructor completo incluyendo anchura, altura y muestras por pixel
Camara::Camara(Direccion _left, Direccion _up, Direccion _forward, Punto _origin, int _width, int _height, int _numMuestras, int _resolucion)
    : up(_up), left(_left), forward(_forward), origin(_origin), base(
        left.x, up.x, forward.x, origin.x,
        left.y, up.y, forward.y, origin.y,
        left.z, up.z, forward.z, origin.z,
        0, 0, 0, 1
    ) {
    // Resto del código del constructor
    width = _width;
    height = _height;
    numMuestras = _numMuestras;
    resolucion = _resolucion;

    // Normalizar vectores left y up
    left = left.normalizar();
    up = up.normalizar();
}

// Setters
void Camara::setObjetos(const vector<Geometria*>& _objetos) {
    objetos = _objetos;
}

void Camara::setFuentes(const vector<FuenteLuz*>& _fuentes) {
    fuentes = _fuentes;
}

Color calcularMaterial(const Color& color, const Punto& puntoInterseccion) {
    // Dividir cada componente del color entre pi
    double r = (color.r / M_PI) / 255;
    double g = (color.g / M_PI) / 255;
    double b = (color.b / M_PI) / 255;

    return Color(r, g, b);
}

// Función para calcular el color de un píxel
Color Camara::calcularColorPixel(const Rayo& rayo, const int& iteracion) const {
    // Definir valores iniciales
    Color color = Color(0, 0, 0);
    float distancia = INFINITY;
    Punto puntoInterseccion = Punto(-INFINITY, -INFINITY, -INFINITY);
    Direccion normal = Direccion(-INFINITY, -INFINITY, -INFINITY);
    int indice = -1;

    // Calcular la interseccion del rayo con todos los objetos de la escena
    // y guardar la interseccion más cercana
    for (int k = 0; k < objetos.size(); k++) {
        Punto puntoInterseccionObjeto = objetos[k]->interseccion(rayo);
        if (puntoInterseccionObjeto.x != -INFINITY) {
            float distanciaInterseccion = origin.distancia(puntoInterseccionObjeto);
            if (distanciaInterseccion <= distancia) {
                distancia = distanciaInterseccion;
                color = objetos[k]->getColor();
                puntoInterseccion = puntoInterseccionObjeto;
                normal = objetos[k]->getNormal(puntoInterseccion);
                puntoInterseccion = puntoInterseccion + normal * 0.0001;
                indice = k;
            }
        }
    }

    if (indice == -1) {
        // No hay interseccion
        return Color(0, 0, 0);
    }
    else if (objetos[indice]->esFuenteLuz()) {
        // Es una fuente de luz directa
        return objetos[indice]->getColor();
    }
    else {
        return luzIndirecta(puntoInterseccion, color, normal, iteracion);
    }
}

// Calcular si el rayo que une un punto y la luz tiene alguna colision en su camino
bool Camara::interseccionObjeto(const Punto& puntoInterseccion, const Direccion& direccion, const Punto& origenFuente) const {
    // Calcular la distancia entre el punto y el origen de la fuente de luz
    double distancia = puntoInterseccion.distancia(origenFuente);
    Rayo rayo = Rayo(puntoInterseccion, direccion);

    for (int k = 0; k < objetos.size(); k++) {
        // Comprobar el punto de interseccion con el objeto
        Punto puntoInterseccionObjeto = objetos[k]->interseccion(rayo);
        bool interseccion = puntoInterseccionObjeto.x != -INFINITY;
        // Comprobar que intersecciona 
        bool interseccionValida = puntoInterseccionObjeto.distancia(puntoInterseccion) < distancia;
        if (interseccion && interseccionValida) {
            return true;
        }
    }
    return false;
}

// Función para calcular la luz incidente de una fuente en un punto de intersección
Color calcularLuzIncidente(const FuenteLuz& fuente, const Punto& puntoInterseccion) {
    Direccion wi = fuente.getOrigen() - puntoInterseccion;
    Direccion wiNormalizada = wi.normalizar();
    Color Energia = fuente.getEnergia();
    double wiModuloCuadrado = wi.modulo() * wi.modulo();
    double r = Energia.r / wiModuloCuadrado;
    double g = Energia.g / wiModuloCuadrado;
    double b = Energia.b / wiModuloCuadrado;
    return Color(r, g, b);
}

Color Camara::luzIndirecta(const Punto& puntoInterseccion, const Color& colorObjeto, const Direccion& normal, int iteracion) const {
    Color resultado = Color(0, 0, 0);
    if (iteracion >= maxIter) {
        return Color(0, 0, 0);
    }

    // Calcular material del objeto
    Color BRDF = calcularMaterial(colorObjeto, puntoInterseccion);
    resultado += luzDirecta(puntoInterseccion, BRDF, normal);

    Rayo rayo = generarRayoAleatorio(puntoInterseccion, normal);
    Color color = calcularColorPixel(rayo, iteracion + 1);

    resultado += color * BRDF * M_PI;

    return resultado;
}

// Función para calcular la luz directa de una fuente en un punto de intersección
Color Camara::luzDirecta(const Punto& puntoInterseccion, const Color& BRDF, const Direccion& normal) const {
    Color resultado = Color(0, 0, 0);
    // Calcular la luz directa a partir de las fuentes de luz
    for (FuenteLuz* fuente : fuentes) {
        Punto origenFuente = fuente->getOrigen();
        Direccion wi = (origenFuente - (puntoInterseccion)).normalizar();

        if (interseccionObjeto(puntoInterseccion, wi, origenFuente)) {
            continue;
        }
        // Direccion wo = (origin - puntoInterseccion).normalizar();

        Color luzIncidente = calcularLuzIncidente(*fuente, puntoInterseccion);
        double coseno = abs(normal * wi);
        Color material = luzIncidente * BRDF * coseno;

        // Calcular el color del pixel
        resultado += material;
    }
    return resultado;
}


// Función para calcular el color de un píxel con anti-aliasing
Color Camara::calcularColorPixelAA(int i, int j) const {
    Color colorSum = Color(0, 0, 0);

    for (int n = 0; n < numRayos; n++) {
        // Lanzar rayos a lugares aleatorios dentro del píxel
        double y = 1.0 - (2.0 * i / height - (random_double() / height));
        double x = 1.0 - (2.0 * j / width - (random_double() / width));
        Direccion direccionRayo = Direccion(x, y, 1);

        // Cambiar a la base del mundo la dirección del rayo
        Direccion direccionRayoBase = direccionRayo.cambioBase(base);

        Rayo rayo = Rayo(origin, direccionRayoBase);
        Color color = calcularColorPixel(rayo, 0);

        // Sumar el color al resultado
        colorSum.r += color.r;
        colorSum.g += color.g;
        colorSum.b += color.b;
    }

    // Calcular el promedio de los colores
    colorSum.r /= numRayos;
    colorSum.g /= numRayos;
    colorSum.b /= numRayos;

    return colorSum;
}


// Función para calcular una región de píxeles utilizando múltiples hilos con anti-aliasing
void Camara::calcularRegionDePixeles(vector<vector<double>>& matrizImagen, int inicioFila, int finFila) const {
    for (int i = inicioFila; i < finFila; i++) {
        for (int j = 0; j < width; j++) {
            Color color = calcularColorPixelAA(i, j);

            // Agregar el color del objeto a la matriz
            int index = 3 * j;
            matrizImagen[i][index] = color.r / 255;
            matrizImagen[i][index + 1] = color.g / 255;
            matrizImagen[i][index + 2] = color.b / 255;
        }
    }
}


ImagenHDR Camara::renderizar(vector<Geometria*> objetos, vector<FuenteLuz*> fuentes) {
    unsigned int numCores = std::thread::hardware_concurrency();
    if (numCores == 0) {
        // No se puede determinar el número de cores
        numCores = 1;
    }
    // numCores = 1;

    // Asignar los objetos y las fuentes de luz
    setObjetos(objetos);
    setFuentes(fuentes);

    vector<vector<double>> matrizImagen(height, vector<double>(3 * width)); // Inicializar matriz de imagen
    vector<thread> threads;

    int filasPorHilo = height / numCores;
    for (int i = 0; i < numCores; i++) {
        int inicioFila = i * filasPorHilo;
        int finFila = (i == numCores - 1) ? height : (i + 1) * filasPorHilo;
        threads.emplace_back(&Camara::calcularRegionDePixeles, this, std::ref(matrizImagen), inicioFila, finFila);
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    // Crear la imagenHDR
    ImagenHDR imagen = ImagenHDR(matrizImagen, width, height, 0, 255);
    return imagen;
}