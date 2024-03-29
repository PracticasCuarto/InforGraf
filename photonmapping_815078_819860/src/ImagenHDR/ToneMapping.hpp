#ifndef TONE_MAPPING_HPP
#define TONE_MAPPING_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include <math.h>
#include <vector>  
#include "ImagenHDR.hpp"

using namespace std;

// Clase que permite aplicar operadores de Tone Mapping a una imagen HDR
class ToneMapping {
public:
    ImagenHDR& imagen;

    // Constructor completo
    ToneMapping(ImagenHDR& imagen);

    // Clamping: Acotar todos los valores superiores a 255 (1 en coma flotante).
    void clamping();

    // Ecualización: Transformación lineal de los valores desde el mínimo hasta el máximo (normalización).
    void ecualizacion();

    // Ecualización hasta el valor v: Transformación lineal de los valores desde el mínimo hasta v.
    void ecualizacionHastaV(float v);

    // Ecualización y clamp: Combinar los dos anteriores según un parámetro de ”clamping.” Nótese que los dos operadores anteriores pueden considerarse casos particularesde este operador.
    void ecualizacionClamp(float v);

    // Curva gamma: Aplicar una curva gamma a todos los valores (necesita ecualización primero).
    void curvaGamma(float gamma);

    // Clamp y curva gamma: Aplicar una curva gamma después de una operación de clamping (necesita ecualización primero). Nótese que todos los operadores anteriores pueden verse como casos particulares de este operador.
    void clampCurvaGamma(float v, float gamma);

    // Función para aplicar el operador Reinhard a toda la imagen
    // Funcion y sus auxiliares obtenidas de: https://64.github.io/tonemapping/#extended-reinhard-luminance-tone-map
    void reinhard(float max_white_l);
};

struct vec3 {
    float x;
    float y;
    float z;
};

#endif
