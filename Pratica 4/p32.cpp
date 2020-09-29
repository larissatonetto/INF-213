#include "Conjunto2.h"

int main() {
    Conjunto<int> a(10), b(10);
    int n = 40000;

    for (int i = 1; i <= n; i++) {
        a.insere(i);
        b.insere(-i);
    }

    Conjunto<int> c = a + b;
    cout << c.pertence(10);

    return 0;
}