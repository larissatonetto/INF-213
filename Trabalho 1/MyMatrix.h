#include <iostream>
using namespace std;

template <class T>
class MyMatrix {
public:
MyMatrix(int, int *, bool);
MyMatrix(const MyMatrix&);
~MyMatrix();

const T& get(int, int);
int getNumRows();
int getNumElems();
int getNumCols(int);
void set(int, int, const T&);

bool isRagged();

void resizeRow(int, int);
void resizeNumRols(int);
void convertToRagged();
void convertToTraditional();

void print();

private:
// Função auxiliar, recebe como argumento um bool indicando se
// a matriz é ragged ou não
void destroy(bool);

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

        // Consertar implementação; deve ser feita uam conversão de arr para start
        int cont = 0;
        start = new int[rows+1];
        start[0] = 0;
        for (int i = 1; i <= rows; i++) { 
            cont+= arr[i-1];
            start[i] = cont;
        }

        for (int i = 0; i <= rows; i++) cout << start[i] << " ";
        cout << endl;

        // Explicar isso
        ragged = new T[(start[rows])];
    } else {
        start = NULL;
        ragged = NULL;

        // Inicializando tam...
        tam = new int[rows];
        for (int i = 0; i < rows; i++) tam[i] = arr[i];

        // Inicializando matriz...
        matriz = new T*[rows];
        for (int i = 0; i < rows; i++) matriz[i] = new T[tam[i]];
    }
}

template<class T>
MyMatrix<T>::~MyMatrix() {
    destroy(isRagged());
}

// --------------------------------------------------------------------------------

template <class T>
void MyMatrix<T>::destroy(bool isRagged) {
    if (isRagged) {
        delete[] start;
        delete[] ragged;

    } else {
        for (int i = 0; i < rows; i++) delete[] matriz[i];
        delete[] matriz;
        delete[] tam;
    }
}

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

template <class T>
void MyMatrix<T>::resizeRow(int linha, int newCols) {
    T temp[getNumCols(linha)];
    int tempCols = getNumCols(linha);
    for (int i = 0; i < getNumCols(linha); i++) temp[i] = get(linha,i);
    
    if (isRagged()) {
        T tempRagged[start[rows]];
        int tempStart[rows+1];

        for (int i = 0; i < start[rows]; i++) tempRagged[i] = ragged[i];
        for (int i = 0; i <= rows; i++) tempStart[i] = start[i];

        // Todos os elementos de start a partir da linha serão aumentados em newCols
        for (int i = linha; i <= rows; i++) start[i]+= newCols;

        for (int i = 0; i <= rows; i++) cout << tempStart[i] << " ";
        cout << endl;
        for (int i = 0; i <= rows; i++) cout << start[i] << " ";
        cout << endl;
        // delete[] ragged;
        
    } else {
        delete[] matriz[linha];
        matriz[linha] = new T[newCols];
        tam[linha] = newCols;

        // Inicializa os elementos padrão primeiro, depois copia os elementos
        // já existentes de volta para a matriz
        for (int i = 0; i < getNumCols(linha); i++) matriz[linha][i] = T();
        for (int i = 0; i < tempCols; i++) matriz[linha][i] = temp[i];
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

    start = new int[rows+1];
    start[0] = 0;
    for (int i = 1; i <= rows; i++) {
        cont+= tam[i-1];
        start[i] = cont;
    }

    ragged = new T[(start[rows])];

    // No convertToTraditional() utilizar um contador global para todos os elementos da matriz
    int i = 0;
    while(i != getNumElems()) {
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < getNumCols(j); k++) {
                ragged[i] = matriz[j][k];
                i++;
            }
        }
    }
    destroy(false);
    matriz = NULL;
    tam = NULL;
}

template <class T>
void MyMatrix<T>::convertToTraditional() {
    int cont = 0;

    // Inicializando tam...
    tam = new int[rows];
    for (int i = 0; i < rows; i++) {
        tam[i] = getNumCols(i);
    }

    // Inicializando matriz...
    matriz = new T*[start[rows]];
    for (int i = 0; i < rows; i++) matriz[i] = new T[tam[i]];

    while(cont != getNumElems()) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < getNumCols(i); j++) {
                matriz[i][j] = ragged[cont];
                cont++;
            }
        }
    }

    destroy(true);
    start = NULL;
    ragged = NULL;
    
}

template <class T>
void MyMatrix<T>::print() {

    cout << "Rows: " << getNumRows() << "\n";
    cout << "Elems: " << getNumElems() << "\n";

    if (isRagged()) {
        
        for (int i = 0; i < rows; i++) {
            cout << getNumCols(i) << ": ";
            for (int j = 0; j < getNumCols(i); j++) {
                cout << get(i,j) << " ";
            }
            cout << "\n";
        }

    } else {

        for (int i = 0; i < rows; i++) {
            cout << tam[i] << ": ";
            for (int j = 0; j < tam[i]; j++) {
                cout << get(i,j) << " ";
            }
            cout << "\n";
        }
    }
}