#include "Color.hpp"

// Constructor completo
Color::Color(double _r, double _g, double _b) {
    r = _r;
    g = _g;
    b = _b;
}

// Operadores
Color Color::operator+(const Color& color) const {
    return Color(r + color.r, g + color.g, b + color.b);
}

Color Color::operator-(const Color& color) const {
    return Color(r - color.r, g - color.g, b - color.b);
}

Color Color::operator*(const Color& color) const {
    return Color(r * color.r, g * color.g, b * color.b);
}

Color Color::operator+(double escalar) const {
    return Color(r + escalar, g + escalar, b + escalar);
}

Color Color::operator-(double escalar) const {
    return Color(r - escalar, g - escalar, b - escalar);
}

Color Color::operator*(double escalar) const {
    return Color(r * escalar, g * escalar, b * escalar);
}

Color Color::operator/(double escalar) const {
    return Color(r / escalar, g / escalar, b / escalar);
}

Color Color::operator+=(const Color& color) {
    r += color.r;
    g += color.g;
    b += color.b;
    return *this;
}

Color Color::operator-=(const Color& color) {
    r -= color.r;
    g -= color.g;
    b -= color.b;
    return *this;
}

Color Color::operator*=(const Color& color) {
    r *= color.r;
    g *= color.g;
    b *= color.b;
    return *this;
}

Color Color::operator+=(double escalar) {
    r += escalar;
    g += escalar;
    b += escalar;
    return *this;
}

Color Color::operator-=(double escalar) {
    r -= escalar;
    g -= escalar;
    b -= escalar;
    return *this;
}

Color Color::operator*=(double escalar) {
    r *= escalar;
    g *= escalar;
    b *= escalar;
    return *this;
}

Color Color::operator/=(double escalar) {
    r /= escalar;
    g /= escalar;
    b /= escalar;
    return *this;
}

