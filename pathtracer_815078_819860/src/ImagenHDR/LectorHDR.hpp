#ifndef LECTOR_HDR_HPP
#define LECTOR_HDR_HPP

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

class LectorHDR {
public:

    // Constructor por defecto
    LectorHDR();

    // Función para leer una imagen HDR y guardarla en una matriz
    ImagenHDR leerImagenHDR(string nombreArchivo);

};

#endif
