#include "ImagenHDR.hpp"
#include <vector>
#include <iostream>

using namespace std;

// Constructor por defecto
ImagenHDR::ImagenHDR(vector<vector<double>>& _matriz, int ancho, int alto, double valorMaximo, double resolucionColor) : matriz(_matriz), ancho(ancho), alto(alto), valorMaximo(valorMaximo), resolucionColor(resolucionColor) {}

// Getters

vector<vector<double>> ImagenHDR::getMatriz() {
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

// Setters
void ImagenHDR::setMatriz(vector<vector<double>>& _matriz) {
    this->matriz = _matriz;
}

// Sobrecargar operacion de comparacion de igualdad (==)
bool ImagenHDR::operator==(ImagenHDR& imagen) {
    return (matriz == imagen.getMatriz() && ancho == imagen.getAncho() && alto == imagen.getAlto() && valorMaximo == imagen.getValorMaximo() && resolucionColor == imagen.getResolucionColor());
}

// Sobrecargar operacion de desigualdad (!=)
bool ImagenHDR::operator!=(ImagenHDR& imagen) {
    return (matriz != imagen.getMatriz() || ancho != imagen.getAncho() || alto != imagen.getAlto() || valorMaximo != imagen.getValorMaximo() || resolucionColor != imagen.getResolucionColor());
}