
#ifndef __Retangulo_h
#define __Retangulo_h

#include <iostream>
#include "FigBase.h"
using std::ostream;
using std::istream;

class Retangulo : public FigBase {
private:
    double largura, altura;

public:
    Retangulo(double = 1, double = 1, double = 1, double = 1, int = 1, int = 1, int = 1);

    double getLargura() const;
    void setLargura(double);

    double getAltura() const;
    void setAltura(double);

    float area() const;
    float perimetro() const;

    void imprime() const;
    void le();

    // Leitura e escrita
    friend ostream& operator<<(ostream&, const Retangulo&);
    friend istream& operator>>(istream&, Retangulo&);
};

#endif
