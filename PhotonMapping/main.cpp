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
const Color marron = Color(0.713, 0.5372, 0.2);

const Color verdeOscuro = Color(0.18, 0.8156, 0.1372);
const Color azulClaro = Color(0.086, 0.690, 0.972);
const Color ocre = Color(0.9058, 0.7490, 0.4509);
const Color blancoTotal = Color(1, 1, 1);

// Materiales difusos
const Difuso amarilloMatDifuso = Difuso(amarillo, negro);
const Difuso rosaMatDifuso = Difuso(rosa, negro);
const Difuso azulMatDifuso = Difuso(azul, negro);
const Difuso rojoMatDifuso = Difuso(rojo, negro);
const Difuso verdeMatDifuso = Difuso(verde, negro);
const Difuso blancoMatDifuso = Difuso(blanco, negro);
const Difuso negroMatDifuso = Difuso(negro, negro);
const Difuso naranjaMatDifuso = Difuso(naranja, negro);
const Difuso turquesaMatDifuso = Difuso(turquesa, negro);
const Difuso grisMatDifuso = Difuso(gris, negro);
const Difuso grisOscuroMatDifuso = Difuso(gris, negro);
const Difuso amatistaMatDifuso = Difuso(amatista, negro);
const Difuso eclipseMatDifuso = Difuso(amatista, negro);
const Difuso azulClaroMatDifuso = Difuso(azulClaro, negro);
const Difuso verdeOscuroMatDifuso = Difuso(verdeOscuro, negro);
const Difuso ocreMatDifuso = Difuso(ocre, negro);
const Difuso blancoTotalMatDifuso = Difuso(blancoTotal, negro);
const Difuso marronMatDifuso = Difuso(marron, negro);

// Materiales plastico
const Plastico espejo = Plastico(blanco * 0, blanco, negro);
const Plastico verdeOscuroMatPlastico = Plastico(verdeOscuro * 0.8, verdeOscuro * 0.2, negro);
const Plastico blancoMatPlastico = Plastico(blanco * 0.8, blanco * 0.2, negro);
const Plastico azulClaroMatPlastico = Plastico(azulClaro * 0.8, azulClaro * 0.2, negro);
const Plastico amarilloMatPlastico = Plastico(amarillo * 0.8, amarillo * 0.2, negro);

const Plastico turquesaMatPlastico = Plastico(turquesa * 0.8, turquesa * 0.2, negro);
const Plastico naranjaMatPlastico = Plastico(naranja * 0.8, naranja * 0.2, negro);

const Plastico rosaMatPlastico = Plastico(rosa * 0.75, rosa * 0.25, negro);
const Plastico marronMatPlastico = Plastico(marron * 0.75, marron * 0.25, negro);
const Plastico rojoMatPlastico = Plastico(rojo * 0.8, rojo * 0.2, negro);


// Materiales dielectricos
const Dielectrico azulMatDielectrico = Dielectrico(azul * 0.1, azul * 0.9, negro, 1.5);

