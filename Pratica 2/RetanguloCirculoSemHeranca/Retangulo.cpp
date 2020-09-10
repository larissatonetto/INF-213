
#include "Retangulo.h"
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

Retangulo::Retangulo(double x, double y, 
                     double larg, double alt,
                     int esp, int c, int t)
                     : FigBase(x, y, esp, c, t) {
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

ostream& operator<<(ostream& os, const Retangulo& rt) {
    /*os << "--- [Retangulo] ---" << endl;
    rt.FigBase::imprime();
    os << " largura = " << rt.getLargura() << " altura = " << rt.getAltura() << endl;  
    os << " area = " << rt.area() << " perimetro = " << rt.perimetro() << endl;*/
    rt.imprime();

    return os;
}

istream& operator>>(istream& is, Retangulo& rt) {
    double xTemp, yTemp, largTemp, altTemp;
    int espTemp, cTemp, tTemp;

    is >> xTemp >> yTemp >> largTemp >> altTemp >> espTemp >> cTemp >> tTemp;
    rt.setX(xTemp);
    rt.setY(yTemp);
    rt.setLargura(largTemp);
    rt.setAltura(altTemp);
    rt.setEspessura(espTemp);
    rt.setCor(cTemp);
    rt.setTipo(tTemp);

    return is;
}