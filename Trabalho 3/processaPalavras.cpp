#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include "MyVec.h"
#include "MyMap.h"

using namespace std;

// Tentar colocar em string 3d

void consulta(MyMap<string,int> map1,
              MyMap<string, MyMap<string,int> > map2,
              MyMap<string, MyMap<string, MyMap<string,int> > > map3,
              MyVec<pair<int,string> > m1,
              MyMap<string,MyVec<pair<int,string> > > m2,
              MyMap<string,MyMap<string,MyVec<pair<int,string> > > > m3,
              int k, const MyVec<string> &v) {
    if (v.size() == 1) {
        cout << v[0] << " (" << map1[v[0]] << ")\n";

        if (m2[v[0]].size() >= 1) {
            int i = 0;

            while((i < m2[v[0]].size()) && (i < k)) {
                cout << v[0] << " " << m2[v[0]][i].second << " (" << m2[v[0]][i].first << ")\n";

                i++;
            }
        }


    } else if (v.size() == 2) {
        cout << v[0] << " " << v[1] << " (" << map2[v[0]][v[1]] << ")\n"; 

        if (m3[v[0]][v[1]].size() >= 1) {
            int i = 0;

            while((i < m3[v[0]][v[1]].size()) && (i < k)) {
                cout << v[0] << " " << v[1] << " ";
                cout << m3[v[0]][v[1]][i].second << " (" << m3[v[0]][v[1]][i].first << ")\n";

                i++;
            }
        }


    } else {
        cout << v[0] << " " << v[1] << " " << v[2] << " (" << map3[v[0]][v[1]][v[2]] << ")\n";
    }
}

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
        cout << frases[i] << "\n\n";
    }

    

    // Passando as palavras para os maps -----------------------------------------------
    string palavra;

    for (int i = 0; i < frases.size(); i++) {
        stringstream t(frases[i]);
        while (t >> palavra) {
            map1[palavra]++;
        }
    }

    for (int i = 0; i < frases.size(); i++) {
        stringstream t(frases[i]);
        while (t >> palavra) {
            int pos = t.tellg();           // Guarda a posição da palavra lida
            string aux1 = palavra;         // Guarda a palavra atual
            // map1[palavra]++;    // palavra = aux1

            // Lê a palavra -> adiciona chave -> guarda valor da próxima palavra

            t >> palavra;                  // Lê a próxima palavra da frase
            string aux2 = palavra;

            if (aux1 != palavra) {    // Se cheguei na última palavra, ela não é adicionada
                map2[aux1][palavra]++;
            }

            t >> palavra;
            string aux3 = palavra;
            if (aux2 != aux3) {
                map3[aux1][aux2][aux3]++;
            }

            t.seekg(pos);    // Volta para a palavra anterior
        }
    }
    
    // Criando maps ordenados ------------------------------------------

    // Funcionando para ordenar map1
    // m1 guarda as palavras em ordem decrescente de ocorrência
    // m1[0] guarda 4,voce
    MyVec<pair<int,string> > m1;
    for (MyMap<string,int>::iterator it = map1.begin(); it!=NULL;it++) {
        m1.sortedInsert(make_pair((*it).second,(*it).first));
    }

    cout << m1[0].second << "\n";

    MyVec<MyVec<pair<int,string> > > v2;
    MyMap<string,MyVec<pair<int,string> > > m2;

    for (MyMap<string,MyMap<string,int> >::iterator it = map2.begin();it!=NULL;it++) {
        for (MyMap<string,int>::iterator it2 = (*it).second.begin();it2!=NULL;it2++) {
            m2[(*it).first].sortedInsert(make_pair((*it2).second,(*it2).first));
        }
    }
    // voce[0] é o mais provável, voce[1] é o segundo mais provável, etc
    cout << m2["voce"][0].second << "\n";

    MyVec<MyVec<pair<int,string> > > v3;
    MyMap<string,MyMap<string,MyVec<pair<int,string> > > > m3;

    for (MyMap<string, MyMap<string, MyMap<string,int> > >::iterator it = map3.begin();it!=NULL;it++) {
        for (MyMap<string,MyMap<string,int> >::iterator it2 = (*it).second.begin();it2!=NULL;it2++) {
            for (MyMap<string,int>::iterator it3 = (*it2).second.begin();it3!=NULL;it3++) {
                m3[(*it).first][(*it2).first].sortedInsert(make_pair((*it3).second,(*it3).first));
            }
        }
    }

    // Exemplo de acesso em m3
    // [como][voce].size() fala quantas opções depois de "como voce"
    cout << m3["como"]["voce"][1].first << "\n";

    // Leitura dos comandos ------------------------------------------------
    string st;
    while (cin >> st) {
        if (st == "consultar") {
            int k;
            MyVec<string> valores;

            cin >> k;
            cin.ignore();
            
            getline(cin, st);
            stringstream steste(st);
            while (steste >> st) {
                valores.push_back(st);
            }
            consulta(map1,map2,map3,m1,m2,m3,k,valores);
            break;
        }
        break;
    }



    return 0;
}

// Aspas, apóstrofo e newline separam palavras
// Números e sinais de pontuação separam sentenças


// voce vai viajar
// voce vai tambem
// a chave “vai” seria mapeada em um segundo map contendo: “tambem” e
// “viajar” como chaves (ambos com o número 1 como valor associado a tais chaves)

/*for (MyMap<string,MyMap<string,int> >::iterator it = map2.begin();it!=NULL;it++) {
        for (MyMap<string,int>::iterator it2 = (*it).second.begin();it2!=NULL;it2++) {
            // cout << "it = " << (*it).first << "\n";
            // cout << "it2 = " << (*it2).first << " " << (*it2).second << "\n";

            v2.sortedInsert(make_pair((*it).first,make_pair((*it2).second,(*it2).first)));
        }
    }*/