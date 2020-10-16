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
// Função auxiliar para desalocar os arrays, recebe como argumento
// um bool indicando se a matriz está no modo ragged ou não
void destroy(bool);

// Função auxiliar para alocar os arrays, recebe como argumento
// um bool indicando se a matriz está no modo ragged ou não
void create(bool);

protected:
int rows, size, *tam, *start;
T *ragged, **matriz;
};

// ------------------------------------------------------------------------------- 

template <class T>
MyMatrix<T>::MyMatrix(int numRows, int *arr, bool isRagged) : rows(numRows) {
    if (isRagged) {
        // O array start é maior do que o número de linhas, já que guarda também
        // o número de elementos no final
        // O tamanho do array ragged é igual ao número de elementos
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
    // O operador de atribuição irá chamar destroy(true), já que matriz = NULL
    // ragged e start apontam para NULL para evitar erros no delete[]
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
        create(true);

        for (int i = 0; i <= rows; i++) this->start[i] = mat.start[i];
    } else {
        this->start = NULL;
        this->ragged = NULL;
        create(false);

        for (int i = 0; i < rows; i++) this->tam[i] = mat.tam[i];
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
void MyMatrix<T>::create(bool isRagged) {
    if (isRagged) {
        ragged = new T[size];
        start = new int[rows+1];
        start[0] = 0;
    } else {
        tam = new int[rows];
        // Como ainda não temos os valores de tam, apenas parte da matriz é alocada aqui
        matriz = new T*[rows];
    }
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

// Funções públicas ---------------------------------------------------------------

// O(1) em ambos os modos - basta retornar o elemento na posição indicada
template <class T>
const T& MyMatrix<T>::get(int linha, int col) const {
    if (isRagged()) {
        return ragged[(start[linha] + col)];

    } else {
        return matriz[linha][col];
    }
}

// O(1) em ambos os modos - basta retornar rows
template <class T>
int MyMatrix<T>::getNumRows() const { return rows; }

// O(1) em ambos os modos - basta retornar size
template <class T>
int MyMatrix<T>::getNumElems() const {
    return size;
}

// O(1) em ambos os modos
// No modo tradicional, retornar o valor de tam na coluna desejada
// No modo ragged, subtrair duas posições consecutivas de start
template <class T>
int MyMatrix<T>::getNumCols(int linha) const {
    if (isRagged()) {
        // No modo ragged, a quantidade de colunas de uma linha
        // é a diferença entre o ponto de início da coluna e da próxima
        return (start[linha+1] - start[linha]);

    } else {
        return tam[linha];
    }
}

// O(1) em ambos os casos, basta mudar o valor na posição indicada
template <class T>
void MyMatrix<T>::set(int linha, int col, const T &elem) {
    if (isRagged()) {
        // O elemento i,j da matriz no modo ragged pode ser acessado
        // a partir do ponto de início da linha i em start somado ao
        // número j da coluna
        ragged[(start[linha] + col)] = elem;

    } else {
        matriz[linha][col] = elem;
    }
}

// Complexidade do modo tradicional: O(C) -- O(C) para copiar os elementos da linha
// + O(C) para preenchar a nova linha = O(2C) = O(C)
// Complexidade do modo ragged: O(T+R) -- O(T) para copiar os elementos de ragged
// + O(R+1) para copiar os elementos de start + O(R+1) para alterar os elementos de start
// + O(T) para inserir os elementos padrão + O(T) para preencher a nova matriz
// = O(T+R+1+R+1+T+T) = O(3T+2R+2) = O(T+R)
template <class T>
void MyMatrix<T>::resizeRow(int linha, int newCols) {
    if (newCols == getNumCols(linha)) return;

    int tempElems = getNumElems();            // Guarda quantos elementos a matriz tinha
    int tempCols = getNumCols(linha);         // Guarda quantas colunas a linha tinha
    int difSize = newCols-getNumCols(linha);  // Guarda a diferença de tamanho entre as quantidades de colunas
    size+= difSize;                           // Atualizando o número de elementos da matriz
    
    if (isRagged()) {
        T tempRagged[tempElems];              // Guarda a matriz antes de alterar o número de colunas
        int tempStart[rows+1];                // Guarda start antes de alterar o número de colunas
        for (int i = 0; i < tempElems; i++) tempRagged[i] = ragged[i];
        for (int i = 0; i <= rows; i++) tempStart[i] = start[i];

        // Todos os elementos de start depois da linha serão somados a difSize
        // Se aumentar a linha i, então as linhas depois dela começarão depois
        // Se diminuir, as linhas começarão antes
        for (int i = linha+1; i <= rows; i++) {
            start[i] = start[i]+difSize;
        }

        // Realocando ragged com o novo número de elementos
        delete[] ragged;
        ragged = new T[size];

        if (difSize > 0) {
            for (int i = 0; i < size; i++) ragged[i] = T();

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
            while(cont < tempElems) {
                ragged[contNew] = tempRagged[cont];
                cont++;
                contNew++;
            }

        } else {
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

            // Pula os elementos das colunas cortadas. Ex. se foram cortadas
            // 2 colunas, contNew = 2, e serão ignorados os dois próximos
            // elementos da matriz antiga ao copiar
            int contNew = cont-difSize;
            while(contNew < tempStart[rows]) {
                ragged[cont] = tempRagged[contNew];

                cont++;
                contNew++;
            }
        }

        
    } else {
        T temp[getNumCols(linha)];          // Guarda a linha antes de alterar o número de colunas
        for (int i = 0; i < tempCols; i++) temp[i] = matriz[linha][i];
        delete[] matriz[linha];
        matriz[linha] = new T[newCols];     // Realocando o array com o novo número de colunas
        tam[linha] = newCols;               // Mudando o número de colunas

        if (newCols == 0) return;

        if (difSize > 0) {
            // Copia os elementos já existentes de volta para a matriz
            // e adiciona os elementos padrão nas novas colunas
            for (int i = 0; i < getNumCols(linha); i++) {
                if (i < tempCols) matriz[linha][i] = temp[i];
                else matriz[linha][i] = T();
            }
        } else {
            for (int i = 0; i < getNumCols(linha); i++)  {
                matriz[linha][i] = temp[i];
            }
        }
    }
}

// Complexidade do modo tradicional: O(R*C) -- O(R) para copiar tam para tempTam
// + O(R*C) para varrer as colunas e copiar matriz para tempMatriz + O(R) para
// desalocar matriz + O(R) para copiar preencher tam + O(R) para realocar matriz
// + O(R*C) para preencher matriz +O(R) para desalocar tempMatriz
// = O(R+(R*C)+R+R+R+(R*C)+R) = O(2(R*C)+5R) = O(R*C)
// Complexidade do modo ragged: O(T+R) -- O(R+1) para copiar start para tempStart
// + O(T) para copiar os elementos para tempRagged + O(R+1) para copiar tempStart
// de volta para start + O(T) para copiar os elementos de volta para ragged
// = O(R+1+T+R+1+T) = O(2T+2R+2) = O(T+R)
template <class T>
void MyMatrix<T>::resizeNumRows(int newRows) {
    if (newRows == rows) return;

    // Se o novo número de linhas for menor, subtrair do tamanho os elementos
    // das linhas que serão retiradas
    if (newRows < rows) {
        for (int i = newRows; i < rows; i++) size-= (getNumCols(i));
    }

    if (isRagged()) {
        int tempStart[newRows+1];
        if (newRows > rows) {
            for (int i = 0; i <= rows; i++) tempStart[i] = start[i];
            // Como as novas linhas não possuem nenhuma coluna, o valor de start
            // será o mesmo para todas as linhas adicionais
            for (int i = rows; i <= newRows; i++) tempStart[i] = start[rows];
        } else {
            for (int i = 0; i <= newRows; i++) tempStart[i] = start[i];
        }

        T tempRagged[getNumElems()];
        for (int i = 0; i < getNumElems(); i++) tempRagged[i] = ragged[i];

        // O número antigo de linhas não é mais necessário, substituindo
        rows = newRows;
        // Realocando start e ragged
        destroy(true);
        create(true);
        for (int i = 0; i <= rows; i++) start[i] = tempStart[i];
        for (int i = 0; i < getNumElems(); i++) ragged[i] = tempRagged[i];

    } else {
        // Transferindo tam para um array temporário para que os dados
        // não sejam perdidos ao realocar a memória
        int tempTam[newRows];
        if (newRows > rows) {
            for (int i = 0; i < rows; i++) tempTam[i] = tam[i];
            // As linhas extras são inicializadas com tamanho 0
            for (int i = rows; i < newRows; i++) tempTam[i] = 0;
        } else {
            for (int i = 0; i < newRows; i++) tempTam[i] = tam[i];
        }

        // Copiando a matriz antiga
        T **tempMatriz = new T*[newRows];
        for (int i = 0; i < newRows; i++) tempMatriz[i] = new T[tempTam[i]];

        if (newRows < rows) {
            for (int i = 0; i < newRows; i++) {
                for (int j = 0; j < getNumCols(i); j++) {
                    tempMatriz[i][j] = matriz[i][j];
                }
            }
        } else {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < getNumCols(i); j++) {
                    tempMatriz[i][j] = matriz[i][j];
                }
            }
        }
        
        // Realocando tam e matriz
        destroy(false);
        // A função create() não é utilizada aqui pois ainda não atualizamos
        // o valor de rows
        tam = new int[newRows];
        matriz = new T*[newRows];
        for (int i = 0; i < newRows; i++) tam[i] = tempTam[i];
        for (int i = 0; i < newRows; i++) matriz[i] = new T[tam[i]];

        if (newRows < rows) {
            for (int i = 0; i < newRows; i++) {
                for (int j = 0; j < getNumCols(i); j++) {
                    matriz[i][j] = tempMatriz[i][j];
                }
            }
        } else {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < getNumCols(i); j++) {
                    matriz[i][j] = tempMatriz[i][j];
                }
            }
        }

        for (int i = 0; i < newRows; i++) delete[] tempMatriz[i];
        delete[] tempMatriz;
        rows = newRows;
    }
}

