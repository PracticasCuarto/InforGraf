#ifndef TONE_MAPPING_HPP
#define TONE_MAPPING_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include <math.h>
#include <vector>  
#include "ImagenHDR.hpp"

using namespace std;

class ToneMapping {
public:
    // La tarea consiste en desarrollar una serie de estrategias de tone mapping como aplicaciones independientes, que tengan como parámetros la imagen de entrada HDR, la imagen de salida
    // LDR y los parámetros del operador de tone mapping. Una vez cargada en la memoria de la computadora, una imagen se guarda como un vector 2D de tripletas RGB con precisión de
    // punto flotante, para evitar la pérdida de información al abrir y guardar la imagen.
    // Definir valores entrada y el constructor
    vector<vector<double>> imagenHDR;
    float v;
    float gamma;

    ToneMapping(vector<vector<double>> _imagenHDR, float _v, float _gamma);

    // Clamping: Acotar todos los valores superiores a 255 (1 en coma flotante).
    void clamping(ImagenHDR imagenHDR);

    // Ecualización: Transformación lineal de los valores desde el mínimo hasta el máximo (normalización).
    void ecualizacion(ImagenHDR imagenHDR);

    // Ecualización y clamp: Combinar los dos anteriores según un parámetro de ”clamping.” Nótese que los dos operadores anteriores pueden considerarse casos particularesde este operador.
    void ecualizacionClamp(ImagenHDR imagenHDR, float v);

    // Curva gamma: Aplicar una curva gamma a todos los valores (necesita ecualización primero).
    void curvaGamma(ImagenHDR imagenHDR, float gamma);

    // Clamp y curva gamma: Aplicar una curva gamma después de una operación de clamping (necesita ecualización primero). Nótese que todos los operadores anteriores pueden verse como casos particulares de este operador.
    void clampCurvaGamma(ImagenHDR imagenHDR, float v, float gamma);
};


#endif
