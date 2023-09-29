#include "ImagenHDR.hpp"
#include <vector>
#include <iostream>

using namespace std;

// Constructor por defecto
ImagenHDR::ImagenHDR(vector<vector<double>>& _matriz, int ancho, int alto, double valorMaximo, double resolucionColor) : matriz(_matriz), ancho(ancho), alto(alto), valorMaximo(valorMaximo), resolucionColor(resolucionColor) {}

// Getters

vector<vector<double>> ImagenHDR::getMatriz() {
    cout << matriz[0][0] << endl;
    cout << matriz.size() << endl;
    return matriz;
}

int ImagenHDR::getAncho() {
    return ancho;
}

int ImagenHDR::getAlto() {
    return alto;
}

double ImagenHDR::getValorMaximo() {
    return valorMaximo;
}

double ImagenHDR::getResolucionColor() {
    return resolucionColor;
}