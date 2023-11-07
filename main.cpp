#include <iostream>
#include <cassert>
#include <vector>
#include <getopt.h>

#include "src/Direccion.hpp"
#include "src/ImagenHDR/ImagenHDR.hpp"
#include "src/Punto.hpp"
#include "src/Matriz.hpp"
#include "src/ImagenHDR/LectorHDR.hpp"
#include "src/ImagenHDR/EscritorHDR.hpp"
#include "src/ImagenHDR/ToneMapping.hpp"
#include "src/Geometria.hpp"
#include "src/Camara.hpp"
#include "src/FuenteLuz.hpp"
#include "src/Color.hpp"


int main(int argc, char* argv[]) {

    // Leer los parametros de entrada

    int ancho = 512;         // Valor predeterminado para el ancho
    int alto = 512;          // Valor predeterminado para el alto
    string nombre = "imagenEscena";      // Nombre del archivo de salida
    int resolucion = 24;     // Valor predeterminado para la resolución de color
    int muestras = 8;      // Valor predeterminado para el número de muestras por píxel

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

    Color amarillo = Color(255, 255, 0);
    Color rosa = Color(254, 137, 232);
    Color azul = Color(150, 214, 255);
    Color rojo = Color(255 * 0.6, 0, 0);
    Color verde = Color(0, 255 * 0.6, 0);
    Color blanco = Color(255, 255, 255);
    Color negro = Color(0, 0, 0);
    Color naranja = Color(255, 128, 0);
    Color gris = Color(205, 205, 205);
    Color turquesa = Color(115, 230, 250);

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

    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), Color(255, 255, 255));
    // FuenteLuz* otra = new FuenteLuz(Punto(0.3, 0.5, 0), Color(0, 0, 255));
    vector<FuenteLuz*> fuentes = vector<FuenteLuz*>();
    fuentes.push_back(blanca);
    // fuentes.push_back(otra);

    /*-------- MEDIR TIEMPOS ------- */
    // Comparar cuanto tiempo tarda sin y con area de luz
    ImagenHDR imagenEscena = camara.renderizar(objetos, fuentes);
    ToneMapping toneMapping = ToneMapping(imagenEscena);
    toneMapping.curvaGamma(1 / 2.2);
    // toneMapping.ecualizacion();
    escritor.escribirImagenHDR("ppms/" + nombre + ".ppm", toneMapping.imagen);
    return 0;
}
