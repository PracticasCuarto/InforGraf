#include <iostream>
#include <cassert>
#include <vector>
#include <getopt.h>
#include <chrono>

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
const Color naranja = Color(1, 0.502, 0);
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

const Plastico rosaMatPlastico = Plastico(rosa * 0.5, rosa * 0.5, negro);
const Plastico marronMatPlastico = Plastico(marron * 0.75, marron * 0.25, negro);
const Plastico rojoMatPlastico = Plastico(rojo * 0.8, rojo * 0.2, negro);

// Materiales dielectricos
const Dielectrico azulMatDielectrico = Dielectrico(azul * 0.1, azul * 0.9, negro, 1.5);




// Escena de la kernel box
void cornellBox(vector<Geometria*>& objetos, vector<FuenteLuz*>& fuentes) {
    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    Esfera* esfera = new Esfera(Punto(-0.5, -0.7, 0.25), 0.3, rosaMatPlastico);

    // Crear una esfera en el punto (-0.5 -0.7, 0.25) de radio 0.3
    Esfera* esfera2 = new Esfera(Punto(0.5, -0.7, -0.25), 0.3, azulMatDielectrico);

    Plano* plano = new Plano(1.0, Direccion(0.0, 0.0, -1.0));

    Plano* planoIzquierda = new Plano(1.0, Direccion(1.0, 0.0, 0.0));

    Plano* planoDerecha = new Plano(1.0, Direccion(-1.0, 0.0, 0.0));

    Plano* techo = new Plano(1.0, Direccion(0.0, -1.0, 0.0), blancoMatDifuso, false);
    Plano* suelo = new Plano(1.0, Direccion(0.0, 1.0, 0.0));

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



// Funcion para añadir al vector de objetos las esferas de la escena
void crearArbolNavidad(vector<Geometria*>& objetos) {
    // Cilindro para el tallo
    Cilindro* cilindroTallo = new Cilindro(Punto(-0.25, -0.9, -0.1), 0.1, 0.4, marronMatDifuso);
    // Hacer el árbol con 3 triángulos de diferente tamaño uno encima de otro
    Triangulo* trianguloGrande = new Triangulo(Punto(-0.65, -0.5, -0.2), Punto(-0.25, 0.1, -0.2), Punto(0.15, -0.5, -0.2), verdeOscuroMatPlastico);
    Triangulo* trianguloMediano = new Triangulo(Punto(-0.65, -0.3, -0.2), Punto(-0.25, 0.2, -0.2), Punto(0.15, -0.3, -0.2), verdeOscuroMatPlastico);
    Triangulo* trianguloPequenio = new Triangulo(Punto(-0.65, -0.1, -0.2), Punto(-0.25, 0.3, -0.2), Punto(0.15, -0.1, -0.2), verdeOscuroMatPlastico);

    Esfera* esferaIzq = new Esfera(Punto(-0.63, -0.5, -0.2), 0.05, naranjaMatPlastico);
    Esfera* esferaIzq2 = new Esfera(Punto(-0.63, -0.3, -0.2), 0.05, turquesaMatPlastico);
    Esfera* esferaIzq3 = new Esfera(Punto(-0.63, -0.1, -0.2), 0.05, azulClaroMatPlastico);
    Esfera* esferaDcha = new Esfera(Punto(0.12, -0.5, -0.2), 0.05, amarilloMatPlastico);
    Esfera* esferaDcha2 = new Esfera(Punto(0.12, -0.3, -0.2), 0.05, rosaMatPlastico);
    Esfera* esferaDcha3 = new Esfera(Punto(0.12, -0.1, -0.2), 0.05, rojoMatPlastico);

    // Para la carita sonriente
    Esfera* esferaCentroIzq = new Esfera(Punto(-0.31, -0.2, -0.2), 0.03, rojoMatDifuso);
    Esfera* esferaCentroDcha = new Esfera(Punto(-0.19, -0.2, -0.2), 0.03, rojoMatDifuso);
    Esfera* esferaCara1 = new Esfera(Punto(-0.35, -0.3, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara2 = new Esfera(Punto(-0.34, -0.31, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara3 = new Esfera(Punto(-0.33, -0.32, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara4 = new Esfera(Punto(-0.32, -0.33, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara5 = new Esfera(Punto(-0.31, -0.34, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara6 = new Esfera(Punto(-0.30, -0.35, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara7 = new Esfera(Punto(-0.29, -0.36, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara8 = new Esfera(Punto(-0.28, -0.37, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara9 = new Esfera(Punto(-0.27, -0.38, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara10 = new Esfera(Punto(-0.26, -0.39, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara11 = new Esfera(Punto(-0.25, -0.4, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara12 = new Esfera(Punto(-0.24, -0.39, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara13 = new Esfera(Punto(-0.23, -0.38, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara14 = new Esfera(Punto(-0.22, -0.37, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara15 = new Esfera(Punto(-0.21, -0.36, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara16 = new Esfera(Punto(-0.20, -0.35, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara17 = new Esfera(Punto(-0.19, -0.34, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara18 = new Esfera(Punto(-0.18, -0.33, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara19 = new Esfera(Punto(-0.17, -0.32, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara20 = new Esfera(Punto(-0.16, -0.31, -0.2), 0.01, rojoMatDifuso);
    Esfera* esferaCara21 = new Esfera(Punto(-0.15, -0.3, -0.2), 0.01, rojoMatDifuso);

    // Cubos que son los regalos
    Cubo* regalo1 = new Cubo(Punto(-0.48, -0.85, -0.2), 0.15, naranjaMatDifuso);
    Cubo* regalo2 = new Cubo(Punto(-0.68, -0.85, -0.2), 0.15, rosaMatDifuso);
    Cubo* regalo3 = new Cubo(Punto(-0.6, -0.75, 0.0), 0.23, turquesaMatDifuso);
    Cubo* regaloEncima = new Cubo(Punto(-0.58, -0.72, -0.2), 0.12, amarilloMatDifuso);
    
    objetos.push_back(cilindroTallo);
    objetos.push_back(trianguloGrande);
    objetos.push_back(trianguloMediano);
    objetos.push_back(trianguloPequenio);
    objetos.push_back(esferaIzq);
    objetos.push_back(esferaIzq2);
    objetos.push_back(esferaIzq3);
    objetos.push_back(esferaDcha);
    objetos.push_back(esferaDcha2);
    objetos.push_back(esferaDcha3);

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
    objetos.push_back(regalo1);
    objetos.push_back(regalo2);
    objetos.push_back(regalo3);
    objetos.push_back(regaloEncima);
}

// Función para crear el muñeco de nieve
void crearMunyecoNieve(vector<Geometria*>& objetos) {
    // Muñeco de nieve con 3 esferas (el cuerpo)
    Esfera* esferaNieve1 = new Esfera(Punto(0.5, -0.7, 0.3), 0.22, blancoTotalMatDifuso);
    Esfera* esferaNieve2 = new Esfera(Punto(0.5, -0.45, 0.3), 0.18, blancoTotalMatDifuso);
    Esfera* esferaNieve3 = new Esfera(Punto(0.5, -0.23, 0.3), 0.15, blancoTotalMatDifuso);
    // Botones negros del muñeco
    Esfera* boton1 = new Esfera(Punto(0.48, -0.7, 0.1), 0.036, negroMatDifuso);
    Esfera* boton2 = new Esfera(Punto(0.48, -0.6, 0.1), 0.035, negroMatDifuso);
    Esfera* boton3 = new Esfera(Punto(0.48, -0.5, 0.1), 0.035, negroMatDifuso);
    Esfera* boton4 = new Esfera(Punto(0.48, -0.4, 0.1), 0.035, negroMatDifuso);
    // Cara del muñeco de nieve
    Esfera* esferaCentroIzq = new Esfera(Punto(0.42, -0.18, 0.1), 0.03, azulClaroMatDifuso);
    Esfera* esferaCentroDcha = new Esfera(Punto(0.54, -0.18, 0.1), 0.03, azulClaroMatDifuso);
    // Esferas para la nariz
    Esfera* esferaNariz1 = new Esfera(Punto(0.48, -0.23, 0.1), 0.02, naranjaMatDifuso);
    Esfera* esferaNariz2 = new Esfera(Punto(0.48, -0.23, 0.07), 0.02, naranjaMatDifuso);
    // Cilindro de poca altura para el sombrero
    Cilindro* sombreroGrande = new Cilindro(Punto(0.442, -0.08, -0.1), 0.16, 0.02, negroMatDifuso);
    Cilindro* sombreroEncima = new Cilindro(Punto(0.445, -0.062, -0.1), 0.08, 0.12, negroMatDifuso);
    // Cilindro para los brazos
    Cilindro* brazoIzq = new Cilindro(Punto(0.26, -0.38, -0.1), 0.065, 0.018, negroMatDifuso);
    Cilindro* brazoDcha = new Cilindro(Punto(0.65, -0.38, -0.1), 0.065, 0.018, negroMatDifuso);
    // Esferas para las manos
    Esfera* manoIzq = new Esfera(Punto(0.195, -0.365, -0.1), 0.022, negroMatDifuso);
    Esfera* manoDcha = new Esfera(Punto(0.705, -0.365, -0.1), 0.022, negroMatDifuso);
    // Cilindro fino para simular bufanda entre la 2 y 3 esfera
    Cilindro* bufanda = new Cilindro(Punto(0.442, -0.29, -0.1), 0.14, 0.02, rojoMatDifuso);

    objetos.push_back(esferaNieve1);
    objetos.push_back(esferaNieve2);
    objetos.push_back(esferaNieve3);
    objetos.push_back(boton1);
    objetos.push_back(boton2);
    objetos.push_back(boton3);
    objetos.push_back(boton4);
    objetos.push_back(esferaCentroIzq);
    objetos.push_back(esferaCentroDcha);
    objetos.push_back(esferaNariz1);
    objetos.push_back(esferaNariz2);
    objetos.push_back(sombreroGrande);
    objetos.push_back(sombreroEncima);
    objetos.push_back(brazoIzq);
    objetos.push_back(brazoDcha);
    objetos.push_back(manoIzq);
    objetos.push_back(manoDcha);
    objetos.push_back(bufanda);
}

// Escena del arbol y muñeco de nieve
void escenaNavidad(vector<Geometria*>& objetos, vector<FuenteLuz*>& fuentes) {
    // Crear el arbol de navidad
    crearArbolNavidad(objetos);
    crearMunyecoNieve(objetos);

    
    // Planos
    Plano* plano = new Plano(2, Direccion(0.0, 0.0, -1), blancoMatDifuso, false);
    Plano* planoIzquierda = new Plano(1.1, Direccion(1.0, 0.0, 0.0), rojoMatDifuso, false);
    Plano* planoDerecha = new Plano(1.1, Direccion(-1.0, 0.0, 0.0), amarilloMatDifuso, false);
    Plano* techo = new Plano(1, Direccion(0.0, -1.0, 0.0), blancoMatDifuso, false);
    Plano* suelo = new Plano(1, Direccion(0.0, 1.0, 0.0), grisMatDifuso, false);

    objetos.push_back(plano);
    objetos.push_back(planoDerecha);
    objetos.push_back(planoIzquierda);
    objetos.push_back(techo);
    objetos.push_back(suelo);
 

    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), blanco);
    FuenteLuz* naranjaLuz = new FuenteLuz(Punto(0.0, 0.5, -1.5), naranja * 0.7);

    fuentes.push_back(blanca);
    
}

void textura(vector<Geometria*>& objetos, vector<FuenteLuz*>& fuentes) {
    Plano* plano = new Plano(1.0, Direccion(0.0, 0.0, -1.0), verdeMatDifuso, false);
    objetos.push_back(plano);

    // colocar 3 esferas en el plano de diferentes colores
    Esfera* esfera1 = new Esfera(Punto(-0.5, -0.0, 0.0), 0.2, blancoMatDifuso);
    Esfera* esfera2 = new Esfera(Punto(0.0, -0.0, 0.0), 0.2, rojoMatDifuso);
    Esfera* esfera3 = new Esfera(Punto(0.5, -0.0, 0.0), 0.2, azulMatDifuso);

    objetos.push_back(esfera1);
    objetos.push_back(esfera2);
    objetos.push_back(esfera3);

    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), blanco);
    // Poner una fuente en cada esquina
    FuenteLuz* otra = new FuenteLuz(Punto(0.3, 0.5, 0), blanco);
    FuenteLuz* otra2 = new FuenteLuz(Punto(-0.3, 0.5, 0), blanco);

    fuentes.push_back(blanca);
    fuentes.push_back(otra);
    fuentes.push_back(otra2);
}

void trianguloTextura(vector<Geometria*>& objetos, vector<FuenteLuz*>& fuentes) {
    Plano* plano = new Plano(1.0, Direccion(0.0, 0.0, -1.0));

    Plano* planoIzquierda = new Plano(1.0, Direccion(1.0, 0.0, 0.0));

    Plano* planoDerecha = new Plano(1.0, Direccion(-1.0, 0.0, 0.0));

    Plano* techo = new Plano(1.0, Direccion(0.0, -1.0, 0.0), blancoMatDifuso, false);
    Plano* suelo = new Plano(1.0, Direccion(0.0, 1.0, 0.0));

    plano->setMaterial(grisMatDifuso);
    suelo->setMaterial(grisMatDifuso);
    planoIzquierda->setMaterial(rojoMatDifuso);
    planoDerecha->setMaterial(verdeMatDifuso);

    objetos.push_back(plano);
    objetos.push_back(planoDerecha);
    objetos.push_back(planoIzquierda);
    objetos.push_back(techo);
    objetos.push_back(suelo);

    LectorHDR lectorTextura;
    ImagenHDR textura = lectorTextura.leerImagenHDR("ppms/textura.ppm");

    // Crear un triangulo con textura
    Triangulo* triangulo = new Triangulo(Punto(0.0, -0.5, 0.0), Punto(0.0, 0.5, 0.0), Punto(0.5, -0.5, 0.0), textura);
    Triangulo* trianguloGrande = new Triangulo(Punto(-0.65, -0.5, -0.2), Punto(-0.25, 0.1, -0.2), Punto(0.15, -0.5, -0.2), textura);


    objetos.push_back(trianguloGrande);

    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), blanco);
    // FuenteLuz* otra = new FuenteLuz(Punto(0.3, 0.5, 0), Color(0, 0, 255));

    fuentes.push_back(blanca);
    // fuentes.push_back(otra);
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
    // esferaCentro->setMaterial(turquesaMatDielectrico);
    esfera1->setMaterial(espejo);
    esfera2->setMaterial(espejo);
    esfera3->setMaterial(espejo);
    esfera4->setMaterial(espejo);

    esfera5->setMaterial(espejo);
    esfera6->setMaterial(espejo);
    esfera7->setMaterial(espejo);

    esfera8->setMaterial(espejo);
    esfera9->setMaterial(espejo);

    esfera10->setMaterial(espejo);

    objetos.push_back(plano);
    objetos.push_back(planoDerecha);
    objetos.push_back(planoIzquierda);
    objetos.push_back(techo);
    objetos.push_back(suelo);
    //objetos.push_back(cilindroIzq1);
    //objetos.push_back(cilindroIzq2);
    //objetos.push_back(cilindroIzq3);
    //objetos.push_back(cilindroDcha1);
    //objetos.push_back(cilindroDcha2);
    //objetos.push_back(cilindroDcha3);
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

    trianguloTextura(objetos, fuentes);
    FuenteLuz* blanca = new FuenteLuz(Punto(0.0, 0.5, 0), blanco);
    FuenteLuz* naranjaLuz = new FuenteLuz(Punto(0.0, 0.5, -1.5), naranja * 0.7);

    fuentes.push_back(blanca);
    fuentes.push_back(naranjaLuz);
}


int main(int argc, char* argv[]) {

    // Leer los parametros de entrada

    int ancho = 512;         // Valor predeterminado para el ancho
    int alto = 512;          // Valor predeterminado para el alto
    string nombre = "imagenEscena";      // Nombre del archivo de salida
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
    LectorHDR lectorTextura;

    // ImagenHDR textura = lectorTextura.leerImagenHDR("texturas/imagenSalida.ppm");
    // ImagenHDR textura = lectorTextura.leerImagenHDR("ppms/imagenSalida.ppm");

    // ImagenHDR imagen = lector.leerImagenHDR("ppms/seymour_park.ppm");
    // Probar a escribir la imagen "ppms/forest_path.ppm"
    EscritorHDR escritor;

    // Crear una camara en el origen de la escena
    Camara camara(Direccion(-1.0, 0.0, 0.0), Direccion(0.0, 1.0, 0.0), Direccion(0.0, 0.0, 3.0), Punto(0.0, 0.0, -3.5), alto, ancho, muestras, resolucion);

    vector<Geometria*> objetos = vector<Geometria*>();
    vector<FuenteLuz*> fuentes = vector<FuenteLuz*>();

    trianguloTextura(objetos, fuentes);
    //columnasCornellBox(objetos, fuentes);
    // fuentes.push_back(otra);

    /*-------- MEDIR TIEMPOS ------- */
    // Comparar cuanto tiempo tarda sin y con area de luz

    // auto start_time = std::chrono::high_resolution_clock::now();


    ImagenHDR imagenEscena = camara.renderizar(objetos, fuentes, resolucion);

    // auto end_time = std::chrono::high_resolution_clock::now();
    // auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // std::cout << "Tiempo de renderizado: " << duration_ms.count() << " ms" << std::endl;

    ToneMapping toneMapping = ToneMapping(imagenEscena);
    toneMapping.curvaGamma(1 / 2.2);
    //toneMapping.ecualizacion();
    escritor.escribirImagenHDR("ppms/" + nombre + ".ppm", toneMapping.imagen);
    return 0;
}
