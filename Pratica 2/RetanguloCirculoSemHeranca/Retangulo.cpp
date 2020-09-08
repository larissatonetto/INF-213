
#include "Retangulo.h"
#include <iostream>
using std::cout;
using std::endl;

Retangulo::Retangulo(double x = 0, double y = 0, 
                     double larg = 0, double alt = 0,
                     int esp = 0, int c = 0, int t = 0): FigBase(x, y, esp, c, t) {
    setLargura(larg);
    setAltura(alt);
}

double Retangulo::getLargura() const {
    return largura;
}

void Retangulo::setLargura(double larg) {
    largura = larg;

}
double Retangulo::getAltura() const {
    return altura;
}

void Retangulo::setAltura(double alt) {
    altura = alt;
}

float Retangulo::area() const {
    return altura * largura;     
}      
          
float Retangulo::perimetro() const {
    return 2*(largura + altura);      
}

void Retangulo::imprime() const {
    cout << "--- [Retangulo] ---" << endl;
    FigBase::imprime();
    cout << " largura = " << getLargura() << " altura = " << getAltura() << endl;  
    cout << " area = " << area() << " perimetro = " << perimetro() << endl; 
}
