#ifndef ESCRITOR_HDR_HPP
#define ESCRITOR_HDR_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include <math.h>
#include <vector>

#include "ImagenHDR.hpp"

using namespace std;

/*
    El formato de las imagenes es el siguiente:
    P3          -> Identificador de formato de la imagen
    # feep.ppm  -> Comentario (puede haber varios)
    4 4         -> Ancho y alto de la imagen
    15          -> Valor maximo de cada componente RGB
    0 0 0 0 0 0 0 0 0 15 0 15
    0 0 0 0 15 7 0 0 0 0 0 0
    0 0 0 0 0 0 0 15 7 0 0 0
    15 0 15 0 0 0 0 0 0 0 0 0
*/

class EscritorHDR {
public:

    // Constructor por defecto
    EscritorHDR();

    // Función para escribir una imagen HDR cargada en memoria y guardarla en un archivo
    void escribirImagenHDR(string nombreArchivo, ImagenHDR imagen);

};

#endif
