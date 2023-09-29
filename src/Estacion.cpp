#include "Estacion.hpp"
#include <iostream>

using namespace std;

// Constructor de la Estacion
Estacion::Estacion(Esfera _planeta, double _inclinacion, double _azimut) : planeta(_planeta), inclinacion(_inclinacion), azimut(_azimut), posicion(0, 0, 0), normal(0, 0, 0), tangenteLongitud(0, 0, 0), tangenteLatitud(0, 0, 0) {
    // Calcula la posición de la estación en el Sistema de Coordenadas del Universo (UCS)
    posicion = planeta.getCentro() + Direccion(cos(inclinacion) * cos(azimut), cos(inclinacion) * sin(azimut), sin(inclinacion)) * planeta.getRadio();

    // Calcula la normal de la superficie del planeta en esa posición (su módulo es 1)
    normal = (posicion - planeta.getCentro()).normalizar();

    // Producto vectorial del eje por la normal
    tangenteLongitud = Direccion(0, 0, 1).cross(normal);

    // Calcula la dirección tangente a la latitud, tangente a la superficie del planeta y perpendicular al eje del planeta y sigue la variación positiva de la inclinación (sin variación del azimut)
    // Producto vectorial tangente longitud y normal
    tangenteLatitud = tangenteLongitud.cross(normal);
}

// Conexion con otra estación en otro planeta. Es importante que no atraviese la superficie de ninguno de los dos planetas
Direccion Estacion::conectar(Estacion otraEstacion) {
    // Calcula la dirección de la conexión
    Direccion direccion = otraEstacion.getPosicion() - posicion;

    // Cambiar la base de la direccion a la base local del planeta
    Matriz baseLocal = Matriz(normal.x, tangenteLongitud.x, tangenteLatitud.x, posicion.x,
        normal.y, tangenteLongitud.y, tangenteLatitud.y, posicion.y,
        normal.z, tangenteLongitud.z, tangenteLatitud.z, posicion.z,
        0, 0, 0, 1);
    Direccion direccionLocal = direccion.cambioBase(baseLocal);

    // Si el angulo es > 90º, y el cohete sale de ese planeta, hay colision
    if (normal.angulo(direccionLocal) > 90 && normal.angulo(direccionLocal) < 270) {
        cout << "Angulo de la normal -->> " << normal.angulo(direccionLocal);
        cout << "Hay ¡¡¡COLISION!!!" << endl;
        return Direccion(0, 0, 0);
    }

    // Cambiar la base de la direccion a la base local del planeta
    Matriz baseVisitante = Matriz(otraEstacion.normal.x, otraEstacion.tangenteLongitud.x, otraEstacion.tangenteLatitud.x, otraEstacion.posicion.y,
        otraEstacion.normal.y, otraEstacion.tangenteLongitud.y, otraEstacion.tangenteLatitud.y, otraEstacion.posicion.y,
        otraEstacion.normal.z, otraEstacion.tangenteLongitud.z, otraEstacion.tangenteLatitud.z, otraEstacion.posicion.z,
        0, 0, 0, 1);
    Direccion direccionVisitante = direccion.cambioBase(baseLocal);

    // Si el ángulo es < 180º, y el cohete entra en ese planeta, hay colision
    if (otraEstacion.normal.angulo(direccionVisitante) < 180) {
        cout << "Angulo de la otra estacion -->> " << otraEstacion.normal.angulo(direccionVisitante);
        cout << "Hay ¡¡¡COLISION!!!";
        return Direccion(0, 0, 0);
    }

    // Devuelve la dirección de la conexión
    return direccion;
}