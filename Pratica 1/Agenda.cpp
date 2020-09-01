#include <iostream>

#include "Agenda.h"
#include "Data.h"
#include "Horario.h"

// ItemAgenda
ItemAgenda::ItemAgenda() {};

ItemAgenda::ItemAgenda(const std::string& desc, const Data &dt, const Horario &hr) {
    descricao = desc;
    d = dt;
    h = hr;
}

ItemAgenda::ItemAgenda(const ItemAgenda &it) {
    descricao = it.descricao;
    d = it.d;
    h = it.h;
}

void ItemAgenda::setDesc(const std::string& desc) {
    descricao = desc;
}

void ItemAgenda::setData(const Data& dt) {
    d = dt;
}

void ItemAgenda::setHorario(const Horario& hr) {
    h = hr;
}

const std::string & ItemAgenda::getDesc() const {
    return descricao;
}

const Data & ItemAgenda::getData() const {
    return d;
}

const Horario & ItemAgenda::getHorario() const {
    return h;
}

// Agenda
Agenda::Agenda() {
}

void Agenda::inserirItem(const ItemAgenda &it) {
    cont++;
    itens[cont] = it;
}

const void Agenda::compromissosData(const Data &d) const {
    for (int i = 1; i <= cont; i++) {
        if (d.difDias(itens[i].getData()) == 0) {
            std::cout << itens[i].getHorario() << " " << itens[i].getDesc() << std::endl;
        }
    }
}

int Agenda::cont = 0;