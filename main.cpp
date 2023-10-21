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

    pixel rosa = Pixel(255, 0, 255);
    esfera->setColor(rosa);

    // Color azul
    pixel azul = Pixel(0, 0, 255);
    esfera2->setColor(azul);

    // Color rojo
    pixel rojo = Pixel(255, 0, 0);
    planoIzquierda->setColor(rojo);

    // Color verde
    pixel verde = Pixel(0, 255, 0);
    planoDerecha->setColor(verde);

    pixel blanco = Pixel(255, 255, 255);
    plano->setColor(blanco);

    pixel naranja = Pixel(255, 165, 0);
    techo->setColor(naranja);
    suelo->setColor(naranja);

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
