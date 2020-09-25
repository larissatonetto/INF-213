#ifndef CONJUNTO2_H
#define CONJUNTO2_H

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
    Conjunto operator+ (const Conjunto &) const;
    Conjunto operator* (const Conjunto &) const;
    Conjunto operator- (const Conjunto &) const;

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
    } else {
        for (int i = 0; i < conj.num_elementos-1; i++) {
            os << conj.elementos[i] << ",";
        }
        os << conj.elementos[conj.num_elementos-1] << "}";
    }

   return os;
}

// TODO: Não deve permitir valores duplicados
// Erro pode ser aqui
template <class T>
istream& operator>> (istream &is, Conjunto<T> &conj) {
    T temp;
    while (is >> temp) {
        if (conj.num_elementos == conj.tam_array){      // Talvez mover para o while
           return is;
        } else {
            if (conj.pertence(temp)) {
               //continue;
            }
           
            else {
                conj.elementos[conj.num_elementos] = temp;

                conj.num_elementos++;
            }
        }
   }

    return is;
}

template <class T>
bool Conjunto<T>::operator== (const Conjunto& conj) {
    if (num_elementos != conj.num_elementos) { return false; }

    else {
        for (int i = 0; i < num_elementos; i++) {
            if (conj.elementos[i] != elementos[i])
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

template <class T>
Conjunto<T> Conjunto<T>::operator+ (const Conjunto<T> &other) const {
    int tam = other.tam_array + this->tam_array;
    Conjunto<T> uniao(tam);

    for (int i = 0; i < this->num_elementos; i++) { uniao.insere(this->elementos[i]); }
    for (int i = 0; i < other.num_elementos; i++) { uniao.insere(other.elementos[i]); }

    return uniao;
}

template <class T>
Conjunto<T> Conjunto<T>::operator* (const Conjunto<T> &other) const {
    int tam = (other.tam_array > this->tam_array) ? this->tam_array : other.tam_array;
    Conjunto<T> inter(tam);

    // Gambiarra
    while (true) {
        /*if (other.num_elementos <= this->num_elementos) {   // Trocar os dois
            for (int i = 0; i < other.num_elementos; i++) {
                if (this->pertence( other.elementos[i] )) { inter.insere(other.elementos[i]); }
            }

            return inter;
        } else {*/

            // Parte comentada, caso resolva deve ser apagada
            for (int i = 0; i < this->num_elementos; i++) {
                if (other.pertence( this->elementos[i] )) { inter.insere(this->elementos[i]); }
            }

            return inter;
        // }
    }

    return inter;
}

template <class T>
Conjunto<T> Conjunto<T>::operator- (const Conjunto<T> &other) const {
    Conjunto<T> dif(this->tam_array);

    for (int i = 0; i < this->num_elementos; i++) {
        if (!other.pertence( this->elementos[i] )) { dif.insere(this->elementos[i]); }
    }

    return dif;
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
        // cout << "Elemento " << tipo << " adicionado\n";
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