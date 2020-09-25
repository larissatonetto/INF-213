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
    Conjunto(int = 10);         // Funcionando
    Conjunto(const Conjunto&);  // Funcionando
    ~Conjunto();                // Funcionando

    int getNum_elementos() const;
    int getTam_array() const;
    T* getElementos() const;
    

    bool pertence(T) const;     // Funcionando
    bool insere(T);             // Funcionando
    int numelementos();         // Funcionando

    bool operator== (const Conjunto &);         // Funcionando
    Conjunto& operator= (const Conjunto &);     // Funcionando

private:
    T* elementos;
    int num_elementos;
    int tam_array;
};

// Operadores -------------------------------------------------
template <class T>
ostream& operator<< (ostream &os, const Conjunto<T> &conj) {
    os << "{";

    if (conj.num_elementos == 0) {
        os << "}";
        return os;
    }

    for (int i = 0; i < conj.num_elementos-1; i++) {
        os << conj.elementos[i] << ",";
    }
    os << conj.elementos[conj.num_elementos-1] << "}";

   return os;
}

// TODO: Não deve permitir valores duplicados
template <class T>
istream& operator>> (istream &is, Conjunto<T> &conj) {
    T temp;
    while (is >> temp) {
        if (conj.num_elementos == conj.tam_array){      // Talvez mover para o while
           return is;
        } else {
            conj.insere(temp);
            /*if (conj.pertence(temp)) {      // TODO: EOF está chamando essa parte
               //continue;
            }
           
            else {
                conj.elementos[conj.num_elementos] = temp;

                conj.num_elementos++;
            }*/
        }
   }

    return is;
}

template <class T>
bool Conjunto<T>::operator== (const Conjunto& conj) {
    if (this->num_elementos != conj.num_elementos) { return false; }

    else if (this->num_elementos == 0 && conj.num_elementos == 0) { return true; }

    else {
        for (int i = 0; i < this->num_elementos; i++) {
            if (conj.elementos[i] != this->elementos[i])
                return false;
        }

        return true;
    }
}

template <class T>
Conjunto<T>& Conjunto<T>::operator= (const Conjunto<T> &conj) {
    if (&conj == this) { return *this; }

    else {
        delete[] elementos;
        elementos = new T[conj.tam_array];
        tam_array = conj.tam_array;
        num_elementos = conj.num_elementos;

        for (int i = 0; i < num_elementos; i++) {
            elementos[i] = conj.elementos[i];
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
Conjunto<T>::Conjunto(const Conjunto<T> &conj) {
    elementos = new T[conj.tam_array];
    tam_array = conj.tam_array;
    num_elementos = conj.num_elementos;

    for (int i = 0; i < num_elementos; i++) {
        elementos[i] = conj.elementos[i];
    }

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
    }
    
    if (num_elementos < tam_array) {
        elementos[num_elementos] = tipo;
        num_elementos++;

        return true;
    } else {
        return false;
    }
}

template <class T>
int Conjunto<T>::numelementos() {
    return num_elementos;
}

template <class T>
int Conjunto<T>::getTam_array() const {
    return tam_array;
}

template <class T>
int Conjunto<T>::getNum_elementos() const {
    return num_elementos;
}

template <class T>
T* Conjunto<T>::getElementos() const {
    return elementos;
}

#endif