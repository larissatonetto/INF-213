#include <iostream>
#include <math.h>
#include "Segmento.h"
using std::cout;
using std::endl;

Segmento::Segmento(double x, double y, double x2,
                   double y2, int esp, int c, int t)
                   : FigBase(x, y, esp, c, t) {
    setX2(x2);
    setY2(y2);
}

double Segmento::getX2() const {
    return x2;
}

void Segmento::setX2(double x2) {
    this->x2 = x2;
}

double Segmento::getY2() const {
    return y2;
}

void Segmento::setY2(double y2) {
    this->y2 = y2;
}

float Segmento::area() const {
    return 0;
}

float Segmento::perimetro() const {
    // a^2 + b^2 = c^2
    return sqrt((pow(x2 - getX(), 2) + pow(y2 - getY(), 2)));
}

void Segmento::imprime() const {
    cout << "--- [Segmento] ---" << endl;
    FigBase::imprime();
    cout << " x2 = " << getX2() << " y2 = " << getY2() << endl;
    cout << " area = " << area() << " perimetro = " << perimetro() << endl;
}