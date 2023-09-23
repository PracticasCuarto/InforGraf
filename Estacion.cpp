#include "Estacion.hpp"
#include <iostream>

using namespace std;

// Constructor de la Estacion
Estacion::Estacion(Esfera _planeta, double _inclinacion, double _azimut) : planeta(_planeta), inclinacion(_inclinacion), azimut(_azimut), posicion(0, 0, 0), normal(0, 0, 0), tangenteLongitud(0, 0, 0), tangenteLatitud(0, 0, 0) {
    // Calcula la posición de la estación en el Sistema de Coordenadas del Universo (UCS)
    posicion = planeta.getCentro() + Direccion(cos(inclinacion) * cos(azimut), cos(inclinacion) * sin(azimut), sin(inclinacion)) * planeta.getRadio();

    // Calcula la normal de la superficie del planeta en esa posición (su módulo es 1)
    normal = (posicion - planeta.getCentro()).normalizar();

    // Calcula la dirección tangente a la longitud, tangente a la superficie del planeta y perpendicular al eje del planeta y sigue la variación positiva del azimut (sin variación de la inclinación)
    tangenteLongitud = Direccion(-sin(azimut), cos(azimut), 0);

    // Calcula la dirección tangente a la latitud, tangente a la superficie del planeta y perpendicular al eje del planeta y sigue la variación positiva de la inclinación (sin variación del azimut)
    tangenteLatitud = Direccion(cos(inclinacion) * cos(azimut), cos(inclinacion) * sin(azimut), sin(inclinacion));
}

// Conexion con otra estación en otro planeta. Es importante que no atraviese la superficie de ninguno de los dos planetas
Direccion Estacion::conectar(Estacion otraEstacion) {
    // Calcula la dirección de la conexión
    Direccion direccion = otraEstacion.getPosicion() - posicion;

    // Comprobar que la direccion no atraviesa la superficie de ninguno del primer planeta
    if (direccion * normal < 0) {
        // Si la dirección atraviesa la superficie del primer planeta, se devuelve un vector nulo
        return Direccion(0, 0, 0);
    }

    // Calcula la dirección de la conexión
    direccion = otraEstacion.getPosicion() - puntoInterseccion;

    // Devuelve la dirección de la conexión
    return direccion;
}