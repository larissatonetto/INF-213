#ifndef CONJUNTO1_H
#define CONJUNTO1_H

#include <iostream>
using namespace std;

template <class T>
class Conjunto;

template <class T>
ostream& operator<< (ostream &, const Conjunto<T> &);

template <class T>
istream& operator>> (istream &, Conjunto<T> &);

template <class T>
class Conjunto {

friend ostream& operator<< <>(ostream &, const Conjunto &);
friend istream& operator>> <>(istream &, Conjunto &);

public:
    Conjunto(int = 10);
    Conjunto(const Conjunto&);
    ~Conjunto();

    bool pertence(T) const;
    bool insere(T);
    int numelementos() const;

    bool operator== (const Conjunto &);
    Conjunto& operator= (const Conjunto &);

private:
    T* elementos;
    int num_elementos;
    int tam_array;
};

// Operadores -------------------------------------------------
template <class T>
ostream& operator<< (ostream &os, const Conjunto<T> &other) {
    os << "{";

    if (other.num_elementos == 0) {
        os << "}";
        return os;
    }

    for (int i = 0; i < other.num_elementos-1; i++) {
        os << other.elementos[i] << ",";
    }
    os << other.elementos[other.num_elementos-1] << "}";

   return os;
}

template <class T>
istream& operator>> (istream &is, Conjunto<T> &other) {
    T temp;
    while (is >> temp) {
        if (other.num_elementos >= other.tam_array) {
           return is;
        } else {
            other.insere(temp);
        }
   }

    return is;
}

template <class T>
bool Conjunto<T>::operator== (const Conjunto& other) {
    if (this->num_elementos != other.num_elementos) { return false; }

    else if (this->num_elementos == 0 && other.num_elementos == 0) { return true; }

    else {
        for (int i = 0; i < this->num_elementos; i++) {
            if (!other.pertence( this->elementos[i] )) { return false; }
        }

        return true;
    }
}

template <class T>
Conjunto<T>& Conjunto<T>::operator= (const Conjunto<T> &other) {
    if (&other == this) { return *this; }

    else {
        delete[] elementos;
        elementos = new T[other.tam_array];
        tam_array = other.tam_array;
        num_elementos = other.num_elementos;

        for (int i = 0; i < num_elementos; i++) {
            elementos[i] = other.elementos[i];
        }
    }
}
// ------------------------------------------------------------

// Construtores e destrutor -----------------------------------
template <class T>
Conjunto<T>::Conjunto(int n) {
    tam_array = n;
    elementos = new T[tam_array];
    num_elementos = 0;
}

template <class T>
Conjunto<T>::Conjunto(const Conjunto<T> &other) {
    elementos = NULL;
    (*this) = other;
}

template <class T>
Conjunto<T>::~Conjunto() {
    delete[] elementos;
}

// ------------------------------------------------------------

template <class T>
bool Conjunto<T>::pertence(T tipo) const {
    for (int i = 0; i < num_elementos; i++) {
        if (elementos[i] == tipo) { return true; }
    }

    return false;
}

template <class T>
bool Conjunto<T>::insere(T tipo){
    if (pertence(tipo)) {
        return false;
    } else if (num_elementos < tam_array) {
        elementos[num_elementos] = tipo;
        num_elementos++;

        return true;
    } else {
        return false;
    }
}

template <class T>
int Conjunto<T>::numelementos() const {
    return num_elementos;
}

#endif