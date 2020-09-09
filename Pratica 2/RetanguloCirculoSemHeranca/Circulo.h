
#ifndef __Circulo_h
#define __Circulo_h

#include "FigBase.h"

class Circulo : public FigBase {
private:
    double raio;

public:
    Circulo(double = 0, double = 0, double = 0, int = 0, int = 0, int = 0);

    double getRaio() const;
    void setRaio(double);

    float area() const;
    float perimetro() const;

    void imprime() const;

};

#endif