// Escena de la kernel box
void kernelBox(vector<Geometria*>& objetos, vector<FuenteLuz*>& fuentes) {
    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    Esfera* esfera = new Esfera(Punto(-0.5, -0.7, 0.25), 0.3);

    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    Esfera* esfera2 = new Esfera(Punto(0.5, -0.7, -0.25), 0.3);

    Plano* plano = new Plano(1.0, Direccion(0.0, 0.0, -1.0));

    Plano* planoIzquierda = new Plano(1.0, Direccion(1.0, 0.0, 0.0));

    Plano* planoDerecha = new Plano(1.0, Direccion(-1.0, 0.0, 0.0));

    Plano* techo = new Plano(1.0, Direccion(0.0, -1.0, 0.0), blancoMatDifuso, false);
    Plano* suelo = new Plano(1.0, Direccion(0.0, 1.0, 0.0));

    esfera->setMaterial(rosaMatPlastico);
    esfera2->setMaterial(azulMatDielectrico);
    plano->setMaterial(grisMatDifuso);
    suelo->setMaterial(grisMatDifuso);
    planoIzquierda->setMaterial(rojoMatDifuso);
    planoDerecha->setMaterial(verdeMatDifuso);


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

    Plano* techo = new Plano(1.0, Direccion(0.0, -1.0, 0.0), blancoMatDifuso, false);
    Plano* suelo = new Plano(1.0, Direccion(0.0, 1.0, 0.0));

    esfera->setMaterial(rosaMatPlastico);
    esfera2->setMaterial(azulMatDielectrico);
    plano->setMaterial(espejo);
    suelo->setMaterial(grisMatDifuso);
    planoIzquierda->setMaterial(rojoMatDifuso);
    planoDerecha->setMaterial(verdeMatDifuso);


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

    Plano* techo = new Plano(1.0, Direccion(0.0, -1.0, 0.0), blancoMatDifuso, false);
    Plano* suelo = new Plano(1.0, Direccion(0.0, 1.0, 0.0));

    esfera->setMaterial(rosaMatDifuso);
    esfera2->setMaterial(rosaMatDifuso);
    cilindro->setMaterial(azulMatDifuso);
    plano->setMaterial(grisMatDifuso);
    suelo->setMaterial(grisMatDifuso);
    planoIzquierda->setMaterial(rojoMatDifuso);
    planoDerecha->setMaterial(verdeMatDifuso);

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

    // Crear una esfera de radio 0.3 en el centro de la escena
    // Esfera* esferaCentro = new Esfera(Punto(0.0, -0.7, 0.0), 0.3);
    // Primera fila
    Esfera* esfera1 = new Esfera(Punto(-0.45, -0.9, -0.1), 0.15);
    Esfera* esfera2 = new Esfera(Punto(-0.15, -0.9, -0.1), 0.15);
    Esfera* esfera3 = new Esfera(Punto(0.15, -0.9, -0.1), 0.15);
    Esfera* esfera4 = new Esfera(Punto(0.45, -0.9, -0.1), 0.15);
    // Segunda fila
    Esfera* esfera5 = new Esfera(Punto(-0.30, -0.7, 0.05), 0.15);

    Esfera* esfera6 = new Esfera(Punto(-0.00, -0.7, 0.05), 0.15);
    
    Esfera* esfera7 = new Esfera(Punto(0.30, -0.7, 0.05), 0.15);
    // Tercera fila
    Esfera* esfera8 = new Esfera(Punto(-0.15, -0.5, 0.2), 0.15);
    Esfera* esfera9 = new Esfera(Punto(0.15, -0.5, 0.2), 0.15);    
    // Cuarta fila
    Esfera* esfera10 = new Esfera(Punto(0.0, -0.25, 0.4), 0.2);

    Triangulo* trianguloCima = new Triangulo(Punto(-0.25, -0.4, 0.5), Punto(0.0, 0.1, 0.5), Punto(0.25, -0.4, 0.5));

    // Cilindro en la cima
    // Cilindro* cilindroCima = new Cilindro(Punto(0.0, -1.4, 2), 0.8, 2.5);


    Plano* plano = new Plano(2, Direccion(0.0, 0.0, -1), espejo, false);
    Plano* planoIzquierda = new Plano(1.1, Direccion(1.0, 0.0, 0.0), rojoMatDifuso, false);
    Plano* planoDerecha = new Plano(1.1, Direccion(-1.0, 0.0, 0.0), amarilloMatDifuso, false);

    Plano* techo = new Plano(1, Direccion(0.0, -1.0, 0.0), blancoMatDifuso, false);
    Plano* suelo = new Plano(1, Direccion(0.0, 1.0, 0.0), espejo, false);

    cilindroIzq1->setMaterial(amatistaMatDifuso);
    cilindroIzq2->setMaterial(eclipseMatDifuso);
    cilindroIzq3->setMaterial(amatistaMatDifuso);
    cilindroDcha1->setMaterial(amatistaMatDifuso);
    cilindroDcha2->setMaterial(eclipseMatDifuso);
    cilindroDcha3->setMaterial(amatistaMatDifuso);
    triangulo1->setMaterial(espejo);
    triangulo2->setMaterial(espejo);
    // esferaCentro->setMaterial(turquesaMatDielectrico);
    esfera1->setMaterial(azulClaroMatPlastico);
    esfera2->setMaterial(verdeOscuroMatPlastico);
    esfera3->setMaterial(amarilloMatPlastico);
    esfera4->setMaterial(blancoMatPlastico);

    esfera5->setMaterial(naranjaMatPlastico);
    esfera6->setMaterial(azulMatDielectrico);
    esfera7->setMaterial(turquesaMatPlastico);

    esfera8->setMaterial(rosaMatPlastico);
    esfera9->setMaterial(marronMatPlastico);

    esfera10->setMaterial(espejo);
    trianguloCima->setMaterial(espejo);

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
    // objetos.push_back(esferaCentro);
    objetos.push_back(esfera1);
    objetos.push_back(esfera2);
    objetos.push_back(esfera3);
    objetos.push_back(esfera4);
    objetos.push_back(esfera5);
    objetos.push_back(esfera6);
    objetos.push_back(esfera7);
    objetos.push_back(esfera8);
    objetos.push_back(esfera9);
    objetos.push_back(esfera10);
    // objetos.push_back(trianguloCima);

    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), blanco);
    FuenteLuz* naranjaLuz = new FuenteLuz(Punto(0.0, 0.5, -1.5), naranja * 0.7);

    fuentes.push_back(blanca);
    fuentes.push_back(naranjaLuz);
}

