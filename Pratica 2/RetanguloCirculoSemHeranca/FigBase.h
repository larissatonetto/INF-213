#ifndef FIGBASE_H
#define FIGBASE_H

class FigBase {
private:
    double x, y;
    int espessura, cor, tipo;

public:
    FigBase(double = 1, double = 1, int = 1, int = 1, int = 1);

    double getX() const;
    void setX(double);

    double getY() const;
    void setY(double);

    int getEspessura() const;
    void setEspessura(int);

    int getCor() const;
    void setCor(int);

    int getTipo() const;
    void setTipo(int);

    void imprime() const;
    void le();
};

#endif