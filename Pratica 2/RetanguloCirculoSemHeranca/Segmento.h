#ifndef SEGMENTO_H
#define SEGMENTO_H

#include <iostream>
#include "FigBase.h"
using std::ostream;
using std::istream;

class Segmento : public FigBase {
private:
    double x2, y2;
public:
    Segmento(double = 1, double = 1, double = 1, double = 1, int = 1, int = 1, int = 1);

    double getX2() const;
    void setX2(double);

    double getY2() const;
    void setY2(double);

    float area() const;

    float perimetro() const;

    void imprime() const;
    void le();

    // Leitura e escrita
    friend ostream& operator<<(ostream&, const Segmento&);
    friend istream& operator>>(istream&, Segmento&);
};

#endif