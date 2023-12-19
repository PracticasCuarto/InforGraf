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
#include "src/Materiales/Material.hpp"
#include "src/Materiales/Difuso.hpp"
#include "src/Materiales/Plastico.hpp"
#include "src/Materiales/Dielectrico.hpp"

int main(int argc, char* argv[]) {

    // Leer los parametros de entrada

    int ancho = 256;         // Valor predeterminado para el ancho
    int alto = 256;          // Valor predeterminado para el alto
    string nombre = "imagenEscenaPocha";      // Nombre del archivo de salida
    int resolucion = 255;     // Valor predeterminado para la resolución de color
    int muestras = 64;      // Valor predeterminado para el número de muestras por píxel nRayos

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

    // Colores
    Color amarillo = Color(0.9, 0.9, 0);
    Color rosa = Color(0.9961, 0.5373, 0.9098);
    Color azul = Color(0.5882, 0.8392, 0.9);
    Color rojo = Color(0.6, 0, 0);
    Color verde = Color(0, 0.6, 0);
    Color blanco = Color(0.7, 0.7, 0.7);
    Color negro = Color(0, 0, 0);
    Color naranja = Color(0.9, 0.502, 0);
    Color gris = Color(0.6039, 0.6039, 0.6039);
    Color turquesa = Color(0.451, 0.902, 0.9804);

    // Materiales difusos
    Difuso amarilloMat = Difuso(amarillo, negro);
    // Difuso rosaMat = Difuso(rosa, negro);
    Plastico rosaMat = Plastico(rosa * 0.5, rosa * 0.5, negro);
    Dielectrico azulMat = Dielectrico(azul * 0, azul * 1, negro, 1.5);
    // Difuso azulMat = Difuso(azul, negro);
    Difuso rojoMat = Difuso(rojo, negro);
    Difuso verdeMat = Difuso(verde, negro);
    Difuso blancoMat = Difuso(blanco, negro);
    Difuso negroMat = Difuso(negro, negro);
    Difuso naranjaMat = Difuso(naranja, negro);
    Difuso turquesaMat = Difuso(turquesa, negro);
    Difuso grisMat = Difuso(gris, negro);


    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    Esfera* esfera = new Esfera(Punto(-0.5, -0.7, 0.25), 0.3);

    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    Esfera* esfera2 = new Esfera(Punto(0.5, -0.7, -0.25), 0.3);

    Plano* plano = new Plano(1.0, Direccion(0.0, 0.0, -1.0));

    Plano* planoIzquierda = new Plano(1.0, Direccion(1.0, 0.0, 0.0));

    Plano* planoDerecha = new Plano(1.0, Direccion(-1.0, 0.0, 0.0));

    Plano* techo = new Plano(1.0, Direccion(0.0, -1.0, 0.0), blancoMat, false);
    Plano* suelo = new Plano(1.0, Direccion(0.0, 1.0, 0.0));

    esfera->setMaterial(rosaMat);
    esfera2->setMaterial(azulMat);
    plano->setMaterial(grisMat);
    suelo->setMaterial(grisMat);
    planoIzquierda->setMaterial(rojoMat);
    planoDerecha->setMaterial(verdeMat);

    vector<Geometria*> objetos = vector<Geometria*>();
    objetos.push_back(esfera);
    objetos.push_back(esfera2);
    objetos.push_back(plano);
    objetos.push_back(planoDerecha);
    objetos.push_back(planoIzquierda);
    objetos.push_back(techo);
    objetos.push_back(suelo);

    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), blanco);
    // FuenteLuz* otra = new FuenteLuz(Punto(0.3, 0.5, 0), Color(0, 0, 255));
    vector<FuenteLuz*> fuentes = vector<FuenteLuz*>();
    fuentes.push_back(blanca);
    // fuentes.push_back(otra);

    /*-------- MEDIR TIEMPOS ------- */
    // Comparar cuanto tiempo tarda sin y con area de luz
    ImagenHDR imagenEscena = camara.renderizar(objetos, fuentes, resolucion, 100000, 200, 0.3);
    ToneMapping toneMapping = ToneMapping(imagenEscena);
    toneMapping.curvaGamma(1 / 2.2);
    //toneMapping.ecualizacion();
    escritor.escribirImagenHDR("ppms/" + nombre + ".ppm", toneMapping.imagen);
    return 0;
}
