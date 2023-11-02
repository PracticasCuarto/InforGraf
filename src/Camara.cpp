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

pixel multiplicarColores(const pixel& color1, const double& valor) {
    return Pixel(color1.r * valor, color1.g * valor, color1.b * valor);
}

pixel sumarColores(const pixel& color1, const pixel& color2) {
    return Pixel(color1.r + color2.r, color1.g + color2.g, color1.b + color2.b);
}

pixel calcularMaterial(const pixel& color, const Punto& puntoInterseccion) {
    // Dividir cada componente del color entre pi
    double r = (color.r / M_PI) / 255;
    double g = (color.g / M_PI) / 255;
    double b = (color.b / M_PI) / 255;

    return Pixel(r, g, b);
}

// Función para calcular el color de un píxel
pixel Camara::calcularColorPixel(const vector<Geometria*>& objetos, const vector<FuenteLuz*>& fuentes, const Rayo& rayo, const int& iteracion) const {
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

    // Para cada fuente de luz comprobar si intersecta con ella antes que con un objeto de la escena.
    // Si es asi devolver el valor directamente en vez de llamar recursivamente
    // for (int k = 0; k < fuentes.size(); k++) {

    //     Direccion wi = fuentes[k]->getOrigen() - (puntoInterseccion);

    // }

    if (indice == -1) {
        return Pixel(0, 0, 0);
    }
    if (objetos[indice]->esFuenteLuz()) {
        return objetos[indice]->getColor();
    }
    pixel resultado = luzIndirecta(objetos, fuentes, puntoInterseccion, color, normal, indice, iteracion);

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
        // Comprobar que intersecciona 
        bool interseccionValida = puntoInterseccionObjeto.distancia(puntoInterseccion) < distancia;
        if (interseccion && interseccionValida) {
            return true;
        }
    }
    return false;
}

// Función para calcular la luz incidente de una fuente en un punto de intersección
pixel calcularLuzIncidente(const FuenteLuz& fuente, const Punto& puntoInterseccion) {
    Direccion wi = fuente.getOrigen() - puntoInterseccion;
    Direccion wiNormalizada = wi.normalizar();
    pixel Energia = fuente.getEnergia();
    double wiModuloCuadrado = wi.modulo() * wi.modulo();
    double r = Energia.r / wiModuloCuadrado;
    double g = Energia.g / wiModuloCuadrado;
    double b = Energia.b / wiModuloCuadrado;
    return Pixel(r, g, b);
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

    // cout << "Direccion aleatoria: " << direccionAleatoria.x << " " << direccionAleatoria.y << " " << direccionAleatoria.z << endl;
    // cout << "Normal: " << normal.x << " " << normal.y << " " << normal.z << endl;
    // Cambiar de base utilizando una matriz generada 
    Direccion aux = normal.rotacionX(10.0);
    aux = aux.rotacionY(10.0);
    aux = aux.rotacionZ(10.0);
    Direccion eje1 = normal.cross(aux);
    Direccion eje2 = normal.cross(eje1);
    // cout << "Eje 1: " << eje1.x << " " << eje1.y << " " << eje1.z << endl;
    // cout << "Eje 2: " << eje2.x << " " << eje2.y << " " << eje2.z << endl;
    Matriz matrizBase = Matriz(
        eje1.x, eje2.x, normal.x, 0,
        eje1.y, eje2.y, normal.y, 0,
        eje1.z, eje2.z, normal.z, 0,
        0, 0, 0, 1
    );

    // Cambiar a la base del mundo la dirección del rayo
    Direccion direccionRayo = direccionAleatoria.multiplicarMatriz(matrizBase);
    // cout << "Direccion rayo (cambiada): " << direccionRayo.x << " " << direccionRayo.y << " " << direccionRayo.z << endl;
    // cout << endl;
    return Rayo(puntoInterseccion, direccionRayo);
}

pixel Camara::luzIndirecta(const vector<Geometria*>& objetos, const vector<FuenteLuz*>& fuentes, const Punto& puntoInterseccion, const pixel& colorObjeto, const Direccion& normal, int indice, int iteracion) const {
    pixel resultado = Pixel(0, 0, 0);
    if (iteracion >= maxIter) {
        return Pixel(0, 0, 0);
    }

    // Calcular material del objeto
    pixel BRDF = calcularMaterial(colorObjeto, puntoInterseccion);
    // cout << "BRDF: " << BRDF.r << " " << BRDF.g << " " << BRDF.b << endl;

    // Calcular en base al punto de interseccion y las fuentes de luz el color del pixel
    for (int k = 0; k < fuentes.size(); k++) {
        Direccion wi = fuentes[k]->getOrigen() - (puntoInterseccion);
        Direccion wiNormalizada = wi.normalizar();

        if (interseccionObjeto(objetos, puntoInterseccion, wiNormalizada, indice, fuentes[k]->getOrigen())) {
            continue;
        }

        Direccion wo = (origin - puntoInterseccion).normalizar();

        pixel luzIncidente = calcularLuzIncidente(*fuentes[k], puntoInterseccion);

        //  Calcular el termino del coseno
        // double coseno = normal * wiNormalizada;
        // Calcular el arcocoseno de "coseno"
        // coseno = acos(coseno) / M_PI * 180;
        double coseno = normal * wiNormalizada;
        coseno = abs(coseno);
        pixel material = multiplicarColores(BRDF, luzIncidente);
        material = multiplicarColores(material, coseno);

        // Calcular el color del pixel
        resultado = sumarColores(resultado, material);
    }

    // cout << "Resultado: " << resultado.r << " " << resultado.g << " " << resultado.b << endl;

    Rayo rayo = generarRayoAleatorio(puntoInterseccion, normal);
    pixel color = calcularColorPixel(objetos, fuentes, rayo, iteracion + 1);

    BRDF.r = BRDF.r * M_PI;
    BRDF.g = BRDF.g * M_PI;
    BRDF.b = BRDF.b * M_PI;
    // cout << "BRDF: " << BRDF.r << " " << BRDF.g << " " << BRDF.b << endl;
    color = multiplicarColores(color, BRDF);
    // cout << "Color: " << color.r << " " << color.g << " " << color.b << endl;
    // cout << "Resultado: " << resultado.r << " " << resultado.g << " " << resultado.b << endl;
    resultado = sumarColores(resultado, color);

    return resultado;
}


// Función para calcular el color de un píxel con anti-aliasing
pixel Camara::calcularColorPixelAA(const vector<Geometria*>& objetos, const vector<FuenteLuz*>& fuentes, int i, int j) const {
    pixel colorSum = Pixel(0, 0, 0);

    for (int n = 0; n < numRayos; n++) {
        // Lanzar rayos a lugares aleatorios dentro del píxel
        double y = 1.0 - (2.0 * i / height - (random_double() / height));
        double x = 1.0 - (2.0 * j / width - (random_double() / width));
        Direccion direccionRayo = Direccion(x, y, 1);

        // Cambiar a la base del mundo la dirección del rayo
        Direccion direccionRayoBase = direccionRayo.cambioBase(base);

        Rayo rayo = Rayo(origin, direccionRayoBase);
        pixel color = calcularColorPixel(objetos, fuentes, rayo, 0);

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
    // numCores = 1;

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