#include "MyPriorityQueue2.h"
#include "Mediana.h"
#include <iostream>

void Mediana::insere(int elem) {
    if (filaMenor.size() == 0 && filaMaior.size() == 0) {
        // Coloca no menor e balanceia (move o maior para o outro heap)
        filaMenor.push(elem);
    } else {
        if (filaMenor.size() == filaMaior.size()) {
            filaMenor.push(elem);
        } else filaMaior.push(elem);
    }
}

int Mediana::getMediana() {
    if (filaMenor.size() == filaMaior.size()) {
        return (filaMenor.top() + filaMaior.top())/2;
    } else return filaMenor.top();
}