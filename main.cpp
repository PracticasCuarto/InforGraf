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

    pixel amarillo = Pixel(255, 255, 0);
    pixel rosa = Pixel(255, 0, 255);
    pixel azul = Pixel(0, 0, 255);
    pixel rojo = Pixel(255, 0, 0);
    pixel verde = Pixel(0, 255, 0);
    pixel blanco = Pixel(255, 255, 255);
    pixel negro = Pixel(0, 0, 0);
    pixel naranja = Pixel(255, 128, 0);


    esfera->setColor(rosa);
    esfera2->setColor(azul);
    plano->setColor(blanco);
    techo->setColor(rojo);
    suelo->setColor(rojo);
    plano->setColor(amarillo);
    planoIzquierda->setColor(amarillo);
    planoDerecha->setColor(amarillo);

    vector<Geometria*> objetos = vector<Geometria*>();
    // objetos.push_back(esfera);
    // objetos.push_back(esfera2);
    // objetos.push_back(plano);
    // objetos.push_back(planoDerecha);
    // objetos.push_back(planoIzquierda);
    // objetos.push_back(techo);
    // objetos.push_back(suelo);

    // Triangulo* triangulo = new Triangulo(Punto(0.0, 0.0, 0.0), Punto(1.0, 0.0, 0.0), Punto(0.0, 1.0, 0.0), rosa);

    // objetos.push_back(triangulo);

    // Definir los vértices de los triángulos
    Punto vertice1(-1.5, 1.0, 0.0);
    Punto vertice2(-1.5, -1.0, 0.0);
    Punto vertice3(0.0, 1.0, 0.0);

    Punto vertice4(0.0, 1.0, 0.0);
    Punto vertice5(-1.5, -1.0, 0.0);
    Punto vertice6(0.0, -1.0, 0.0);

    Punto vertice7(0.0, 1.0, 0.0);
    Punto vertice8(0.0, -1.0, 0.0);
    Punto vertice9(1.5, 1.0, 0.0);

    // Crear triángulos con los vértices y colores
    Triangulo* triangulo1 = new Triangulo(vertice1, vertice2, vertice3, rojo);
    Triangulo* triangulo2 = new Triangulo(vertice4, vertice5, vertice6, amarillo);
    Triangulo* triangulo3 = new Triangulo(vertice7, vertice8, vertice9, rojo);

    objetos.push_back(triangulo1);
    objetos.push_back(triangulo2);
    objetos.push_back(triangulo3);

    ImagenHDR imagenEscena = camara.renderizar(objetos);
    escritor.escribirImagenHDR("ppms/imagenEscena.ppm", imagenEscena);
    return 0;
}
