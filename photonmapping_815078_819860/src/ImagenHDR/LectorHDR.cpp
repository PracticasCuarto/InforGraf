#include "LectorHDR.hpp"
#include "ImagenHDR.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

LectorHDR::LectorHDR() {
    // Constructor por defecto, no necesitas hacer nada aquí.
}

ImagenHDR LectorHDR::leerImagenHDR(string nombreArchivo) {
    vector<vector<double>> imagenHDR;
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return ImagenHDR(imagenHDR, 0, 0, 0, 0);
    }

    string linea;
    int ancho = 0, alto = 0;
    double valorMaximo = 0, resolucionColor = 0;

    // Leer el encabezado del archivo PPM
    getline(archivo, linea); // Leer el identificador (P3)
    while (getline(archivo, linea)) {
        if (linea[0] != '#') {
            istringstream iss(linea);
            iss >> ancho >> alto;
            break;
        }
        else {
            // Si el comentario contiene "MAX=" seguido de un real, establecemos
            // el valor máximo de la imagen en ese valor.
            if (linea.find("MAX=") != string::npos) {
                istringstream iss(linea);
                string basura;
                iss >> basura >> valorMaximo;
            }
        }
    }
    getline(archivo, linea); // Leer el valor máximo
    istringstream iss(linea);
    iss >> resolucionColor;

    // Redimensionar el vector de vectores para que coincida con el tamaño de la imagen
    imagenHDR.resize(alto, vector<double>(ancho * 3));

    if (valorMaximo == 0) {
        // Leer los valores de píxeles y almacenarlos en el vector de vectores
        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho * 3; j += 3) {
                int r, g, b;
                archivo >> r >> g >> b;
                // Normalizar los valores de RGB y almacenarlos en el vector de vectores
                imagenHDR[i][j] = static_cast<double>(r) / resolucionColor;
                imagenHDR[i][j + 1] = static_cast<double>(g) / resolucionColor;
                imagenHDR[i][j + 2] = static_cast<double>(b) / resolucionColor;
            }
        }
    }
    else {
        // Leer los valores de píxeles y almacenarlos en el vector de vectores
        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho * 3; j += 3) {
                int r, g, b;
                archivo >> r >> g >> b;

                // Normalizar los valores de RGB y almacenarlos en el vector de vectores
                imagenHDR[i][j] = static_cast<double>(r) / resolucionColor * valorMaximo;
                imagenHDR[i][j + 1] = static_cast<double>(g) / resolucionColor * valorMaximo;
                imagenHDR[i][j + 2] = static_cast<double>(b) / resolucionColor * valorMaximo;
            }
        }
    }
    archivo.close();

    // Mostrar por pantalla la información de la imagen
    cout << "Imagen HDR cargada con éxito." << endl;
    // cout << "Ancho: " << ancho << endl;
    // cout << "Alto: " << alto << endl;
    // cout << "Valor máximo: " << valorMaximo << endl;
    // cout << "Resolución de color: " << resolucionColor << endl;

    ImagenHDR imagen(imagenHDR, ancho, alto, valorMaximo, resolucionColor);

    return imagen;
}
