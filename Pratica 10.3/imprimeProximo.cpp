#include <iostream>
#include "MySet.h"

using namespace std;

int main() {
    MySet<int> dados;
    char c;

    while (cin >> c) {
        int n;
        cin >> n;

        if (c == 'C') {
            dados.insert(n);
        } else {
            MySet<int>::iterator it = dados.find(n);
            if (it == NULL) cout << "FALHA\n";

            else {
                it++;
                if (it == NULL) cout << "FALHA\n";

                else cout << *it << "\n";
            }
        }
    }

    return 0;
}