// Escena con esferas y suelo espejo
void arbolNavidad(vector<Geometria*>& objetos, vector<FuenteLuz*>& fuentes) {
    // Primera fila
    Esfera* esfera1 = new Esfera(Punto(-0.30, -0.4, -0.1), 0.1);
    Esfera* esfera2 = new Esfera(Punto(-0.10, -0.4, -0.1), 0.1);
    Esfera* esfera3 = new Esfera(Punto(0.10, -0.4, -0.1), 0.1);
    Esfera* esfera4 = new Esfera(Punto(0.30, -0.4, -0.1), 0.1);
    // Segunda fila
    Esfera* esfera5 = new Esfera(Punto(-0.20, -0.22, -0.1), 0.1);
    Esfera* esfera6 = new Esfera(Punto(-0.00, -0.22, -0.1), 0.1);
    Esfera* esfera7 = new Esfera(Punto(0.20, -0.22, -0.1), 0.1);
    // Tercera fila
    Esfera* esfera8 = new Esfera(Punto(-0.1, -0.04, -0.1), 0.1);
    Esfera* esfera9 = new Esfera(Punto(0.1, -0.04, -0.1), 0.1);    
    // Cuarta fila
    Esfera* esfera10 = new Esfera(Punto(0.0, 0.14, -0.1), 0.1);


    // Cilindro en el centro
    Cilindro* cilindroTallo = new Cilindro(Punto(0.0, -0.9, -0.1), 0.1, 0.4, marronMatDifuso);

    // Triangulo que ocupe la misma superficie que todas las esferas
    Triangulo* trianguloTotal = new Triangulo(Punto(-0.3, -0.5, -0.2), Punto(0.0, 0.1, -0.2), Punto(0.3, -0.5, -0.2));
    Esfera* esferaIzq = new Esfera(Punto(-0.3, -0.5, -0.2), 0.05);
    Esfera* esferaDcha = new Esfera(Punto(0.3, -0.5, -0.2), 0.05);
    Esfera* esferaArriba = new Esfera(Punto(0.0, 0.1, -0.2), 0.05);
    // Esfera en el centro del triangulo
    Esfera* esferaCentroIzq = new Esfera(Punto(-0.06, -0.2, -0.2), 0.03);
    Esfera* esferaCentroDcha = new Esfera(Punto(0.06, -0.2, -0.2), 0.03);

    Esfera* esferaCara1 = new Esfera(Punto(-0.1, -0.3, -0.2), 0.01);
    Esfera* esferaCara2 = new Esfera(Punto(-0.09, -0.31, -0.2), 0.01);
    Esfera* esferaCara3 = new Esfera(Punto(-0.08, -0.32, -0.2), 0.01);
    Esfera* esferaCara4 = new Esfera(Punto(-0.07, -0.33, -0.2), 0.01);
    Esfera* esferaCara5 = new Esfera(Punto(-0.06, -0.34, -0.2), 0.01);
    Esfera* esferaCara6 = new Esfera(Punto(-0.05, -0.35, -0.2), 0.01);
    Esfera* esferaCara7 = new Esfera(Punto(-0.04, -0.36, -0.2), 0.01);
    Esfera* esferaCara8 = new Esfera(Punto(-0.03, -0.37, -0.2), 0.01);
    Esfera* esferaCara9 = new Esfera(Punto(-0.02, -0.38, -0.2), 0.01);
    Esfera* esferaCara10 = new Esfera(Punto(-0.01, -0.39, -0.2), 0.01);
    Esfera* esferaCara11 = new Esfera(Punto(0.0, -0.4, -0.2), 0.01);
    Esfera* esferaCara12 = new Esfera(Punto(0.01, -0.39, -0.2), 0.01);
    Esfera* esferaCara13 = new Esfera(Punto(0.02, -0.38, -0.2), 0.01);
    Esfera* esferaCara14 = new Esfera(Punto(0.03, -0.37, -0.2), 0.01);
    Esfera* esferaCara15 = new Esfera(Punto(0.04, -0.36, -0.2), 0.01);
    Esfera* esferaCara16 = new Esfera(Punto(0.05, -0.35, -0.2), 0.01);
    Esfera* esferaCara17 = new Esfera(Punto(0.06, -0.34, -0.2), 0.01);
    Esfera* esferaCara18 = new Esfera(Punto(0.07, -0.33, -0.2), 0.01);
    Esfera* esferaCara19 = new Esfera(Punto(0.08, -0.32, -0.2), 0.01);
    Esfera* esferaCara20 = new Esfera(Punto(0.09, -0.31, -0.2), 0.01);
    Esfera* esferaCara21 = new Esfera(Punto(0.1, -0.3, -0.2), 0.01);



    Plano* plano = new Plano(2, Direccion(0.0, 0.0, -1), blancoMatDifuso, false);
    Plano* planoIzquierda = new Plano(1.1, Direccion(1.0, 0.0, 0.0), rojoMatDifuso, false);
    Plano* planoDerecha = new Plano(1.1, Direccion(-1.0, 0.0, 0.0), amarilloMatDifuso, false);

    Plano* techo = new Plano(1, Direccion(0.0, -1.0, 0.0), blancoMatDifuso, false);
    Plano* suelo = new Plano(1, Direccion(0.0, 1.0, 0.0), blancoMatDifuso, false);

    esfera1->setMaterial(verdeOscuroMatPlastico);
    esfera2->setMaterial(verdeOscuroMatPlastico);
    esfera3->setMaterial(verdeOscuroMatPlastico);
    esfera4->setMaterial(verdeOscuroMatPlastico);

    esfera5->setMaterial(verdeOscuroMatPlastico);
    esfera6->setMaterial(verdeOscuroMatPlastico);
    esfera7->setMaterial(verdeOscuroMatPlastico);

    esfera8->setMaterial(verdeOscuroMatPlastico);
    esfera9->setMaterial(verdeOscuroMatPlastico);

    esfera10->setMaterial(verdeOscuroMatPlastico);
    trianguloTotal->setMaterial(verdeOscuroMatPlastico);
    esferaIzq->setMaterial(naranjaMatPlastico);
    esferaDcha->setMaterial(naranjaMatPlastico);
    esferaArriba->setMaterial(naranjaMatPlastico);
    esferaCentroIzq->setMaterial(rojoMatDifuso);
    esferaCentroDcha->setMaterial(rojoMatDifuso);
    esferaCara1->setMaterial(rojoMatDifuso);
    esferaCara2->setMaterial(rojoMatDifuso);
    esferaCara3->setMaterial(rojoMatDifuso);
    esferaCara4->setMaterial(rojoMatDifuso);
    esferaCara5->setMaterial(rojoMatDifuso);
    esferaCara6->setMaterial(rojoMatDifuso);
    esferaCara7->setMaterial(rojoMatDifuso);
    esferaCara8->setMaterial(rojoMatDifuso);
    esferaCara9->setMaterial(rojoMatDifuso);
    esferaCara10->setMaterial(rojoMatDifuso);
    esferaCara11->setMaterial(rojoMatDifuso);
    esferaCara12->setMaterial(rojoMatDifuso);
    esferaCara13->setMaterial(rojoMatDifuso);
    esferaCara14->setMaterial(rojoMatDifuso);
    esferaCara15->setMaterial(rojoMatDifuso);
    esferaCara16->setMaterial(rojoMatDifuso);
    esferaCara17->setMaterial(rojoMatDifuso);
    esferaCara18->setMaterial(rojoMatDifuso);
    esferaCara19->setMaterial(rojoMatDifuso);
    esferaCara20->setMaterial(rojoMatDifuso);
    esferaCara21->setMaterial(rojoMatDifuso);


    objetos.push_back(plano);
    objetos.push_back(planoDerecha);
    objetos.push_back(planoIzquierda);
    objetos.push_back(techo);
    objetos.push_back(suelo);
    // objetos.push_back(esfera1);
    // objetos.push_back(esfera2);
    // objetos.push_back(esfera3);
    // objetos.push_back(esfera4);
    // objetos.push_back(esfera5);
    // objetos.push_back(esfera6);
    // objetos.push_back(esfera7);
    // objetos.push_back(esfera8);
    // objetos.push_back(esfera9);
    // objetos.push_back(esfera10);
    objetos.push_back(cilindroTallo);
    objetos.push_back(trianguloTotal);
    objetos.push_back(esferaIzq);
    objetos.push_back(esferaDcha);
    objetos.push_back(esferaArriba);
    objetos.push_back(esferaCentroIzq);
    objetos.push_back(esferaCentroDcha);
    objetos.push_back(esferaCara1);
    objetos.push_back(esferaCara2);
    objetos.push_back(esferaCara3);
    objetos.push_back(esferaCara4);
    objetos.push_back(esferaCara5);
    objetos.push_back(esferaCara6);
    objetos.push_back(esferaCara7);
    objetos.push_back(esferaCara8);
    objetos.push_back(esferaCara9);
    objetos.push_back(esferaCara10);
    objetos.push_back(esferaCara11);
    objetos.push_back(esferaCara12);
    objetos.push_back(esferaCara13);
    objetos.push_back(esferaCara14);
    objetos.push_back(esferaCara15);
    objetos.push_back(esferaCara16);
    objetos.push_back(esferaCara17);
    objetos.push_back(esferaCara18);
    objetos.push_back(esferaCara19);
    objetos.push_back(esferaCara20);
    objetos.push_back(esferaCara21);



    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), blanco);
    FuenteLuz* naranjaLuz = new FuenteLuz(Punto(0.0, 0.5, -1.5), naranja * 0.7);

    fuentes.push_back(blanca);
    
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
    //columnasCornellBox(objetos, fuentes);
    arbolNavidad(objetos, fuentes);

    /*-------- MEDIR TIEMPOS ------- */
    // Comparar cuanto tiempo tarda sin y con area de luz
    ImagenHDR imagenEscena = camara.renderizar(objetos, fuentes, resolucion, 10000, 200, 0.3);
    ToneMapping toneMapping = ToneMapping(imagenEscena);
    toneMapping.curvaGamma(1 / 2.2);
    //toneMapping.ecualizacion();
    escritor.escribirImagenHDR("ppms/" + nombre + ".ppm", toneMapping.imagen);
    return 0;
}


