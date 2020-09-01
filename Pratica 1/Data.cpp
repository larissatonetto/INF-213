#include <iostream>

#include "Data.h"

Data::Data(int d, int m, int a) {
    setDia(d);
    setMes(m);
    setAno(a);
}

Data::Data(const Data &dt) {
    dia = dt.dia;
    mes = dt.mes;
    ano = dt.ano;
}

void Data::setDia(int d) {
    if (d < 1) dia = 1;
    else if (d > 30) dia = 30;
    else dia = d;
}

void Data::setMes(int m) {
    if (m < 1) mes = 1;
    else if (m > 12) mes = 12;
    else mes = m;
}

void Data::setAno(int a) {
    if (a < 2018) ano = 2018;
    else if (a > 2020) ano = 2020;
    else ano = a;
}

int Data::getDia() {
    return dia;
}

int Data::getMes() {
    return mes;
}

int Data::getAno() {
    return ano;
}

int Data::compData(const Data& dma) {
    if (ano == dma.ano) {
        if (mes == dma.mes) {
            if (dia == dma.dia) return 0;
            else return (dia > dma.dia) ? 1 : -1;
        }
        return (mes > dma.mes) ? 1 : -1;
    }
    return (ano > dma.ano) ? 1 : -1;
}

int Data::difDias(const Data& dma) {
    if (compData(dma) == 0) return 0;

    int dias_d = dia + mes*30 + ano*365;
    int dias_dma = dma.dia + dma.mes*30 + dma.ano*365;
    
    if (compData(dma) > 0) return dias_d - dias_dma;
    else return dias_dma - dias_d;
}

void Data::imprime() {
    std::cout << dia << " " << mes << " " << ano << "\n";
}