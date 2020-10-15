#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <iostream>
using namespace std;

template <class T>
class MyMatrix {

public:
MyMatrix(int, int *, bool);
MyMatrix(const MyMatrix&);
~MyMatrix();

const T& get(int, int) const;
int getNumRows() const;
int getNumElems() const;
int getNumCols(int) const;
void set(int, int, const T&);

bool isRagged() const ;

void resizeRow(int, int);
void resizeNumRows(int);
void convertToRagged();
void convertToTraditional();

void print() const;

MyMatrix &operator= (const MyMatrix&);

private:
// Função auxiliar, recebe como argumento um bool indicando se
// a matriz é ragged ou não
void destroy(bool);

protected:
int rows, size, *tam, *start;
T *ragged, **matriz;
};

// ---------------------------------------------------------------------------------------

template <class T>
MyMatrix<T>::MyMatrix(int numRows, int *arr, bool isRagged) : rows(numRows) {
    // this->rows = rows;

    if (isRagged) {
        // O array start é maior do que o número de linhas
        // O tamanho do array ragged é igual ao último elemento de start
        tam = NULL;
        matriz = NULL;

        int cont = 0;
        start = new int[rows+1];
        // start[0] sempre será 0, independente da matriz
        start[0] = 0;


        for (int i = 1; i <= rows; i++) { 
            cont+= arr[i-1];
            start[i] = cont;
        }

        // O número de elementos é igual ao elemento guardado na última
        // posição de start
        size = start[rows];
        ragged = new T[size];
    } else {
        start = NULL;
        ragged = NULL;
        int cont = 0;

        tam = new int[rows];
        for (int i = 0; i < rows; i++) tam[i] = arr[i];

        // Iterando na matriz para descobrir o número de elementos
        for (int i = 0; i < rows; i++) cont+= tam[i];
        size = cont;

        matriz = new T*[rows];
        for (int i = 0; i < rows; i++) matriz[i] = new T[tam[i]];
    }
}

template <class T>
MyMatrix<T>::MyMatrix(const MyMatrix &mat) {
    this->matriz = NULL;
    this->start = NULL;
    this->ragged = NULL;
    *this = mat;
}

template<class T>
MyMatrix<T>::~MyMatrix() {
    destroy(isRagged());
}

template <class T>
MyMatrix<T> &MyMatrix<T>::operator= (const MyMatrix<T> &mat) {
    destroy(this->isRagged());

    this->rows = mat.rows;
    this->size = mat.size;

    if (mat.isRagged()) {
        this->tam = NULL;
        this->matriz = NULL;

        this->start = new int[rows+1];
        for (int i = 0; i <= rows; i++) this->start[i] = mat.start[i];

        this->ragged = new T[size];
    } else {
        this->start = NULL;
        this->ragged = NULL;

        this->tam = new int[rows];
        for (int i = 0; i < rows; i++) this->tam[i] = mat.tam[i];

        this->matriz = new T*[rows];
        for (int i = 0; i < rows; i++) matriz[i] = new T[tam[i]];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < getNumCols(i); j++) {
            this->set(i,j,( mat.get(i,j) ));
        }
    }

    return *this;
}

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

// O(1)
template <class T>
const T& MyMatrix<T>::get(int linha, int col) const {
    if (isRagged()) {
        return ragged[(start[linha] + col)];

    } else {
        return matriz[linha][col];
    }
}

template <class T>
int MyMatrix<T>::getNumRows() const { return rows; }

template <class T>
int MyMatrix<T>::getNumElems() const {
    return size;
}

// O(1)
template <class T>
int MyMatrix<T>::getNumCols(int linha) const {
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
    // Se o número de colunas for menor, será necessário subtrair dos
    // elementos de start ao invés de somar
    if (newCols == getNumCols(linha)) return;

    int tempElems = getNumElems();
    int difSize = newCols-getNumCols(linha);    // Guarda a diferença de tamanho entre as quantidades de colunas
    size+= difSize;

    T temp[getNumCols(linha)];                  // Guarda a linha antes de alterar o número de colunas
    int tempCols = getNumCols(linha);           // Guarda quantas colunas a linha tinha
    for (int i = 0; i < getNumCols(linha); i++) temp[i] = get(linha,i);
    
    if (isRagged()) {
        T tempRagged[tempElems];              // Guarda a matriz do tipo ragged antes de alterar a linha
        int tempStart[rows+1];                  // Guarda start antes de alterar a linha

        for (int i = 0; i < tempElems; i++) tempRagged[i] = ragged[i];
        for (int i = 0; i <= rows; i++) tempStart[i] = start[i];

        // Todos os elementos de start depois da linha serão aumentados em newCols
        // Se aumentar a linha i, então as linhas i+n começaram depois
        for (int i = linha+1; i <= rows; i++) {
            start[i] = start[i]+difSize;
        }

        delete[] ragged;
        ragged = new T[size];

        if (difSize < 0) {
            int cont = 0;
            while(cont < tempStart[linha]) {
                ragged[cont] = tempRagged[cont];
                cont++;
            }

            // Para de copiar os as colunas quando o novo limite é atingido
            for (int i = 0; i < getNumCols(linha); i++) { 
                ragged[cont] = tempRagged[cont];
                cont++;
            }

            // Pula os elementos das colunas extras
            int contNew = cont-difSize;
            while(contNew < tempStart[rows]) {
                ragged[cont] = tempRagged[contNew];

                cont++;
                contNew++;
            }

        } else {
            for (int i = 0; i < size; i++) ragged[i] = T();

            // Pular os elementos adicionados, continuar depois
            int cont = 0;
            // tempStart[linha+1] guarda a posição inicial do elemento
            // da linha após a linha alterada
            // Ex. se alterarmos o tamanho da linha 5, serão copiados todos
            // os elementos até o final da linha 5
            while(cont < tempStart[linha+1]) {
                ragged[cont] = tempRagged[cont];
                cont++;
            }
            // Se foram adicionadas difSize colunas, então a próxima linha
            // começará em cont+difSize (final da linha antes de ser alterada
            // a quantidade de colunas + quantas colunas foram adicionadas)
            int contNew = cont+difSize;
            while(cont < tempStart[rows]) {
                ragged[contNew] = tempRagged[cont];
                cont++;
                contNew++;
            }
        }

        
    } else {
        delete[] matriz[linha];
        matriz[linha] = new T[newCols];     // Realocando o array com o novo número de colunas
        tam[linha] = newCols;               // Mudando o número de colunas

        if (newCols == 0) return;

        if (difSize > 0) {
            // Inicializa os elementos padrão primeiro, depois copia os elementos
            // já existentes de volta para a matriz
            for (int i = 0; i < getNumCols(linha); i++) matriz[linha][i] = T();
            for (int i = 0; i < tempCols; i++) matriz[linha][i] = temp[i];
        } else {
            for (int i = 0; i < getNumCols(linha); i++)  {
                matriz[linha][i] = temp[i];
            }
        }
    }
}

