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
    vector<vector<double>> matriz = this->imagen.getMatriz();
    double alto = this->imagen.getAlto();
    double ancho = this->imagen.getAncho();
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho * 3; j++) {
            if (matriz[i][j] >= 1) {
                matriz[i][j] = 1;
            }
        }
    }
    this->imagen.setMatriz(matriz);
}

// Ecualización: Transformación lineal de los valores desde el mínimo hasta el máximo (normalización).
void ToneMapping::ecualizacion() {
    float min = 1;
    float max = 0;
    vector<vector<double>> matriz = this->imagen.getMatriz();
    double alto = this->imagen.getAlto();
    double ancho = this->imagen.getAncho();
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho * 3; j++) {
            if (matriz[i][j] < min) {
                min = matriz[i][j];
            }
            if (matriz[i][j] > max) {
                max = matriz[i][j];
            }
        }
    }

    for (int i = 0; i < imagen.getAlto(); i++) {
        for (int j = 0; j < imagen.getAncho() * 3; j++) {
            matriz[i][j] = (matriz[i][j]) / (max);
        }
    }

    this->imagen.setMatriz(matriz);
}

// Ecualización hasta el valor v: Transformación lineal de los valores desde el mínimo hasta v.
void ToneMapping::ecualizacionHastaV(float v) {
    float min = 1;
    float max = 0;
    vector<vector<double>> matriz = this->imagen.getMatriz();
    double alto = this->imagen.getAlto();
    double ancho = this->imagen.getAncho();
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho * 3; j++) {
            if (matriz[i][j] < min) {
                min = matriz[i][j];
            }
            if (matriz[i][j] > max) {
                max = matriz[i][j];
            }
        }
    }
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho * 3; j++) {
            matriz[i][j] = (matriz[i][j] - min) / (v - min);
        }
    }

    this->imagen.setMatriz(matriz);
}

// Ecualización y clamp: Combinar los dos anteriores según un parámetro de ”clamping.” Nótese que los dos operadores anteriores pueden considerarse casos particularesde este operador.
void ToneMapping::ecualizacionClamp(float v) {
    ecualizacionHastaV(v);
    clamping();
}

// Curva gamma: Aplicar una curva gamma a todos los valores (necesita ecualización primero).
void ToneMapping::curvaGamma(float gamma) {
    ecualizacion();
    vector<vector<double>> matriz = this->imagen.getMatriz();
    double alto = this->imagen.getAlto();
    double ancho = this->imagen.getAncho();
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho * 3; j++) {
            double valor = pow(matriz[i][j], gamma);
            if (valor > 1) {
                valor = 1;
            }
            matriz[i][j] = valor;
        }
    }

    this->imagen.setMatriz(matriz);
}

// Clamp y curva gamma: Aplicar una curva gamma después de una operación de clamping (necesita ecualización primero). Nótese que todos los operadores anteriores pueden verse como casos particulares de este operador.
void ToneMapping::clampCurvaGamma(float v, float gamma) {
    ecualizacionClamp(v);
    curvaGamma(gamma);
}


float luminance(vec3 v) {
    return v.x * 0.2126f + v.y * 0.7152f + v.z * 0.0722f;
}

vec3 change_luminance(vec3 c_in, float l_out) {
    float l_in = luminance(c_in);
    // return c_in * (l_out / l_in);
    // Para cada pixel del color, multiplica por el ratio entre la luminancia deseada y la luminancia actual
    float x = c_in.x * (l_out / l_in);
    float y = c_in.y * (l_out / l_in);
    float z = c_in.z * (l_out / l_in);
    return { x, y, z };
}

vec3 reinhard_extended_luminance(vec3 v, float max_white_l) {
    float l_old = luminance(v);
    float numerator = l_old * (1.0f + (l_old / (max_white_l * max_white_l)));
    float l_new = numerator / (1.0f + l_old);
    return change_luminance(v, l_new);
}


// Función para aplicar el operador Reinhard a toda la imagen
void ToneMapping::reinhard(float max_white_l) {
    vector<vector<double>> matriz = this->imagen.getMatriz();
    double alto = this->imagen.getAlto();
    double ancho = this->imagen.getAncho();

    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho * 3; j += 3) {
            // Obtén el pixel actual
            vec3 pixel;
            pixel.x = matriz[i][j];
            pixel.y = matriz[i][j + 1];
            pixel.z = matriz[i][j + 2];

            // Aplica el operador Reinhard al pixel
            vec3 resultado = reinhard_extended_luminance(pixel, max_white_l);

            // Actualiza los valores de color en la matriz
            matriz[i][j] = resultado.x;
            matriz[i][j + 1] = resultado.y;
            matriz[i][j + 2] = resultado.z;
        }
    }

    this->imagen.setMatriz(matriz);
}