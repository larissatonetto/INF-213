
#include "Circulo.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

const float PI = 3.141592653589;

Circulo::Circulo(double x, double y, double r, 
                 int esp, int c, int t)
                 : FigBase(x, y, esp, c, t) {
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

void Circulo::le() {
    // Ordem de leitura: x -> y -> espessura -> cor -> tipo
    // -> raio
    double tempR;

    FigBase::le();
    cin >> tempR;
    setRaio(tempR);
}

ostream& operator<<(ostream& os, const Circulo& cl) {
    cl.imprime();

    return os;
}

istream& operator>>(istream& is, Circulo& cl) {
    cl.le();

    return is;
}