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

            // cout << "Palavra lida: " << palavra << "\n";

            map1[palavra]++;

            if (!t.peek()) {    // Verifica se chegou no final da frase
                // cout << "\nFinal da frase\n\n";
                break;
            }
            // Lê a palavra -> adiciona chave -> guarda valor da próxima palavra
            string aux = palavra;    // Guarda a palavra atual
            t >> palavra;    // Lê a próxima palavra da frase
            if (aux == palavra) break;    // Se cheguei na última palavra, ela não é adicionada

            map2[aux].insert(make_pair(palavra,2));    // Insere com valor 2

            // cout << "Palavra lida 2: " << palavra << "\n\n";

            t.seekg(pos);    // Volta para a palavra anterior
        }
    }

    // cout << map2["meu"]["guarda-chuva"] << "\n";
    
    map2["teste"].insert(make_pair("teste2",5));
    map2["test"].insert(make_pair("TESTE 3",2));
    MyMap<string, MyMap<string,int> >::iterator it = map2.find("teste");
    // cout << map2["teste"]["teste2"] << "\n";
    // if (it != map2.end()) {
        // cout << ((*it).second)["teste2"] << "\n";    // Acessa o valor de teste->teste2
    // }

    return 0;
}

// Aspas, apóstrofo e newline separam palavras
// Números e sinais de pontuação separam sentenças


// voce vai viajar
// voce vai tambem
// a chave “vai” seria mapeada em um segundo map contendo: “tambem” e
// “viajar” como chaves (ambos com o número 1 como valor associado a tais chaves)