// --------------------------------------------------------------------------------

// O(1) -- apenas verificar se matriz é NULL
template <class T>
bool MyMatrix<T>::isRagged() const {
    return (matriz == NULL);
}

// O(R*C) -- O(R+1) para preencher start + O(R*C) para copiar os elementos para ragged
// + O(R) para desalocar matriz
// = O(R+1+(R*C)+R) = O((R*C)+2R+1) = O(R*C)
template <class T>
void MyMatrix<T>::convertToRagged() {
    if (isRagged()) return;

    // Alocando start e ragged
    create(true);
    // cont guarda a soma dos elementos de todas as colunas
    // A cada iteração, a soma atual de elementos é guardada em start[i]
    // Por exemplo, se a coluna 0 tem 3 elementos, então cont = 3 e start[1] = 3
    // i começa no 1 pois start[0] é sempre 0
    int cont = 0;
    for (int i = 1; i <= rows; i++) {
        cont+= tam[i-1];
        start[i] = cont;
    }

    int i = 0;
    for (int j = 0; j < rows; j++) {
        for (int k = 0; k < getNumCols(j); k++) {
            ragged[i] = matriz[j][k];
            i++;
        }
    }

    // Destruindo matriz e tam
    destroy(false);
    matriz = NULL;
    tam = NULL;
}

// O(R*C) -- O(R) para preencher tam + O(R) para alocar matriz + O(R*C) para preencher
// matriz = O(R+R+(R*C)) = O((R*C)+2R) = O(R*C)
template <class T>
void MyMatrix<T>::convertToTraditional() {
    if (!isRagged()) return;

    // matriz é alocada depois para que getNumCols() utilize o modo ragged
    // getNumCols verifica se matriz é NULL ou não
    tam = new int[rows];
    for (int i = 0; i < rows; i++) tam[i] = getNumCols(i);
    matriz = new T*[rows];
    for (int i = 0; i < rows; i++) matriz[i] = new T[tam[i]];

    // cont guarda quantos elementos já foram adicionados à matriz convertida
    int cont = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < getNumCols(i); j++) {
            matriz[i][j] = ragged[cont];
            cont++;
        }
    }

// Destruindo start e ragged
    destroy(true);
    start = NULL;
    ragged = NULL;  
}

// O(R*C) para varrer as colunas e imprimir os elementos
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