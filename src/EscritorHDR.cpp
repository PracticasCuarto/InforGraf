#include "EscritorHDR.hpp"
#include "ImagenHDR.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

EscritorHDR::EscritorHDR() {
    // Constructor por defecto, no necesitas hacer nada aquí.
}

void EscritorHDR::escribirImagenHDR(string nombreArchivo, ImagenHDR imagen) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    // Mostrar por pantalla los valores de la imagen
    cout << "Ancho: " << imagen.getAncho() << endl;
    cout << "Alto: " << imagen.getAlto() << endl;
    cout << "Valor máximo: " << imagen.getValorMaximo() << endl;
    cout << "Resolución de color: " << imagen.getResolucionColor() << endl;

    // Escribir el encabezado del archivo PPM
    archivo << "P3" << endl;
    archivo << "# Imagen HDR" << endl;
    if (imagen.getValorMaximo() != 0) {
        archivo << "#MAX=" << imagen.getValorMaximo() << endl;
    }
    archivo << imagen.getAncho() << " " << imagen.getAlto() << endl;
    archivo << fixed << setprecision(0) << imagen.getResolucionColor() << endl;

    double valorMaximo = imagen.getValorMaximo();
    if (valorMaximo == 0) {
        valorMaximo = 1;
    }

    vector<vector<double>> imagenHDR = imagen.getMatriz();


    // Escribir los valores de píxeles en el archivo
    for (int i = 0; i < imagen.getAlto(); i++) {
        for (int j = 0; j < imagen.getAncho() * 3; j += 3) {
            int r = static_cast<int>(imagenHDR[i][j] * imagen.getResolucionColor() / valorMaximo);
            int g = static_cast<int>(imagenHDR[i][j + 1] * imagen.getResolucionColor() / valorMaximo);
            int b = static_cast<int>(imagenHDR[i][j + 2] * imagen.getResolucionColor() / valorMaximo);
            archivo << r << " " << g << " " << b << " ";
        }
        archivo << endl;
    }
}
