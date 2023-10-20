#include <iostream>
#include <cassert>
#include <vector>

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


int main() {

    // Probar a leer la imagen "ppms/forest_path.ppm"
    LectorHDR lector;
    // ImagenHDR imagen = lector.leerImagenHDR("ppms/seymour_park.ppm");
    // Probar a escribir la imagen "ppms/forest_path.ppm"
    EscritorHDR escritor;

    // Crear una camara en el origen de la escena
    Camara camara(Direccion(-1.0, 0.0, 0.0), Direccion(0.0, 1.0, 0.0), Direccion(0.0, 0.0, 3.0), Punto(0.0, 0.0, -3.5));

    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    Esfera* esfera = new Esfera(Punto(-0.5, -0.7, 0.25), 0.3);

    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    Esfera* esfera2 = new Esfera(Punto(0.5, -0.7, -0.25), 0.3);

    Plano* plano = new Plano(1.0, Direccion(0.0, 0.0, -1.0));

    Plano* planoIzquierda = new Plano(1.0, Direccion(1.0, 0.0, 0.0));

    Plano* planoDerecha = new Plano(1.0, Direccion(-1.0, 0.0, 0.0));

    Plano* techo = new Plano(1.0, Direccion(0.0, -1.0, 0.0));
    Plano* suelo = new Plano(1.0, Direccion(0.0, 1.0, 0.0));

    pixel color;
    color.r = 128;
    color.g = 0;
    color.b = 128;
    esfera->setColor(color);

    // Color azul
    pixel color2;
    color2.r = 0;
    color2.g = 0;
    color2.b = 255;
    esfera2->setColor(color2);

    // Color rojo
    pixel color3;
    color3.r = 255;
    color3.g = 0;
    color3.b = 0;
    planoIzquierda->setColor(color3);

    // Color verde
    pixel color4;
    color4.r = 0;
    color4.g = 255;
    color4.b = 0;
    planoDerecha->setColor(color4);

    pixel blanco;
    blanco.r = 255;
    blanco.g = 255;
    blanco.b = 255;
    plano->setColor(blanco);

    pixel negro;
    negro.r = 0;
    negro.g = 70;
    negro.b = 128;
    techo->setColor(negro);
    suelo->setColor(negro);

    vector<Geometria*> objetos = vector<Geometria*>();
    objetos.push_back(esfera);
    objetos.push_back(esfera2);
    objetos.push_back(plano);
    objetos.push_back(planoDerecha);
    objetos.push_back(planoIzquierda);
    objetos.push_back(techo);
    objetos.push_back(suelo);
    ImagenHDR imagenEscena = camara.renderizar(objetos);
    escritor.escribirImagenHDR("ppms/imagenEscena.ppm", imagenEscena);
    return 0;
}
