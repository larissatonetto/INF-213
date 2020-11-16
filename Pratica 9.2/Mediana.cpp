#include "MyPriorityQueue.h"
#include "Mediana.h"
#include <iostream>

void Mediana::insere(int elem) {
    // filaMaior guarda elementos negativos para que filaMaior.top() seja o menor número
    if (filaMenor.size() == 0 && filaMaior.size() == 0) {
        filaMenor.push(elem);
    } else if (filaMenor.size() == 1 && filaMaior.size() == 0) {
        if (elem < filaMenor.top()) {
            filaMaior.push(-filaMenor.top());
            filaMenor.pop();
            filaMenor.push(elem);
        } else filaMaior.push(-elem);
    } else {
        if (elem <= getMediana()) filaMenor.push(elem);
        else filaMaior.push(-elem);
    }

    if (filaMenor.size() > (filaMaior.size()+1)) {
        filaMaior.push(-filaMenor.top());
        filaMenor.pop();
    } else if (filaMaior.size() > (filaMenor.size()+1)) {
        filaMenor.push(-filaMaior.top());
        filaMaior.pop();
    }
}

int Mediana::getMediana() {
    if (filaMenor.size() == filaMaior.size()) {
        return (filaMenor.top() + -filaMaior.top())/2;
    } else return (filaMenor.size() > filaMaior.size() ? filaMenor.top() : -filaMaior.top());
}