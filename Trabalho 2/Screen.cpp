#include "Screen.h"
#include <iostream>

Screen::Screen(int height, int width) {
    this->height = height;
    this->width = width;
    data = new int*[width];
    dataHeight = new int[width];
    for (int i = 0; i < width; i++) {   // Inicialmente não há pixels preenchidos
        data[i] = new int[0];
        dataHeight[i] = 0;
    }
}

Screen::~Screen() {
    destroy();
}

void Screen::destroy() {
    std::cout << "Destrutor de Screen\n";
    for (int i = 0; i < width; i++) delete[] data[i];
    delete[] data;
    delete[] dataHeight;
}

int Screen::getWidth() {
    return width;
}

int Screen::getHeight() {
    return height;
}

// r = linha, c = coluna
int Screen::get(int r, int c) {
    if (r > width || c > width) return WALL;

    if (r >= dataHeight[c]) return EMPTY;

    // Não há a necessidade de especificar qual valor será retornado
    return data[c][r];
}

// r representa a altura da coluna em que será alterado o valor
// O pixel mais alto preenchido é sempre dataHeight[c]-1
void Screen::set(int r, int c, int val) {
    if (dataHeight[c] <= r) {

        // Copiar data[c] antigo antes de realocar
        int auxData[dataHeight[c]], auxHeight = dataHeight[c];
        for (int i = 0; i < dataHeight[c]; i++) auxData[i] = data[c][i];

        dataHeight[c] = r+1;
        delete[] data[c];
        data[c] = new int[(dataHeight[c])]();           // Inicia o array com valor 0  
        for (int i = 0; i < auxHeight; i++) data[c][i] = auxData[i];
    }

    data[c][r] = val;
}

// https://stackoverflow.com/questions/14955824/initializing-a-dynamic-array-to-0