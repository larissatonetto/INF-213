#include <iostream>
using namespace std;

template <class T>
class MyMatrix {
public:
MyMatrix(int, int *, bool);
MyMatrix(const MyMatrix&);
~MyMatrix();

const T& get(int, int);
int getNumRows();               // OK
int getNumElems();              // OK
int getNumCols(int);            // OK
void set(int, int, const T&);   // OK

T resizeRow();

bool isRagged();                // OK

void convertToRagged();
void convertToTraditional();

void print();

protected:
// Start é int pois guarda a posição em que cada linha começa
int rows, size, *tam, *start;
T *ragged, **matriz;
};

// Construtores -------------------------------------------------------------------
template <class T>
MyMatrix<T>::MyMatrix(int rows, int *arr, bool isRagged) {
    this->rows = rows;

    if (isRagged) {
        // O array start é maior do que o número de linhas
        // O tamanho do array ragged é igual ao último elemento de start
        tam = NULL;
        matriz = NULL;
        start = arr;

        // Explicar isso
        ragged = new T[(start[rows])];
    } else {
        start = NULL;
        ragged = NULL;
        tam = arr;

        matriz = new T*[rows];
        for (int i = 0; i < rows; i++) matriz[i] = new T[tam[i]];
    }
}

template<class T>
MyMatrix<T>::~MyMatrix() {
    if (isRagged()) {
        delete[] start;
        delete[] ragged;

    } else {
        for (int i = 0; i < rows; i++) delete[] matriz[i];
        delete[] matriz;
    }
}

// --------------------------------------------------------------------------------

// Get e set ----------------------------------------------------------------------
// O(1)
template <class T>
const T& MyMatrix<T>::get(int linha, int col) {
    if (isRagged()) {
        return ragged[(start[linha] + col)];

    } else {
        return matriz[linha][col];
    }
}

template <class T>
int MyMatrix<T>::getNumRows() { return rows; }

template <class T>
int MyMatrix<T>::getNumElems() {
    if (isRagged()) {
        return start[rows];
    } else {

        // TODO: Método O(1)
        int cont = 0;
        for (int i = 0; i < rows; i++) cont+= tam[i];
        return cont;
    }
}

// O(1)
template <class T>
int MyMatrix<T>::getNumCols(int linha) {
    if (isRagged()) {
        return (start[linha+1] - start[linha]);

    } else {
        return tam[linha];
    }
}

template <class T>
void MyMatrix<T>::set(int linha, int col, const T &elem) {
    if (isRagged()) {
        ragged[(start[linha] + col)] = elem;

    } else {
        matriz[linha][col] = elem;
    }
}

// --------------------------------------------------------------------------------

template <class T>
bool MyMatrix<T>::isRagged() {
    return (matriz == NULL);
}

template <class T>
void MyMatrix<T>::convertToRagged() {
    int cont = 0;
    // Passar diretamente para start ao invès de criar um array intermediário
    /*int tempStart[rows+1];
    tempStart[0] = 0;
    int cont = 0;

    // Convertendo o array tam para start
    for (int i = 1; i <= rows; i++) {
        cont+=tam[i-1];
        tempStart[i] = cont;
    }
    this->start = tempStart;*/


    start = new int[rows+1];
    start[0] = 0;
    for (int i = 1; i <= rows; i++) {
        cont+=tam[i-1];
        start[i] = cont;
    }

    ragged = new T[(start[rows])];

    // No convertToTraditional() utilizar um contador global para todos os elementos da matriz
    int i = 0;
    while(i != getNumElems()) {
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < tam[j]; k++) {
                ragged[i] = matriz[j][k];
                i++;
            }
        }
    }

    for (int i = 0; i < rows; i++) delete[] matriz[i];
        delete[] matriz;
    matriz = NULL;
    tam = NULL;
}

template <class T>
void MyMatrix<T>::print() {

    cout << "Rows: " << getNumRows() << "\n";
    cout << "Elems: " << getNumElems() << "\n";

    if (isRagged()) {
        // cout << "start[0] = " << start[0] << " start[1] = " << start[1] << "\n";
        
        for (int i = 0; i < rows; i++) {
            cout << (start[i+1]-start[i]) << ": ";
            for (int j = 0; j < start[i+1]-start[i]; j++) {
                // cout << "start[i] = " << start[i+1]-start[i] << "\n";
                cout << ragged[(start[i] + j)] << " ";
            }
            cout << "\n";
        }

    } else {

        for (int i = 0; i < rows; i++) {
            cout << tam[i] << ": ";
            for (int j = 0; j < tam[i]; j++) {
                cout << matriz[i][j] << " ";
            }
            cout << "\n";
        }
    }
}