template <class T>
void MyMatrix<T>::resizeNumRows(int newRows) {
    if (newRows == rows) return;

    int oldRows = rows;
    rows = newRows;
    if (rows < oldRows) {
        for (int i = rows; i < oldRows; i++) size-= (getNumCols(i));
    }

    if (isRagged()) {
        int tempStart[rows+1];
        if (rows > oldRows) {
            for (int i = 0; i <= oldRows; i++) tempStart[i] = start[i];
            // Como as novas linhas não possuem nenhuma coluna, o valor
            // de start será o mesmo para todas as linhas adicionais
            for (int i = oldRows; i <= rows; i++) tempStart[i] = start[oldRows];
        } else {
            for (int i = 0; i <= rows; i++) tempStart[i] = start[i];
        }

        T tempRagged[getNumElems()];
        for (int i = 0; i < getNumElems(); i++) tempRagged[i] = ragged[i];

        destroy(true);
        start = new int[rows+1];
        for (int i = 0; i <= rows; i++) start[i] = tempStart[i];
        ragged = new T[getNumElems()];
        for (int i = 0; i < getNumElems(); i++) ragged[i] = tempRagged[i];

    } else {
        // Transferindo tam para um array temporário para que os dados
        // não sejam perdidos ao desalocar a memória
        int tempTam[rows];
        if (rows > oldRows) {
            for (int i = 0; i < oldRows; i++) tempTam[i] = tam[i];
            // As linhas extras são inicializadas com tamanho 0
            for (int i = oldRows; i < rows; i++) tempTam[i] = 0;
        } else {
            for (int i = 0; i < rows; i++) tempTam[i] = tam[i];
        }

        // Copiando a matriz antiga
        T **tempMatriz = new T*[rows];
        for (int i = 0; i < rows; i++) tempMatriz[i] = new T[tempTam[i]];

        if (rows < oldRows) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < getNumCols(i); j++) {
                    tempMatriz[i][j] = matriz[i][j];
                }
            }
        } else {
            for (int i = 0; i < oldRows; i++) {
                for (int j = 0; j < getNumCols(i); j++) {
                    tempMatriz[i][j] = matriz[i][j];
                }
            }
        }
        // Destruir tam e matriz antes de alocar com o novo número de linhas
        for (int i = 0; i < oldRows; i++) delete[] matriz[i];
        delete[] matriz;
        delete[] tam;

        tam = new int[rows];
        for (int i = 0; i < rows; i++) tam[i] = tempTam[i];

        matriz = new T*[rows];
        for (int i = 0; i < rows; i++) matriz[i] = new T[tam[i]];

        if (rows < oldRows) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < getNumCols(i); j++) {
                    matriz[i][j] = tempMatriz[i][j];
                }
            }
        } else {
            for (int i = 0; i < oldRows; i++) {
                for (int j = 0; j < getNumCols(i); j++) {
                    matriz[i][j] = tempMatriz[i][j];
                }
            }
        }

        for (int i = 0; i < rows; i++) delete[] tempMatriz[i];
        delete[] tempMatriz;
    }
}

// --------------------------------------------------------------------------------

template <class T>
bool MyMatrix<T>::isRagged() const {
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
    tam = new int[rows];
    for (int i = 0; i < rows; i++) {
        tam[i] = getNumCols(i);
    }

    matriz = new T*[start[rows]];
    for (int i = 0; i < rows; i++) matriz[i] = new T[tam[i]];

    // cont guarda quantos elementos já foram adicionados à matriz convertida
    int cont = 0;
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
void MyMatrix<T>::print() const {
    cout << "Rows: " << getNumRows() << "\n";
    cout << "Elems: " << getNumElems() << "\n";

    for (int i = 0; i < getNumRows(); i++) {
        cout << getNumCols(i) << ":";
        if (getNumCols(i) == 0) {
            cout << "\n";
            continue;
        }

        for (int j = 0; j < getNumCols(i); j++) {
            if (j == 0) cout << " " << get(i,j);
            else cout << " " << get(i,j);
        }
        cout << "\n";
    }
}

#endif