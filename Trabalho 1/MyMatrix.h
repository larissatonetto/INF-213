
template <class T>
class MyMatrix {
public:
MyMatrix(int, int *, bool);
MyMatrix(const MyMatrix&);
// ~MyMatrix();

T get();
void set(T);
int getNumRows();
int getNumElems();
int getNumCols(int);

T resizeRow();

bool isRagged();

T convertToRagged();
T convertToTraditional();

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
        tam = nullptr;
        matriz = nullptr;
    } else {
        tam = arr;
        start = nullptr;
        ragged = nullptr;

        // matriz[0] = tam[0] => matriz[0] = 1
        for (int i = 0; i < rows; i++) matriz[i] = new int[tam[i]];
    }
}


template <class T>
int MyMatrix<T>::getNumRows() { return rows; }

template <class T>
int MyMatrix<T>::getNumCols(int linha) {
    int cont = 0;

    if (tam == nullptr) {

    } else {
    for (int i = 0; i < tam[linha]; i++) cont++;
    } 

    return cont;
}