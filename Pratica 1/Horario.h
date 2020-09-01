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

    int getHora() const;
    int getMinuto() const;
    int getSegundo() const;

    int compHorario(const Horario& hms) const;

    int difSegundos(const Horario& hms) const;

    void imprime() const;

    // Leitura e escrita
    friend std::ostream& operator<<(std::ostream& os, const Horario& hr);
    friend std::istream& operator>>(std::istream& is, Horario& hr);
};

#endif
