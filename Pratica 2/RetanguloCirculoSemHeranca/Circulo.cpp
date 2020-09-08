
#include "Circulo.h"
#include <iostream>
using std::cout;
using std::endl;

const float PI = 3.141592653589;

Circulo::Circulo(double x = 0, double y = 0, double r = 0, 
                     int esp = 0, int c = 0, int t = 0): FigBase(x, y, esp, c, t) {
    setRaio(r);
}

double Circulo::getRaio() const {
    return raio;
}

void Circulo::setRaio(double r) {
    raio = r;
}

float Circulo::area() const {
    return PI * raio * raio;    
}      
          
float Circulo::perimetro() const {
    return 2 * PI * raio;      
}

void Circulo::imprime() const {
    cout << "--- [Circulo] ---" << endl;
    FigBase::imprime();
    cout << " raio = " << getRaio() << endl; 
    cout << " area = " << area() << " perimetro = " << perimetro() << endl; 
}
