#include "MyMap.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    int cont = 0;
    string entrada;
    MyMap<string,int> m;

    while (cin >> entrada) {
        if (m.find(entrada) == NULL) {
            m[entrada] = cont;
            cont++;
        }

        cout << entrada << " " << m[entrada] << "\n";
    }

    return 0;
}