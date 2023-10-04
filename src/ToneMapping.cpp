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
                cout << "Clamping" << endl;
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
        for (int j = 0; j < imagen.getAncho(); j++) {
            matriz[i][j] = (matriz[i][j] - min) / (max - min);
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
            matriz[i][j] = pow(matriz[i][j], gamma);
        }
    }

    this->imagen.setMatriz(matriz);
}

// Clamp y curva gamma: Aplicar una curva gamma después de una operación de clamping (necesita ecualización primero). Nótese que todos los operadores anteriores pueden verse como casos particulares de este operador.
void ToneMapping::clampCurvaGamma(float v, float gamma) {
    ecualizacionClamp(v);
    curvaGamma(gamma);
}

// Calcula la luminancia de la imagen HDR
double ToneMapping::calcularLuminancia() {
    vector<vector<double>> matriz = this->imagen.getMatriz();
    double luminancia = 0.0;
    double alto = this->imagen.getAlto();
    double ancho = this->imagen.getAncho();

    // Calcular la luminancia como el promedio ponderado de los canales RGB
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            double r = matriz[i][j * 3];
            double g = matriz[i][j * 3 + 1];
            double b = matriz[i][j * 3 + 2];
            luminancia += 0.2126 * r + 0.7152 * g + 0.0722 * b;
        }
    }

    // Normalizar la luminancia dividiendo por el número total de píxeles
    luminancia /= (alto * ancho);

    return luminancia;
}

// Aplica el algoritmo de tone mapping de Reinhard
void ToneMapping::toneMappingReinhard(double alpha) {
    double luminancia = calcularLuminancia();

    // Calcular la media logarítmica de la luminancia
    double logMedia = log(1.0 + alpha * luminancia);

    // Escalar la luminancia de acuerdo a la media logarítmica
    vector<vector<double>> matriz = this->imagen.getMatriz();
    double alto = this->imagen.getAlto();
    double ancho = this->imagen.getAncho();

    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            double r = matriz[i][j * 3];
            double g = matriz[i][j * 3 + 1];
            double b = matriz[i][j * 3 + 2];

            // Escalar los canales RGB de acuerdo a la media logarítmica
            r = (r / (1.0 + alpha * luminancia)) * logMedia;
            g = (g / (1.0 + alpha * luminancia)) * logMedia;
            b = (b / (1.0 + alpha * luminancia)) * logMedia;

            matriz[i][j * 3] = r;
            matriz[i][j * 3 + 1] = g;
            matriz[i][j * 3 + 2] = b;
        }
    }

    this->imagen.setMatriz(matriz);
}
