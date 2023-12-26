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

    ImagenHDR();

    // Constructor por defecto
    ImagenHDR(vector<vector<double>>& matriz, int ancho, int alto, double valorMaximo, double resolucionColor);

    // Getters
    vector<vector<double>> getMatriz();
    int getAncho() const;
    int getAlto() const;
    double getValorMaximo() const;
    double getResolucionColor() const;

    // Setters
    void setMatriz(vector<vector<double>>& matriz);

    // Sobrecargar operacion de comparacion de igualdad (==)
    bool operator==(ImagenHDR& imagen);

    // Sobrecargar operacion de desigualdad (!=)
    bool operator!=(ImagenHDR& imagen);

    // Funcion que dado una coordenada "x" y una "y" devuelve el pixel correspondiente
    vector<double> getPixel(int fila, int columna) const;
};

#endif
