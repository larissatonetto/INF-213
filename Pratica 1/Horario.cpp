#include <iostream>

#include "Horario.h"

Horario::Horario(int h, int m, int s) {
    setHora(h);
    setMinuto(m);
    setSegundo(s);
}

Horario::Horario(const Horario &hr) {
    hora = hr.hora;
    minuto = hr.minuto;
    segundo = hr.segundo;
}

void Horario::setHora(int h) {
    if (h < 0) hora = 0;
    else if (h >= 24) hora = 23;
    else hora = h; 
}

void Horario::setMinuto(int m) {
    if (m < 0) minuto = 0;
    else if (m >= 60) minuto = 59;
    else minuto = m;
}

void Horario::setSegundo(int s) {
    if (s < 0) segundo = 0;
    else if (s >= 60) segundo = 59;
    else segundo = s;
}

int Horario::getHora() const {
    return hora;
}

int Horario::getMinuto() const {
    return minuto;
}

int Horario::getSegundo() const {
    return segundo;
}

int Horario::compHorario(const Horario& hms) const {
    if (hora == hms.hora) {
        if (minuto == hms.minuto) {
            if (segundo == hms.segundo) return 0;
            else return (segundo > hms.segundo) ? 1 : -1;
        }
        return (minuto > hms.minuto) ? 1 : -1;
    }
    return (hora > hms.hora) ? 1 : -1;
}

int Horario::difSegundos(const Horario& hms) const {
    if (compHorario(hms) == 0) return 0;

    // Converter o tempo em segundos
    int seg_h = segundo + minuto*60 + hora*3600;
    int segundos_hms = hms.segundo + hms.minuto*60 + hms.hora*3600;

    if (compHorario(hms) > 0) return seg_h - segundos_hms;
    else return segundos_hms - seg_h;
}

void Horario::imprime() const {
    std::cout << hora << " " << minuto << " " << segundo << "\n";
}

std::ostream& operator<<(std::ostream& os, const Horario& hr) {
    os << hr.hora << " " << hr.minuto << " " << hr.segundo;

    return os;
}

std::istream& operator>>(std::istream& is, Horario& hr) {
    is >> hr.hora >> hr.minuto >> hr.segundo;

    // Tratamendo da entrada, caso haja algum valor inválido
    hr.setHora(hr.hora);
    hr.setMinuto(hr.minuto);
    hr.setSegundo(hr.segundo);

    return is;
}