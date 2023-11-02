#include <iostream>
#include <cassert>
#include <vector>
#include <getopt.h>

#include "src/Direccion.hpp"
#include "src/ImagenHDR.hpp"
#include "src/Punto.hpp"
#include "src/Matriz.hpp"
// #include "src/Estacion.hpp"
// #include "src/Esfera.hpp"
#include "src/LectorHDR.hpp"
#include "src/EscritorHDR.hpp"
#include "src/ToneMapping.hpp"
#include "src/Geometria.hpp"
#include "src/Camara.hpp"
#include "src/FuenteLuz.hpp"


int main(int argc, char* argv[]) {

    // Leer los parametros de entrada

    int ancho = 512;         // Valor predeterminado para el ancho
    int alto = 512;          // Valor predeterminado para el alto
    string nombre = "imagenEscena";      // Nombre del archivo de salida
    int resolucion = 24;     // Valor predeterminado para la resolución de color
    int muestras = 100;      // Valor predeterminado para el número de muestras por píxel

    // Parsear los argumentos de línea de comandos
    int opt;
    while ((opt = getopt(argc, argv, "a:l:n:r:m:")) != -1) {
        switch (opt) {
        case 'a':
            ancho = atoi(optarg);
            break;
        case 'l':
            alto = atoi(optarg);
            break;
        case 'n':
            nombre = optarg;
            break;
        case 'r':
            resolucion = atoi(optarg);
            break;
        case 'm':
            muestras = atoi(optarg);
            break;
        default:
            std::cerr << "Uso: " << argv[0] << " -a ancho -l alto -n nombre -r resolucion -m muestras" << std::endl;
            return 1;
        }
    }

    // Probar a leer la imagen "ppms/forest_path.ppm"
    LectorHDR lector;
    // ImagenHDR imagen = lector.leerImagenHDR("ppms/seymour_park.ppm");
    // Probar a escribir la imagen "ppms/forest_path.ppm"
    EscritorHDR escritor;

    // Crear una camara en el origen de la escena
    Camara camara(Direccion(-1.0, 0.0, 0.0), Direccion(0.0, 1.0, 0.0), Direccion(0.0, 0.0, 3.0), Punto(0.0, 0.0, -3.5), alto, ancho, muestras, resolucion);

    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    Esfera* esfera = new Esfera(Punto(-0.5, -0.7, 0.25), 0.3);

    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    Esfera* esfera2 = new Esfera(Punto(0.5, -0.7, -0.25), 0.3);

    Plano* plano = new Plano(1.0, Direccion(0.0, 0.0, -1.0));

    Plano* planoIzquierda = new Plano(1.0, Direccion(1.0, 0.0, 0.0));

    Plano* planoDerecha = new Plano(1.0, Direccion(-1.0, 0.0, 0.0));

    Plano* techo = new Plano(1.0, Direccion(0.0, -1.0, 0.0));
    Plano* suelo = new Plano(1.0, Direccion(0.0, 1.0, 0.0));

    pixel amarillo = Pixel(255, 255, 0);
    pixel rosa = Pixel(254, 137, 232);
    pixel azul = Pixel(150, 214, 255);
    pixel rojo = Pixel(255 * 0.9, 0, 0);
    pixel verde = Pixel(0, 255 * 0.9, 0);
    pixel blanco = Pixel(255, 255, 255);
    pixel negro = Pixel(0, 0, 0);
    pixel naranja = Pixel(255, 128, 0);
    pixel gris = Pixel(205, 205, 205);
    pixel turquesa = Pixel(115, 230, 250);

    esfera->setColor(rosa);
    esfera2->setColor(turquesa);
    plano->setColor(gris);
    techo->setColor(gris);
    suelo->setColor(gris);
    planoIzquierda->setColor(rojo);
    planoDerecha->setColor(verde);

    vector<Geometria*> objetos = vector<Geometria*>();
    objetos.push_back(esfera);
    objetos.push_back(esfera2);
    objetos.push_back(plano);
    objetos.push_back(planoDerecha);
    objetos.push_back(planoIzquierda);
    objetos.push_back(techo);
    objetos.push_back(suelo);

    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), Pixel(255, 255, 255));
    // FuenteLuz* otra = new FuenteLuz(Punto(0.3, 0.5, 0), Pixel(0, 0, 255));
    vector<FuenteLuz*> fuentes = vector<FuenteLuz*>();
    fuentes.push_back(blanca);
    // fuentes.push_back(otra);

    /*-------- MEDIR TIEMPOS ------- */
    // Comparar cuanto tiempo tarda sin y con area de luz
    ImagenHDR imagenEscena = camara.renderizar(objetos, fuentes);
    ToneMapping toneMapping = ToneMapping(imagenEscena);
    toneMapping.curvaGamma(1 / 2.2);
    // toneMapping.ecualizacion();
    escritor.escribirImagenHDR("ppms/" + nombre + "8Rebotes.ppm", toneMapping.imagen);
    return 0;
}
