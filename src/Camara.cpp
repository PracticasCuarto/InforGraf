#include "Camara.hpp"
#include <iostream>
#include <string> 
#include <thread>
#include <mutex>
#include <random>
#include "Matriz.hpp"

using namespace std;

// Mutex para proteger la matriz de imagen compartida
std::mutex mtx;

// Función para generar un número aleatorio en el rango [0, 1)
double random_double() {
    static std::random_device rd;
    static std::mt19937 generator(rd()); // Inicializa el generador con una semilla aleatoria
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

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

pixel multiplicarColores(const pixel& color1, const pixel& color2) {
    return Pixel(color1.r * color2.r, color1.g * color2.g, color1.b * color2.b);
}

pixel calcularMaterial(const pixel& color, const Direccion& wi, const Direccion& wo, const Punto& puntoInterseccion) {
    // Dividir cada componente del color entre pi
    double r = color.r / M_PI;
    double g = color.g / M_PI;
    double b = color.b / M_PI;

    return Pixel(r, g, b);
}

// Función para calcular el color de un píxel
pixel Camara::calcularColorPixel(const vector<Geometria*>& objetos, const vector<FuenteLuz*>& fuentes, const Rayo& rayo) const {
    pixel color = Pixel(0, 0, 0);
    float distancia = INFINITY;
    Punto puntoInterseccion = Punto(-INFINITY, -INFINITY, -INFINITY);
    Direccion normal = Direccion(-INFINITY, -INFINITY, -INFINITY);
    int indice = -1;
    for (int k = 0; k < objetos.size(); k++) {
        Punto puntoInterseccionObjeto = objetos[k]->interseccion(rayo);
        if (puntoInterseccionObjeto.x != -INFINITY) {
            float distanciaInterseccion = origin.distancia(puntoInterseccionObjeto);
            if (distanciaInterseccion <= distancia) {
                distancia = distanciaInterseccion;
                color = objetos[k]->getColor();
                puntoInterseccion = puntoInterseccionObjeto;
                normal = objetos[k]->getNormal(puntoInterseccion);
                indice = k;
            }
        }
    }

    pixel resultado = luzIndirecta(objetos, fuentes, puntoInterseccion, color, normal, indice);

    return resultado;
}

// Calcular si el rayo que une un punto y la luz tiene alguna colision en su camino
bool interseccionObjeto(const vector<Geometria*>& objetos, const Punto& puntoInterseccion, const Direccion& direccion, int indice, const Punto& origenFuente) {
    // Calcular la distancia entre el punto y el origen de la fuente de luz
    double distancia = puntoInterseccion.distancia(origenFuente);
    Rayo rayo = Rayo(puntoInterseccion, direccion);

    for (int k = 0; k < objetos.size(); k++) {
        // Si es la clase plano o triangulo saltar la iteracion
        bool biDimensional = dynamic_cast<Plano*>(objetos[k]) || dynamic_cast<Triangulo*>(objetos[k]);
        if (k == indice && biDimensional) {
            continue;
        }

        // Comprobar el punto de interseccion con el objeto
        Punto puntoInterseccionObjeto = objetos[k]->interseccion(rayo);
        bool interseccion = puntoInterseccionObjeto.x != -INFINITY;
        bool interseccionValida = puntoInterseccionObjeto.distancia(puntoInterseccion) < distancia;
        if (interseccion && interseccionValida) {
            return true;
        }
    }
    return false;
}

pixel Camara::luzIndirecta(const vector<Geometria*>& objetos, const vector<FuenteLuz*>& fuentes, const Punto& puntoInterseccion, const pixel& colorObjeto, const Direccion& normal, int indice) const {
    pixel resultado = Pixel(0, 0, 0);

    // Calcular en base al punto de interseccion y las fuentes de luz el color del pixel
    for (int k = 0; k < fuentes.size(); k++) {
        Direccion wi = fuentes[k]->getOrigen() - (puntoInterseccion);
        Direccion wiNormalizada = wi.normalizar();

        if (interseccionObjeto(objetos, puntoInterseccion, wiNormalizada, indice, fuentes[k]->getOrigen())) {
            continue;
        }

        Direccion wo = (origin - puntoInterseccion).normalizar();

        // Luz incidente
        pixel Energia = fuentes[k]->getEnergia();
        double wiModuloCuadrado = wi.modulo() * wi.modulo();
        double r = Energia.r / wiModuloCuadrado;
        double g = Energia.g / wiModuloCuadrado;
        double b = Energia.b / wiModuloCuadrado;
        pixel luzIncidente = Pixel(r, g, b);

        // cout << "Luz incidente: " << luzIncidente.r << " " << luzIncidente.g << " " << luzIncidente.b << endl;

        // Calcular material del objeto
        pixel material = calcularMaterial(colorObjeto, wi, wo, puntoInterseccion);

        material = multiplicarColores(material, luzIncidente);
        // cout << "Material: " << material.r << " " << material.g << " " << material.b << endl;

        //  Calcular el termino del coseno
        double coseno = normal * wiNormalizada;
        coseno = abs(coseno);

        // cout << "Coseno: " << coseno << endl;

        // Calcular el color del pixel
        resultado.r += material.r * coseno;
        resultado.g += material.g * coseno;
        resultado.b += material.b * coseno;
    }
    return resultado;
}


// Función para calcular el color de un píxel con anti-aliasing
pixel Camara::calcularColorPixelAA(const vector<Geometria*>& objetos, const vector<FuenteLuz*>& fuentes, int i, int j) const {
    pixel colorSum = Pixel(0, 0, 0);

    for (int n = 0; n < numRayos; n++) {
        // Lanzar rayos a lugares aleatorios dentro del píxel
        // double y = 1.0 - (2.0 * (i + random_double()) / height);
        // double x = 1.0 - (2.0 * (j + random_double()) / width);
        double y = 1.0 - (2.0 * i / height - (random_double() / height));
        double x = 1.0 - (2.0 * j / width - (random_double() / width));
        Direccion direccionRayo = Direccion(x, y, 1);

        // Cambiar a la base del mundo la dirección del rayo
        Direccion direccionRayoBase = direccionRayo.cambioBase(base);

        Rayo rayo = Rayo(origin, direccionRayoBase);
        pixel color = calcularColorPixel(objetos, fuentes, rayo);

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
void Camara::calcularRegionDePixeles(const vector<Geometria*>& objetos, const vector<FuenteLuz*>& fuentes, vector<vector<double>>& matrizImagen, int inicioFila, int finFila) const {
    for (int i = inicioFila; i < finFila; i++) {
        for (int j = 0; j < width; j++) {
            pixel color = calcularColorPixelAA(objetos, fuentes, i, j);

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

    vector<vector<double>> matrizImagen(height, vector<double>(3 * width)); // Inicializar matriz de imagen
    vector<thread> threads;

    int filasPorHilo = height / numCores;
    for (int i = 0; i < numCores; i++) {
        int inicioFila = i * filasPorHilo;
        int finFila = (i == numCores - 1) ? height : (i + 1) * filasPorHilo;
        threads.emplace_back(&Camara::calcularRegionDePixeles, this, std::ref(objetos), std::ref(fuentes), std::ref(matrizImagen), inicioFila, finFila);
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    // Crear la imagenHDR
    ImagenHDR imagen = ImagenHDR(matrizImagen, width, height, 0, 255);
    return imagen;
}