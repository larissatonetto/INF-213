#ifndef Mediana_H
#define Mediana_H

#include "MyPriorityQueue.h"

class Mediana {
public:
    Mediana():size(0) {};
    ~Mediana() {};

    int getMediana();

    void insere(int elem);

private:
    MyPriorityQueue<int> filaMenor;
    MyPriorityQueue<int> filaMaior;
    int size;
};

#endif