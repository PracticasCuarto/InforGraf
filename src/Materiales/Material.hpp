#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>
#include "../Color.hpp"
#include "../Punto.hpp"
#include "../Direccion.hpp"
#include "../RandomNumber.hpp"

using namespace std;

enum TipoMaterial {
    NADA,
    DIFUSO_PURO,
    DIELECTRICO,
    PLASTICO
};

enum Componentes {
    DIFUSO,
    ESPECULAR,
    REFRACCION,
    ABSORCION
};

// Clase que almacena los colores de un material
class Material {
protected:
    Color difuso;
    Color especular;
    Color refraccion;
    Color coeficienteEmision;

public:

    double pDifuso, pEspecular, pRefraccion;
    TipoMaterial tipo;

    // Constructor completo
    Material();

    // Constructor con colores
    Material(Color _difuso, Color _especular, Color _reflectante, Color coeficienteEmision);

    // Getters del color
    Color getDifuso() const;
    Color getEspecular() const;
    Color getRefraccion() const;

    // Setters del color
    void setDifuso(Color _difuso);
    void setEspecular(Color _especular);
    void setRefraccion(Color _refraccion);

    // Ruleta rusa para decidir que componente hay que calcular
    Componentes ruletaRusa() const;
};




#endif