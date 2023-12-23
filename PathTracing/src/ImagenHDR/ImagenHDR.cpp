#include "ImagenHDR.hpp"
#include <vector>
#include <iostream>

using namespace std;

// Constructor vacio
ImagenHDR::ImagenHDR() {

}

// Constructor por defecto
ImagenHDR::ImagenHDR(vector<vector<double>>& _matriz, int ancho, int alto, double valorMaximo, double resolucionColor) : matriz(_matriz), ancho(ancho), alto(alto), valorMaximo(valorMaximo), resolucionColor(resolucionColor) {}

// Getters

vector<vector<double>> ImagenHDR::getMatriz() {
    return matriz;
}

int ImagenHDR::getAncho() const {
    return ancho;
}

int ImagenHDR::getAlto() const {
    return alto;
}

double ImagenHDR::getValorMaximo() const {
    return valorMaximo;
}

double ImagenHDR::getResolucionColor() const {
    return resolucionColor;
}

// Funcion que dado una coordenada "x" y una "y" devuelve el pixel correspondiente
vector<double> ImagenHDR::getPixel(int fila, int columna) const {
    vector<double> result;
    result.push_back(matriz[fila][columna * 3]);
    result.push_back(matriz[fila][columna * 3 + 1]);
    result.push_back(matriz[fila][columna * 3 + 2]);

    return result;
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