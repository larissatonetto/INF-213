#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include "MyVec.h"
#include "MyMap.h"

using namespace std;

// Tentar colocar em string 3d

int main(int argc, char **argv) {
    string line, teste;
    MyVec<string> frases;
    MyMap<string,int> map1;
    MyMap<string, MyMap<string,int> > map2;
    MyMap<string, MyMap<string, MyMap<string,int> > > map3;

    // it->first aponta para a chave, it->second aponta para o map
    // Dá pra fazer sem usar o find

    // Se o operador [] retornar 0 não deve imprimir

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
    // Passar daqui direto para map1?
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



    for (int i = 0; i < frases.size(); i++) {
        cout << frases[i] << "\n\n\n";
    }



    // Passando as palavras para map1 ------------------------------------------------
    string palavra;
    for (int i = 0; i < frases.size(); i++) {
        stringstream t(frases[i]);
        while (t >> palavra) {
            int pos = t.tellg();    // Guarda a posição da palavra lida
            string aux1 = palavra;         // Guarda a palavra atual

            // cout << "Palavra lida: " << palavra << "\n";

            map1[palavra]++;    // palavra = aux1

            // Lê a palavra -> adiciona chave -> guarda valor da próxima palavra

            t >> palavra;                  // Lê a próxima palavra da frase
            string aux2 = palavra;

            if (aux1 != palavra) {    // Se cheguei na última palavra, ela não é adicionada
                map2[aux1][palavra]++;
            }

            t >> palavra;
            if (aux2 != palavra) {
                map3[aux1][aux2][palavra]++;
            }

            // cout << "Palavra lida 2: " << palavra << "\n\n";

            t.seekg(pos);    // Volta para a palavra anterior
        }
    }

    cout << map1["voce"] << "\n";
    cout << map2["voce"]["vai"] << "\n";
    cout << map3["voce"]["vai"]["viajar"] << "\n";
    
    return 0;
}

// Aspas, apóstrofo e newline separam palavras
// Números e sinais de pontuação separam sentenças


// voce vai viajar
// voce vai tambem
// a chave “vai” seria mapeada em um segundo map contendo: “tambem” e
// “viajar” como chaves (ambos com o número 1 como valor associado a tais chaves)