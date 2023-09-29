#include "ToneMapping.hpp"
#include <iostream>
#include <string> 
#include <vector>

using namespace std;

ToneMapping::ToneMapping(vector<vector<double>> _imagenHDR, float _v, float _gamma) {
    imagenHDR = _imagenHDR;
    v = _v;
    gamma = _gamma;
}

// Operadores de Tone Mapping
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

