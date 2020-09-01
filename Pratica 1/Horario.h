#ifndef HORARIO_H
#define HORARIO_H
class Horario {
private:
    int hora, minuto, segundo;

public:
    Horario(int h = 0, int m = 0, int s = 0);
    Horario(const Horario &hr);

    void setHora(int h);
    void setMinuto(int m);
    void setSegundo(int s);

    int getHora();
    int getMinuto();
    int getSegundo();

    int compHorario(const Horario& hms);

    int difSegundos(const Horario& hms);

    void imprime();
};

#endif
