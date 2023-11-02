#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>
using namespace std;


class Color {
public:
    double r;
    double g;
    double b;

    // Constructor completo
    Color(double _r, double _g, double _b);

    // Operadores
    Color operator+(const Color& color) const;
    Color operator-(const Color& color) const;
    Color operator*(const Color& color) const;
    Color operator+(double escalar) const;
    Color operator-(double escalar) const;
    Color operator*(double escalar) const;
    Color operator/(double escalar) const;

    Color operator+=(const Color& color);
    Color operator-=(const Color& color);
    Color operator*=(const Color& color);
    Color operator+=(double escalar);
    Color operator-=(double escalar);
    Color operator*=(double escalar);
    Color operator/=(double escalar);
};

#endif