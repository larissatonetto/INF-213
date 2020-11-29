#include <iostream>
#include <fstream>
#include <string>
#include "MyVec.h"
#include "MyMap.h"

using namespace std;

int main(int argc, char **argv) {
    string line, teste;
    MyVec<string> frases;
    MyMap<string,int> map1;
    int pos = 0;

    if (argc == 2) {
        ifstream entrada(argv[1]);
        while(getline(entrada,line)) {
            
            for (int i = 0; i < line.size(); i++) {
                // Convertendo maiúscula para minúscula
                if (line[i] > 64 && line[i] < 91) line[i]+= 32;
            }
            // if (line[line.size()-1] == '.' || line[line.size()-1] == ',') line.pop_back();
            // Se eu chegar em um separador de sentença, mande a string atual para o MyVec e recomece

            // map1[line] += 1;
            teste+=line + " ";
            // cout << teste << "\n";
        }
    } else {
        cout << "else\n";
        while (getline(cin,line)) {
            if (line == "FINAL_TREINO") break;
            frases.push_back(line);
        }   
    }

    // cout << map1["sentenca"] << "\n";

    // cout << "Frases:\n" << teste << "\n";
    /*for (int i = 0; i < teste.size(); i++) {
        char c = teste[i];
        if (c > 64 && c < 91){
            if (teste[i]+1)
        } c+= 32;
        s.push_back(c);
    }

    cout << s << "\n";*/
    string s;
    // cout << teste << "\n";
    for (int i = 0; i < teste.size(); i++) {
        if (teste[i] == '.'   ||
            teste[i] == '!'   ||
            (teste[i] > 45 && teste[i] < 65) ||    // Retira de . até @
            (teste[i] > 34 && teste[i] < 39) ||
            (teste[i] > 39 && teste[i] < 45)){
            frases.push_back(s);
            s = "";
            continue;
        }

        s+=teste[i];
    }

    for (int i = 0; i < frases.size(); i++) {
        cout << frases[i] << "\n";
    }

    return 0;
}

// Aspas, apóstrofo e newline separam palavras
// Números e sinais de pontuação separam sentenças