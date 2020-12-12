#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;
    int dig1[n] = {0};
    int dig2[n] = {0};

    for (int i = 0; i < n; i++) {
        string cpf;
        cin >> cpf;
        for (int j = 0, k = 10, l = 11; j < 9; j++, k--, l--) {
            dig1[i]+= (cpf[j]-'0')*k;

            dig2[i]+= (cpf[j]-'0')*l;
        }
        dig1[i] = (dig1[i]*10)%11;
        if (dig1[i] == 10) dig1[i] = 0;

        dig2[i]+= dig1[i]*2;
        dig2[i] = (dig2[i]*10)%11;
    }

    for (int i = 0; i < n; i++) {
        cout << dig1[i] << dig2[i] << "\n";
    }

    return 0;
}