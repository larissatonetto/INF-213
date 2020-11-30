#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MyVec.h"
#include "MyMap.h"

using namespace std;

int main(int argc, char **argv) {
    string line, teste;
    MyVec<string> frases;
    MyMap<string,int> map1;

    // Lê a entrada a cada char e adiciona à string
    // Se o char for um separador de sentença, a string atual é passada para MyVec e resetada

    if (argc == 2) {
        ifstream entrada(argv[1]);
        while(getline(entrada,line)) {
            
            for (int i = 0; i < line.size(); i++) {    // TODO: Colocar em uma função?
                // Convertendo maiúscula para minúscula
                if (line[i] > 64 && line[i] < 91) line[i]+= 32;
            }

            teste+=line + " ";
        }
    } else {
        cin >> line;    // Ignora o INICIO_TREINO
        cin.ignore();
        while (getline(cin,line)) {
            if (line == "FINAL_TREINO") break;
            
            for (int i = 0; i < line.size(); i++) {
                // Convertendo maiúscula para minúscula
                if (line[i] > 64 && line[i] < 91) line[i]+= 32;
            }

            teste+=line + " ";
        }   
    }

    // Separando as sentenças e passando para MyVec ---------------------------
    string s;
    for (int i = 0; i < teste.size(); i++) {
        if (s[0] == ' ') s.erase(0,1);

        if (teste[i] == 39) {    // Verifica se tem apóstrofe
            s+= ' ';
            continue;
        }

        if (teste[i] == '!'   ||
            (teste[i] > 45 && teste[i] < 65) ||    // Retira de . até @
            (teste[i] > 34 && teste[i] < 39) ||
            (teste[i] > 39 && teste[i] < 45)) {
            if (s != "") {
                frases.push_back(s);
            }
            s = "";
            continue;
        }

        s+=teste[i];
    }

    // Se ainda há uma sentença a ser guardada
    if (s != "") {
        if (s[0] == ' ') s.erase(0,1);
        frases.push_back(s);
    }

    // for (int i = 0; i < frases.size(); i++) {
        // cout << frases[i] << "\n";
    // }


    // Passando as palavras para map1 ------------------------------------------------
    string palavra;
    for (int i = 0; i < frases.size(); i++) {
        stringstream t(frases[i]);
        while (t >> palavra) {
            map1[palavra]++;
        }
    }

    return 0;
}

// Aspas, apóstrofo e newline separam palavras
// Números e sinais de pontuação separam sentenças

// cout << map1["sentenca"] << "\n";