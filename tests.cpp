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

    // Probar las operaciones de tone mapping sobre la imagen
    // cout << "Cargando imagen..." << endl;
    // ImagenHDR imagenClamp = imagen;
    // ImagenHDR imagenEcualizacion = imagen;
    // ImagenHDR imagenEcualizacionHastaV = imagen;
    // ImagenHDR imagenClampEcualizacion = imagen;
    // ImagenHDR imagenGamma = imagen;
    // ImagenHDR imagenClampGamma = imagen;
    // ImagenHDR imagenReinhard = imagen;


    // cout << "Aplicando tone mapping..." << endl;
    // ToneMapping toneMappingClamp(imagenClamp);
    // ToneMapping toneMappingEcualizacion(imagenEcualizacion);
    // ToneMapping toneMappingEcualizacionHastaV(imagenEcualizacionHastaV);
    // ToneMapping toneMappingClampEcualizacion(imagenClampEcualizacion);
    // ToneMapping toneMappingGamma(imagenGamma);
    // ToneMapping toneMappingClampGamma(imagenClampGamma);
    // ToneMapping toneMappingReinhard(imagenReinhard);

    // toneMappingClamp.clamping();
    // toneMappingEcualizacion.ecualizacion();
    // toneMappingEcualizacionHastaV.ecualizacionHastaV(0.8);
    // toneMappingClampEcualizacion.clamping();
    // toneMappingClampEcualizacion.ecualizacion();
    // toneMappingGamma.curvaGamma(0.6);
    // toneMappingClampGamma.clampCurvaGamma(0.8, 0.6);
    // toneMappingReinhard.reinhard(1000);


    // Probar a escribir las imagenes resultantes
    // cout << "Escribiendo imagenes..." << endl;
    // escritor.escribirImagenHDR("ppms/forest_path_clamp.ppm", imagenClamp);
    // escritor.escribirImagenHDR("ppms/forest_path_ecualizacion.ppm", imagenEcualizacion);
    // escritor.escribirImagenHDR("ppms/forest_path_ecualizacionHastaV.ppm", imagenEcualizacionHastaV);
    // escritor.escribirImagenHDR("ppms/forest_path_clampEcualizacion.ppm", imagenClampEcualizacion);
    // escritor.escribirImagenHDR("ppms/forest_path_gamma.ppm", imagenGamma);
    // escritor.escribirImagenHDR("ppms/seymour_park_clampGamma.ppm", imagenClampGamma);
    // escritor.escribirImagenHDR("ppms/seymour_park_reinhard_1000.ppm", imagenReinhard);

    // // Probar la interseccion de un rayo con un plano
    // Plano plano(10.0, Direccion(0.0, -1.0, 0.0));
    // Rayo rayo1(Punto(0.0, 0.0, 0.0), Direccion(1.0, 0.0, 0.0));

    // Punto interseccion = rayo1.interseccion(plano);
    // assert(interseccion.x == -INFINITY && interseccion.y == -INFINITY && interseccion.z == -INFINITY);
    // // assert(interseccion.x == 10.0 && interseccion.y == 0.0 && interseccion.z == 0.0);

    // // Probar la interseccion de un rayo con una esfera
    // Esfera esfera(Punto(10.0, 0.0, 0.0), 5.0);
    // Rayo rayo2(Punto(10.0, 0.0, 0.0), Direccion(1.0, 1.0, 0.0));

    // interseccion = rayo2.interseccion(esfera);
    // cout << "interseccion.x: " << interseccion.x << endl;
    // cout << "interseccion.y: " << interseccion.y << endl;
    // cout << "interseccion.z: " << interseccion.z << endl;
    // // assert(interseccion.x == 13.54 && interseccion.y == 3.54 && interseccion.z == 0.0);

    // // Probar la interseccion de un rayo con un triangulo
    // Triangulo triangulo(Punto(0.0, 0.0, 0.0), Punto(0.0, 1.0, 0.0), Punto(1.0, 0.0, 0.0));
    // Rayo rayo3(Punto(-1.0, -1.0, 0.0), Direccion(1.0, 1.0, 0.0));

    // interseccion = rayo3.interseccion(triangulo);
    // cout << "interseccion.x: " << interseccion.x << endl;
    // cout << "interseccion.y: " << interseccion.y << endl;
    // cout << "interseccion.z: " << interseccion.z << endl;
    // assert(interseccion.x == 0.0 && interseccion.y == 0.0 && interseccion.z == 0.0);


    // std::cout << "Todas las pruebas de tone mapping pasaron con éxito." << std::endl;

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

    vector<Geometria*> objetos = vector<Geometria*>();
    objetos.push_back(esfera);
    objetos.push_back(esfera2);
    objetos.push_back(plano);
    objetos.push_back(planoDerecha);
    objetos.push_back(planoIzquierda);
    objetos.push_back(techo);
    ImagenHDR imagenEscena = camara.renderizar(objetos);
    escritor.escribirImagenHDR("ppms/imagenEscena.ppm", imagenEscena);
    return 0;
}
