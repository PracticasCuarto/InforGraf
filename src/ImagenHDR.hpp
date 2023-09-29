#ifndef IMAGEN_HDR_HPP
#define IMAGEN_HDR_HPP

#include <iostream>
#include <string> 
#include <ostream>
#include <math.h>
#include <vector>

using namespace std;

class ImagenHDR {
private:
    vector<vector<double>> matriz;
    int ancho;
    int alto;
    double valorMaximo;
    double resolucionColor;
public:

    // Constructor por defecto
    ImagenHDR(vector<vector<double>>& matriz, int ancho, int alto, double valorMaximo, double resolucionColor);

    // Getters
    vector<vector<double>> getMatriz();
    int getAncho();
    int getAlto();
    double getValorMaximo();
    double getResolucionColor();
};

#endif
