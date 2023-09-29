#include "ToneMapping.hpp"
#include <iostream>
#include <string> 
#include <vector>

using namespace std;

// Constructor por defecto
ToneMapping::ToneMapping(ImagenHDR& imagen) : imagen(imagen) {}

// Operadores de Tone Mapping
// Clamping: Acotar todos los valores superiores a 255 (1 en coma flotante).
void ToneMapping::clamping() {
    for (int i = 0; i < imagen.getAlto(); i++) {
        for (int j = 0; j < imagen.getAncho(); j++) {
            if (imagen.getMatriz()[i][j] > 1) {
                imagen.getMatriz()[i][j] = 1;
            }
        }
    }
}

// Ecualización: Transformación lineal de los valores desde el mínimo hasta el máximo (normalización).
void ToneMapping::ecualizacion() {
    float min = 1;
    float max = 0;
    for (int i = 0; i < imagen.getAlto(); i++) {
        for (int j = 0; j < imagen.getAncho(); j++) {
            if (imagen.getMatriz()[i][j] < min) {
                min = imagen.getMatriz()[i][j];
            }
            if (imagen.getMatriz()[i][j] > max) {
                max = imagen.getMatriz()[i][j];
            }
        }
    }
    for (int i = 0; i < imagen.getAlto(); i++) {
        for (int j = 0; j < imagen.getAncho(); j++) {
            imagen.getMatriz()[i][j] = (imagen.getMatriz()[i][j] - min) / (max - min);
        }
    }
}

// Ecualización hasta el valor v: Transformación lineal de los valores desde el mínimo hasta v.
void ToneMapping::ecualizacionHastaV(float v) {
    float min = 1;
    float max = 0;
    for (int i = 0; i < imagen.getAlto(); i++) {
        for (int j = 0; j < imagen.getAncho(); j++) {
            if (imagen.getMatriz()[i][j] < min) {
                min = imagen.getMatriz()[i][j];
            }
            if (imagen.getMatriz()[i][j] > max) {
                max = imagen.getMatriz()[i][j];
            }
        }
    }
    for (int i = 0; i < imagen.getAlto(); i++) {
        for (int j = 0; j < imagen.getAncho(); j++) {
            imagen.getMatriz()[i][j] = (imagen.getMatriz()[i][j] - min) / (v - min);
        }
    }
}

// Ecualización y clamp: Combinar los dos anteriores según un parámetro de ”clamping.” Nótese que los dos operadores anteriores pueden considerarse casos particularesde este operador.
void ToneMapping::ecualizacionClamp(float v) {
    ecualizacionHastaV(v);
    clamping();
}

// Curva gamma: Aplicar una curva gamma a todos los valores (necesita ecualización primero).
void ToneMapping::curvaGamma(float gamma) {
    ecualizacion();
    for (int i = 0; i < imagen.getAlto(); i++) {
        for (int j = 0; j < imagen.getAncho(); j++) {
            imagen.getMatriz()[i][j] = pow(imagen.getMatriz()[i][j], gamma);
        }
    }
}

// Clamp y curva gamma: Aplicar una curva gamma después de una operación de clamping (necesita ecualización primero). Nótese que todos los operadores anteriores pueden verse como casos particulares de este operador.
void ToneMapping::clampCurvaGamma(float v, float gamma) {
    ecualizacionClamp(v);
    curvaGamma(gamma);
}
