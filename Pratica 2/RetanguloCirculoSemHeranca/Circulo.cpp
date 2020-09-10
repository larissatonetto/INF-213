
#include "Circulo.h"
#include <iostream>
using std::cout;
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

ostream& operator<<(ostream& os, const Circulo& cl) {
    /*os << "--- [Circulo] ---" << endl;
    cl.FigBase::imprime();
    os << " raio = " << cl.getRaio() << endl;
    os << " area = " << cl.area() << " perimetro = " << cl.perimetro() << endl;*/
    cl.imprime();

    return os;
}

istream& operator>>(istream& is, Circulo& cl) {
    double xTemp, yTemp, rTemp;
    int espTemp, cTemp, tTemp;

    is >> xTemp >> yTemp >>rTemp >> espTemp >> cTemp >> tTemp;
    cl.setX(xTemp);
    cl.setY(yTemp);
    cl.setRaio(rTemp);
    cl.setEspessura(espTemp);
    cl.setCor(cTemp);
    cl.setTipo(tTemp);

    return is;
}