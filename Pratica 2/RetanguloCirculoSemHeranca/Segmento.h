#ifndef SEGMENTO_H
#define SEGMENTO_H

#include "FigBase.h"

class Segmento : public FigBase {
private:
    double x2, y2;
public:
    Segmento(double = 0, double = 0, double = 0, double = 0, int = 0, int = 0, int = 0);

    double getX2() const;
    void setX2(double);

    double getY2() const;
    void setY2(double);

    float area() const;

    float perimetro() const;

    void imprime() const;
};

#endif