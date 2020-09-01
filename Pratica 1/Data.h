#ifndef DATA_H
#define DATA_H

class Data {
private:
    int dia, mes, ano;

public:
    Data(int d = 1, int m = 1, int a = 2018);
    Data(const Data &dt);

    void setDia(int d);
    void setMes(int m);
    void setAno(int a);

    int getDia();
    int getMes();
    int getAno();

    int compData(const Data& dma);

    int difDias(const Data& dma);

    void imprime();
};

#endif