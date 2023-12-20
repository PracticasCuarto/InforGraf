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


/*
 * Definicion de constantes para los materiales
 */

 // Colores
const Color amarillo = Color(0.9, 0.9, 0);
const Color rosa = Color(0.9961, 0.5373, 0.9098);
const Color azul = Color(0.5882, 0.8392, 0.9);
const Color rojo = Color(0.6, 0, 0);
const Color verde = Color(0, 0.6, 0);
const Color blanco = Color(0.7, 0.7, 0.7);
const Color negro = Color(0, 0, 0);
const Color naranja = Color(0.9, 0.502, 0);
const Color gris = Color(0.6039, 0.6039, 0.6039);
const Color turquesa = Color(0.451, 0.902, 0.9804);
const Color grisOscuro = Color(0.4039, 0.4039, 0.4039);
const Color amatista = Color(0.7765, 0.451, 1);
const Color eclipse = Color(0.6823, 0.2156, 1);


// Materiales difusos
const Difuso amarilloMat = Difuso(amarillo, negro);
const Difuso rosaMatDifuso = Difuso(rosa, negro);
const Plastico rosaMat = Plastico(rosa * 0.2, rosa * 0.8, negro);
const Dielectrico azulMat = Dielectrico(azul * 0.2, azul * 0.8, negro, 1.5);
const Difuso azulMatDifuso = Difuso(azul, negro);
const Difuso rojoMat = Difuso(rojo, negro);
const Difuso verdeMat = Difuso(verde, negro);
const Difuso blancoMat = Difuso(blanco, negro);
const Difuso negroMat = Difuso(negro, negro);
const Difuso naranjaMat = Difuso(naranja, negro);
const Difuso turquesaMat = Difuso(turquesa, negro);
const Difuso grisMat = Difuso(gris, negro);
const Difuso grisOscuroMat = Difuso(gris, negro);
const Difuso amatistaMat = Difuso(amatista, negro);
const Difuso eclipseMat = Difuso(amatista, negro);

const Plastico espejo = Plastico(blanco * 0, blanco, negro);

// Escena de la kernel box
void kernelBox(vector<Geometria*>& objetos, vector<FuenteLuz*>& fuentes) {
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


    objetos.push_back(esfera);
    objetos.push_back(esfera2);
    objetos.push_back(plano);
    objetos.push_back(planoDerecha);
    objetos.push_back(planoIzquierda);
    objetos.push_back(techo);
    objetos.push_back(suelo);

    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), blanco);
    // FuenteLuz* otra = new FuenteLuz(Punto(0.3, 0.5, 0), Color(0, 0, 255));

    fuentes.push_back(blanca);
    // fuentes.push_back(otra);
}

// Escena de la kernel box
void kernelBoxEspejo(vector<Geometria*>& objetos, vector<FuenteLuz*>& fuentes) {
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
    plano->setMaterial(espejo);
    suelo->setMaterial(grisMat);
    planoIzquierda->setMaterial(rojoMat);
    planoDerecha->setMaterial(verdeMat);


    objetos.push_back(esfera);
    objetos.push_back(esfera2);
    objetos.push_back(plano);
    objetos.push_back(planoDerecha);
    objetos.push_back(planoIzquierda);
    objetos.push_back(techo);
    objetos.push_back(suelo);

    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), blanco);
    // FuenteLuz* otra = new FuenteLuz(Punto(0.3, 0.5, 0), Color(0, 0, 255));

    fuentes.push_back(blanca);
    // fuentes.push_back(otra);
}

// Escena con cilindros y esferas en la cornell box
void cilindroCornellBox(vector<Geometria*>& objetos, vector<FuenteLuz*>& fuentes) {
    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    Esfera* esfera = new Esfera(Punto(-0.5, -0.7, -0.25), 0.3);

    Esfera* esfera2 = new Esfera(Punto(0.5, -0.7, -0.25), 0.3);

    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    Cilindro* cilindro = new Cilindro(Punto(0.0, -1.4, -0.25), 0.3, 3);

    Plano* plano = new Plano(1.0, Direccion(0.0, 0.0, -1.0));

    Plano* planoIzquierda = new Plano(1.0, Direccion(1.0, 0.0, 0.0));

    Plano* planoDerecha = new Plano(1.0, Direccion(-1.0, 0.0, 0.0));

    Plano* techo = new Plano(1.0, Direccion(0.0, -1.0, 0.0), blancoMat, false);
    Plano* suelo = new Plano(1.0, Direccion(0.0, 1.0, 0.0));

    esfera->setMaterial(rosaMatDifuso);
    esfera2->setMaterial(rosaMatDifuso);
    cilindro->setMaterial(azulMatDifuso);
    plano->setMaterial(grisMat);
    suelo->setMaterial(grisMat);
    planoIzquierda->setMaterial(rojoMat);
    planoDerecha->setMaterial(verdeMat);

    objetos.push_back(esfera);
    objetos.push_back(esfera2);
    objetos.push_back(cilindro);
    objetos.push_back(plano);
    objetos.push_back(planoDerecha);
    objetos.push_back(planoIzquierda);
    objetos.push_back(techo);
    objetos.push_back(suelo);

    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), blanco);

    fuentes.push_back(blanca);
}

