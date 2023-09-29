#include <iostream>
#include <cassert>

#include "src/Direccion.hpp"
#include "src/Punto.hpp"
#include "src/Matriz.hpp"
#include "src/Estacion.hpp"
#include "src/Esfera.hpp"
#include "src/LectorHDR.hpp"
#include "src/EscritorHDR.hpp"
#include "src/ToneMapping.hpp"


int main() {
    // Crear objetos de dirección para las pruebas
    Direccion dir1(1.0, 2.0, 3.0);
    Direccion dir2(2.0, 3.0, 4.0);

    // Prueba de la sobrecarga del operador de salida por pantalla
    std::cout << "Dir1: " << dir1 << std::endl;

    // Prueba de la sobrecarga del operador de resta
    Direccion resta = dir1 - dir2;
    assert(resta.x == -1.0 && resta.y == -1.0 && resta.z == -1.0);

    // Prueba de la sobrecarga del operador de suma
    Direccion suma = dir1 + dir2;
    assert(suma.x == 3.0 && suma.y == 5.0 && suma.z == 7.0);

    // Prueba de la sobrecarga del operador de multiplicación escalar (dot product)
    double productoPunto = dir1 * dir2;
    assert(productoPunto == 20.0);

    // Prueba de la sobrecarga del operador de multiplicación escalar
    Direccion productoEscalar = dir1 * 2.0;
    assert(productoEscalar.x == 2.0 && productoEscalar.y == 4.0 && productoEscalar.z == 6.0);

    // Prueba de la sobrecarga del operador de división por escalar
    Direccion divisionEscalar = dir1 / 2.0;
    assert(divisionEscalar.x == 0.5 && divisionEscalar.y == 1.0 && divisionEscalar.z == 1.5);

    // Prueba de la sobrecarga del operador de producto cruzado
    Direccion cruz = dir1.cross(dir2);
    assert(cruz.x == -1.0 && cruz.y == 2.0 && cruz.z == -1.0);

    // Prueba del cálculo del módulo
    double mod = dir1.modulo();
    assert(mod == sqrt(14)); // Aproximadamente igual a la raíz cuadrada de 14

    // Prueba de la normalización
    Direccion normalizada = dir1.normalizar();
    const double tolerancia = 0.00001; // Define una tolerancia adecuada

    assert(std::abs(normalizada.x - (dir1.x / mod)) < tolerancia &&
        std::abs(normalizada.y - (dir1.y / mod)) < tolerancia &&
        std::abs(normalizada.z - (dir1.z / mod)) < tolerancia);

    std::cout << "Todas las pruebas de direcciones pasaron con éxito." << std::endl;

    std::cout << "----------------------------------------------------" << std::endl;

    // Crear objetos de punto para las pruebas
    Punto punto1(1.0, 2.0, 3.0);
    Punto punto2(2.0, 3.0, 4.0);
    Direccion direccion(1.0, 1.0, 1.0);

    // Prueba de la sobrecarga del operador de resta
    Direccion restaDir = punto1 - punto2;
    assert(restaDir.x == -1.0 && restaDir.y == -1.0 && restaDir.z == -1.0);

    // Prueba de la sobrecarga del operador de suma de un punto con una dirección
    Punto sumaDir = punto1 + direccion;
    assert(sumaDir.x == 2.0 && sumaDir.y == 3.0 && sumaDir.z == 4.0);

    // Prueba de la sobrecarga del operador de salida por pantalla
    std::cout << "Punto1: " << punto1 << std::endl;

    std::cout << "Todas las pruebas de puntos pasaron con éxito." << std::endl;

    std::cout << "----------------------------------------------------" << std::endl;

    // Crear objetos de matriz para las pruebas
    Matriz matriz1(1.0, 3.0, 23.0, 14.0,
        5.0, 125.0, 7.0, 8.0,
        91.0, 10.0, 17.0, 12.0,
        13.0, 1.0, 15.0, 21.0);

    std::cout << "Matriz1: " << std::endl << matriz1 << std::endl;

    // Probar la matriz inversa
    Matriz inversa = matriz1.transformadaInversa();
    std::cout << "Inversa de Matriz1: " << std::endl << inversa << std::endl;

    // Probar los calculos relacionados con la estacion y esfera
    // centro, eje, ciudad de referencia
    Esfera esfera(Punto(0.0, 0.0, 0.0), Punto(0.0, 0.0, 1.0), Direccion(0.0, 1.0, 0.0));
    // Esfera con diferentes valores
    Esfera esfera2(Punto(2.0, 0.0, 0.0), Punto(0.0, 0.0, 0.0), Direccion(0.0, 2.0, 0.0));

    // Crear una estacion y verificar sus valores
    Estacion estacion(esfera, 0.0, 0.0);
    // std::cout << "getPosicion().x: " << std::endl << estacion.getPosicion().x << std::endl;
    // std::cout << "getPosicion().y: " << std::endl << estacion.getPosicion().y << std::endl;
    // std::cout << "getPosicion().z: " << std::endl << estacion.getPosicion().z << std::endl;
    // std::cout << "getRadio()" << std::endl << esfera.getRadio() << std::endl;

    // assert(estacion.getPosicion().x == 1.0 && estacion.getPosicion().y == 0.0 && estacion.getPosicion().z == 0.0);
    // assert(estacion.getNormal().x == 1.0 && estacion.getNormal().y == 0.0 && estacion.getNormal().z == 0.0);
    // assert(estacion.getTangenteLongitud().x == 1.0 && estacion.getTangenteLongitud().y == 0.0 && estacion.getTangenteLongitud().z == 0.0);
    // assert(estacion.getTangenteLatitud().x == 0.0 && estacion.getTangenteLatitud().y == 1.0 && estacion.getTangenteLatitud().z == 0.0);

    // Crear otra estacion y verificar sus valores
    Estacion estacion2(esfera2, 90.0, 0.0);

    // Comprobar si hay colision entre las dos estaciones
    Direccion direccionConexion = estacion.conectar(estacion2);

    // Probar a leer la imagen "ppms/forest_path.ppm"
    LectorHDR lector;
    ImagenHDR imagen = lector.leerImagenHDR("ppms/bosque.ppm");
    // Probar a escribir la imagen "ppms/forest_path.ppm"
    EscritorHDR escritor;
    escritor.escribirImagenHDR("ppms/bosqueEscrito.ppm", imagen);

    // Asegurar que el operador de igualdad de imagenes esta bien implementado
    assert(imagen == imagen);

    // Probar las operaciones de tone mapping sobre la imagen
    ImagenHDR imagenClamp = imagen;
    // ImagenHDR imagenEcualizacion = imagen;
    // ImagenHDR imagenEcualizacionHastaV = imagen;
    // ImagenHDR imagenClampEcualizacion = imagen;
    // ImagenHDR imagenGamma = imagen;
    // ImagenHDR imagenClampGamma = imagen;

    ToneMapping toneMappingClamp(imagenClamp);
    // ToneMapping toneMappingEcualizacion(imagenEcualizacion);
    // ToneMapping toneMappingEcualizacionHastaV(imagenEcualizacionHastaV);
    // ToneMapping toneMappingClampEcualizacion(imagenClampEcualizacion);
    // ToneMapping toneMappingGamma(imagenGamma);
    // ToneMapping toneMappingClampGamma(imagenClampGamma);

    toneMappingClamp.clamping();
    // toneMappingEcualizacion.ecualizacion();
    // toneMappingEcualizacionHastaV.ecualizacionHastaV(0.5);
    // toneMappingClampEcualizacion.clamping();
    // toneMappingClampEcualizacion.ecualizacion();
    // toneMappingGamma.curvaGamma(2.0);
    // toneMappingClampGamma.clampCurvaGamma(0.5, 2.0);

    // Probar a escribir las imagenes resultantes
    escritor.escribirImagenHDR("ppms/bosqueClamp.ppm", imagenClamp);
    // escritor.escribirImagenHDR("ppms/forest_path_ecualizacion.ppm", imagenEcualizacion);
    // escritor.escribirImagenHDR("ppms/forest_path_ecualizacionHastaV.ppm", imagenEcualizacionHastaV);
    // escritor.escribirImagenHDR("ppms/forest_path_clampEcualizacion.ppm", imagenClampEcualizacion);
    // escritor.escribirImagenHDR("ppms/forest_path_gamma.ppm", imagenGamma);
    // escritor.escribirImagenHDR("ppms/forest_path_clampGamma.ppm", imagenClampGamma);

    std::cout << "Todas las pruebas de tone mapping pasaron con éxito." << std::endl;

    return 0;
}
