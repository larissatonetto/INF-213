
#include "Retangulo.h"
#include <iostream>
using std::cout;
using std::cin;
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

void Retangulo::le() {
    // Ordem de leitura: x -> y -> espessura -> cor -> tipo
    // -> largura -> altura
    double tempLarg, tempAlt;

    FigBase::le();
    cin >> tempLarg >> tempAlt;
    setLargura(tempLarg);
    setAltura(tempAlt);
}

ostream& operator<<(ostream& os, const Retangulo& rt) {
    rt.imprime();

    return os;
}

istream& operator>>(istream& is, Retangulo& rt) {
    rt.le();

    return is;
}