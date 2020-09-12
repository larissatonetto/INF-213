#include <iostream>
#include "FigBase.h"
using std::cin;
using std::cout;
using std::endl;

FigBase::FigBase(double x, double y, int esp, int c, int t) {
    setX(x);
    setY(y);
    setEspessura(esp);
    setCor(c);
    setTipo(t);
}

double FigBase::getX() const {
    return x;
}

void FigBase::setX(double x) {
    this->x = x;
}

double FigBase::getY() const {
    return y;
}

void FigBase::setY(double y) {
    this->y = y;
}

int FigBase::getEspessura() const {
    return espessura;
}

void FigBase::setEspessura(int esp) {
    espessura = (esp < 1 || esp > 5) ? 1 : esp;
}

int FigBase::getCor() const {
    return cor;
}

void FigBase::setCor(int c) {
    cor = (c < 1 || c > 5) ? 1 : c;
}

int FigBase::getTipo() const {
    return tipo;
}

void FigBase::setTipo(int t) {
    tipo = (t < 1 || t > 3) ? 1 : t;
}

void FigBase::imprime() const {
    cout << " Atributos da linha: " << endl;
    cout << "     Espessura = " << getEspessura() << endl;
    cout << "     Cor       = " << getCor() << endl;
    cout << "     Tipo      = " << getTipo() << endl;          
    cout << " x = " << getX() << " y = " << getY() << endl;
}

void FigBase:: le() {
    // Ordem de leitura: x -> y -> espessura -> cor -> tipo
    double tempX, tempY;
    int tempEsp, tempC, tempT;

    cin >> tempX >> tempY >> tempEsp >> tempC >> tempT;
    setX(tempX);
    setY(tempY);
    setEspessura(tempEsp);
    setCor(tempC);
    setTipo(tempT);
}