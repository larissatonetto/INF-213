#ifndef CONJUNTO1_H
#define CONJUNTO1_H

#include <iostream>
using namespace std;

template <class T>
class Conjunto;

template <class T>
ostream& operator<< (ostream &, const Conjunto<T> &);

template <class T>
istream& operator>> (istream &is, Conjunto<T> &conj);

template <class T>
class Conjunto {
private:
    T* elementos;
    int num_elementos;
    int tam_array;

public:
    Conjunto(int = 10);         // Funcionando
    Conjunto(const Conjunto&);  // Funcionando
    ~Conjunto();                // Funcionando

    int getNum_elementos() const;
    int getTam_array() const;
    T getElementos() const;
    

    bool pertence(T) const;     // Funcionando
    bool insere(T);             // Funcionando
    int numelementos();         // Funcionando

    bool operator== (const Conjunto &);         // Funcionando
    Conjunto& operator= (const Conjunto &);  // Funcionando

    friend ostream& operator<< <>(ostream &, const Conjunto &);
    friend istream& operator>> <>(istream &, Conjunto &);

    void imprimeTamanho() const;
};

// Operadores -------------------------------------------------
template <class T>
ostream& operator<< (ostream &os, const Conjunto<T> &conj) {
    os << "{";
    for (int i = 0; i < conj.num_elementos-1; i++) {
        os << conj.elementos[i] << ",";
    }
    os << conj.elementos[conj.num_elementos-1] << "}";

   return os;
}

template <class T>
istream& operator>> (istream &is, Conjunto<T> &conj) {
   while (true) {
       // Verificar EOF...
       if (is.eof()) {
           cout << "EOF\n";
           return is;
       } else if (conj.num_elementos == conj.tam_array){
           return is;
       } else {
           /*is >> conj.elementos[conj.num_elementos];

           conj.num_elementos++;
           cout << "num_elementos = " << conj.num_elementos << endl;*/
       }
   }


    // for (int i = 0; i < conj.tam_array; i++) {
        // is >> conj.elementos[i];
    // }
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
            // TODO: insere()...
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
Conjunto<T>::Conjunto(const Conjunto<T>& conj) {
    tam_array = conj.tam_array;
    elementos = new T[tam_array];
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

// Getters (desnecessários?) ----------------------------------------------------
/*template <class T>
int Conjunto<T>::getNum_elementos() const{
     return num_elementos;
 }

template <class T>
int Conjunto<T>::getTam_array() const {
    return tam_array;
}

template <class T>
T Conjunto<T>::getElementos() const {
    return &elementos;
}*/

// ------------------------------------------------------------

template <class T>
bool Conjunto<T>::pertence(T placeholder) const {
    for (int i = 0; i < num_elementos; i++) {
        if (elementos[i] == placeholder) { cout << "Pertence\n"; return true; }
    }

    cout << "Não pertence\n";
    return false;
}

template <class T>
bool Conjunto<T>::insere(T placeholder){
    if (num_elementos < tam_array) {
        cout << "Elemento " << placeholder << " inserido\n";  // Retirar depois

        elementos[num_elementos] = placeholder;
        num_elementos++;
        return true;
    } else {
        cout << "Limite de elementos atingido\n";   // Retirar depois

        return false;
    }
}

template <class T>
int Conjunto<T>::numelementos() {
    return num_elementos;
}

// Funções de teste =======================================
template <class T>
void Conjunto<T>::imprimeTamanho() const{
    cout << "Tamanho do array: " << tam_array << " ";
    cout << "Numero de elementos: " << num_elementos << endl;
}

#endif

// TODO: Construtor de cópia deve chamar o operador de atribuição
// TODO: operadores << e >>