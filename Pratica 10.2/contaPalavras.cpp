#include "MySet.h"
#include "MyVecNewIterator.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    int cont = 0;   // Guarda a quantidade total de palavras
    string entrada = argv[1];
    
    if (entrada == "myvec") {
        MyVec<string> palavras;

        while (cin >> entrada) {
            bool igual = false;
            cont++;

            for (int i = 0; i < palavras.size(); i++) {
                if (palavras[i] == entrada) igual = true;
            }

            if (igual == false) palavras.push_back(entrada);
        }

        cout << cont << " " << palavras.size() << "\n";
    } else {
        MySet<string> palavras;

        while (cin >> entrada) {
            cont++;
            palavras.insert(entrada);
        }

        cout << cont << " " << palavras.size() << "\n";
    }

    return 0;
}