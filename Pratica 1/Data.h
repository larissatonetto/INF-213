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

    const int getDia() const;
    const int getMes() const;
    const int getAno() const;

    const int compData(const Data& dma) const;

    const int difDias(const Data& dma) const;

    const void imprime() const;

    // Leitura e escrita
    friend std::ostream& operator<<(std::ostream& os, const Data& dt);
    friend std::istream& operator>>(std::istream& is, Data& dt);
};

#endif