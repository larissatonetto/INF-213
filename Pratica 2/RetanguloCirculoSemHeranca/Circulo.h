
#ifndef __Circulo_h
#define __Circulo_h

#include <iostream>
#include "FigBase.h"
using std::ostream;
using std::istream;

class Circulo : public FigBase {
private:
    double raio;

public:
    Circulo(double = 1, double = 1, double = 1, int = 1, int = 1, int = 1);

    double getRaio() const;
    void setRaio(double);

    float area() const;
    float perimetro() const;

    void imprime() const;
    void le();

    // Leitura e escrita
    friend ostream& operator<<(ostream&, const Circulo&);
    friend istream& operator>>(istream&, Circulo&);
};

#endif
