#ifndef AGENDA_H
#define AGENDA_H

#include <string>

#include "Data.h"
#include "Horario.h"

class ItemAgenda {
private:
    std::string descricao;
    Data d;
    Horario h;

public:
    ItemAgenda();
    ItemAgenda(const std::string& desc, const Data &dt, const Horario &hr);
    ItemAgenda(const ItemAgenda &it);

    void setDesc(const std::string& desc);
    void setData(const Data& dt);
    void setHorario(const Horario& hr);

    const std::string & getDesc() const;
    const Data & getData() const;
    const Horario & getHorario() const;
};

class Agenda {
private:
    ItemAgenda itens[1000];
    static int cont;
    
public:
    Agenda();
    void inserirItem(const ItemAgenda &it);
    const void compromissosData(const Data &d) const;
};

#endif