// Escena con columnas
void columnasCornellBox(vector<Geometria*>& objetos, vector<FuenteLuz*>& fuentes) {
    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    //Esfera* esfera = new Esfera(Punto(-0.5, -0.7, -0.25), 0.3);

    //Esfera* esfera2 = new Esfera(Punto(0.5, -0.7, -0.25), 0.3);

    Cilindro* cilindroIzq1 = new Cilindro(Punto(-0.68, -1.4, 1.45), 0.12, 3);
    Cilindro* cilindroIzq2 = new Cilindro(Punto(-0.78, -1.4, 0.4), 0.12, 3);
    Cilindro* cilindroIzq3 = new Cilindro(Punto(-0.88, -1.4, -0.35), 0.12, 3);

    Cilindro* cilindroDcha1 = new Cilindro(Punto(0.68, -1.4, 1.45), 0.12, 3);
    Cilindro* cilindroDcha2 = new Cilindro(Punto(0.78, -1.4, 0.4), 0.12, 3);
    Cilindro* cilindroDcha3 = new Cilindro(Punto(0.88, -1.4, -0.35), 0.12, 3);

    Triangulo* triangulo1 = new Triangulo(Punto(-0.3, -0.3, 1.8), Punto(0.3, 0.5, 1.8), Punto(-0.3, 0.5, 1.8));
    Triangulo* triangulo2 = new Triangulo(Punto(-0.3, -0.3, 1.8), Punto(0.3, -0.3, 1.8), Punto(0.3, 0.5, 1.8));


    Plano* plano = new Plano(2, Direccion(0.0, 0.0, -1));

    Plano* planoIzquierda = new Plano(1.1, Direccion(1.0, 0.0, 0.0));

    Plano* planoDerecha = new Plano(1.1, Direccion(-1.0, 0.0, 0.0));

    Plano* techo = new Plano(1, Direccion(0.0, -1.0, 0.0), blancoMat, false);
    Plano* suelo = new Plano(1, Direccion(0.0, 1.0, 0.0));

    plano->setMaterial(grisMat);
    suelo->setMaterial(grisMat);
    planoIzquierda->setMaterial(rojoMat);
    planoDerecha->setMaterial(verdeMat);
    cilindroIzq1->setMaterial(amatistaMat);
    cilindroIzq2->setMaterial(eclipseMat);
    cilindroIzq3->setMaterial(amatistaMat);
    cilindroDcha1->setMaterial(amatistaMat);
    cilindroDcha2->setMaterial(eclipseMat);
    cilindroDcha3->setMaterial(amatistaMat);
    triangulo1->setMaterial(espejo);
    triangulo2->setMaterial(espejo);


    objetos.push_back(plano);
    objetos.push_back(planoDerecha);
    objetos.push_back(planoIzquierda);
    objetos.push_back(techo);
    objetos.push_back(suelo);
    objetos.push_back(cilindroIzq1);
    objetos.push_back(cilindroIzq2);
    objetos.push_back(cilindroIzq3);
    objetos.push_back(cilindroDcha1);
    objetos.push_back(cilindroDcha2);
    objetos.push_back(cilindroDcha3);
    objetos.push_back(triangulo1);
    // objetos.push_back(triangulo2);

    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), blanco);
    FuenteLuz* naranjaLuz = new FuenteLuz(Punto(0.0, 0.5, -1.5), naranja * 0.7);

    fuentes.push_back(blanca);
    fuentes.push_back(naranjaLuz);
}


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

    vector<Geometria*> objetos = vector<Geometria*>();
    vector<FuenteLuz*> fuentes = vector<FuenteLuz*>();

    //kernelBox(objetos, fuentes);
    columnasCornellBox(objetos, fuentes);


    /*-------- MEDIR TIEMPOS ------- */
    // Comparar cuanto tiempo tarda sin y con area de luz
    ImagenHDR imagenEscena = camara.renderizar(objetos, fuentes, resolucion, 10000, 200, 0.3);
    ToneMapping toneMapping = ToneMapping(imagenEscena);
    toneMapping.curvaGamma(1 / 2.2);
    //toneMapping.ecualizacion();
    escritor.escribirImagenHDR("ppms/" + nombre + ".ppm", toneMapping.imagen);
    return 0;
}


