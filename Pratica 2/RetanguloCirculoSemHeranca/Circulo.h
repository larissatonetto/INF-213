
#ifndef __Circulo_h
#define __Circulo_h

#include "FigBase.h"

class Circulo : public FigBase {
private:
    double raio;

public:
    Circulo(double, double, double, int, int, int);

    double getRaio() const;
    void setRaio(double);

    float area() const;
    float perimetro() const;

    void imprime() const;

};

#endif
