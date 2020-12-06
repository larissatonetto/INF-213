#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "MyVec.h"
#include "MyMap.h"

using namespace std;

void consultar(MyMap<string,int> map1,
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

string aleatorio(MyVec<pair<int,string> > v) {
    MyVec<string> vecAux;

    // Palavras mais frequentes são adicionadas mais vezes no vetor,
    // logo elas tem mais chance de serem escolhidas
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].first; j++) {
            vecAux.push_back(v[i].second);
        }
    }

    if (vecAux.size() == 1) return vecAux[0];   // Se só tem uma opção, ela é retornada

    int n = rand()%(vecAux.size());

    return vecAux[n];
}

void gerar(MyMap<string,int> map1,
           MyMap<string, MyMap<string,int> > map2,
           MyMap<string, MyMap<string, MyMap<string,int> > > map3,
           MyVec<pair<int,string> > m1,
           MyMap<string,MyVec<pair<int,string> > > m2,
           MyMap<string,MyMap<string,MyVec<pair<int,string> > > > m3,
           int k, string modo,const MyVec<string> &v) {
    
    // As duas últimas palavras da frase são guardadas em um array
    // O array é atualizado a cada palavra gerada
    string palavraAnterior[2], palavraAtual;

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }

    int i = 0;
    if (v.size() == 0) {
        if (modo == "aleat") {
            palavraAtual = aleatorio(m1);
        } else {
            palavraAtual = m1[0].second;
        }
    
        cout << palavraAtual << " ";
        palavraAnterior[0] = palavraAtual;

        i++;

        if (i == k) return;

        if (m2[m1[0].second].size() != 0) {
            if (modo == "aleat") {
                palavraAtual = aleatorio(m2[m1[0].second]);
            } else {
                palavraAtual = m2[m1[0].second][0].second;
            }

            cout << palavraAtual << " ";
            palavraAnterior[1] = palavraAtual;

        } else {
            if (modo == "aleat") {
                palavraAtual = aleatorio(m1);
            } else {
                palavraAtual = m1[0].second;
            }

            cout << palavraAtual << " ";
            palavraAnterior[1] = palavraAtual;
        }

        i++;

    } else if (v.size() == 1) {
        palavraAnterior[0] = v[0];

        if (m2[v[0]].size() != 0) {
            if (modo == "aleat") {
                palavraAtual = aleatorio(m2[v[0]]);
            } else {
                palavraAtual = m2[v[0]][0].second;
            }

            cout << palavraAtual << " ";
            palavraAnterior[1] = palavraAtual;

        } else {
            if (modo == "aleat") {
                palavraAtual = aleatorio(m1);
            } else {
                palavraAtual = m1[0].second;
            }

            cout << palavraAtual << " ";
            palavraAnterior[1] = palavraAtual;
        }

        i++;

    } else {
        palavraAnterior[0] = v[v.size()-2];
        palavraAnterior[1] = v[v.size()-1];
    }
    
    if (i == k) return;
    
    while (i < k) {
        if (m3[palavraAnterior[0]][palavraAnterior[1]].size() != 0) {
            if (modo == "aleat") {
                palavraAtual = aleatorio(m3[palavraAnterior[0]][palavraAnterior[1]]);
            } else {
                palavraAtual = m3[palavraAnterior[0]][palavraAnterior[1]][0].second;
            }

            string aux = palavraAnterior[0];
            palavraAnterior[0] = palavraAnterior[1];
            palavraAnterior[1] = palavraAtual;

        } else if (m2[palavraAnterior[1]].size() != 0){
            if (modo == "aleat") {
                palavraAtual = aleatorio(m2[palavraAnterior[1]]);
            } else {
                palavraAtual = m2[palavraAnterior[1]][0].second;
            }

            palavraAnterior[0] = palavraAnterior[1];
            palavraAnterior[1] = palavraAtual;

        } else {
            if (modo == "aleat") {
                palavraAtual = aleatorio(m1);
            } else {
                palavraAtual = m1[0].second;
            }

            palavraAnterior[0] = palavraAnterior[1];
            palavraAnterior[1] = palavraAtual;
        }

        cout << palavraAtual << " ";
        i++; 
    }
}

string processaTexto(istream &fin) {
    string texto, line;
    fin >> texto;

    while(getline(fin,line)) {
        if (line == "INICIO_TREINO") continue;

        if (line == "FINAL_TREINO") return texto;
            
        for (int i = 0; i < line.size(); i++) {
            // Convertendo maiúscula para minúscula
            if (line[i] > 64 && line[i] < 91) line[i]+= 32;
        }

        texto+= line + " ";
}

    return texto;
}

int main(int argc, char **argv) {
    string line, textoTratado;    // line lê de linha em linha, cada linha tratada é adicionada a textoTratado
    MyVec<string> frases;   // Armazena as frases separadas
    MyMap<string,int> map1;
    MyMap<string, MyMap<string,int> > map2;
    MyMap<string, MyMap<string, MyMap<string,int> > > map3;

    // Lê a entrada a cada char e adiciona à string
    if (argc == 2) {
        ifstream entrada(argv[1]);
        textoTratado = processaTexto(entrada);
        
    } else {
        textoTratado = processaTexto(cin);  
    }

    // Separando as sentenças e passando para um MyVec --------------------------------
    string s;
    for (int i = 0; i < textoTratado.size(); i++) {
        if (s[0] == ' ') s.erase(0,1);  // Retira espaço vazio antes da frase

        if (textoTratado[i] == 39) {    // Verifica se tem apóstrofe
            s+= ' ';
            continue;
        }

        if ((textoTratado[i] > 45 && textoTratado[i] < 65) ||    // Retira de . até @
            (textoTratado[i] > 32 && textoTratado[i] < 39) ||    // Retira de ! até &
            (textoTratado[i] > 39 && textoTratado[i] < 45)) {    // Retira de ( até ,
            if (s != "") {
                frases.push_back(s);
            }
            s = "";
            continue;
        }

        s+= textoTratado[i];
    }

    // Verifica se ainda há alguma sentença a ser guardada
    if (s != "") {
        if (s[0] == ' ') s.erase(0,1);
        frases.push_back(s);
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
            int pos = t.tellg();    // Guarda a posição da palavra lida
            string aux1 = palavra;  // Guarda a palavra atual

            t >> palavra;    // Lê a próxima palavra da frase
            string aux2 = palavra;

            if (aux1 != palavra) {    // Se cheguei na última palavra, ela não é adicionada
                map2[aux1][palavra]++;
            }

            t >> palavra;
            if (aux2 != palavra) {
                map3[aux1][aux2][palavra]++;
            }

            t.seekg(pos);    // Volta para a palavra anterior
        }
    }
    
    // Criando maps ordenados --------------------------------------------------

    // m1 guarda as palavras em ordem decrescente de ocorrência
    MyVec<pair<int,string> > m1;
    for (MyMap<string,int>::iterator it = map1.begin(); it!=NULL;it++) {
        m1.sortedInsert(make_pair((*it).second,(*it).first));
    }

    // Exemplo de acesso em m2:
    // [como].size() fala quantas opções depois de "como"
    MyMap<string,MyVec<pair<int,string> > > m2;

    for (MyMap<string,MyMap<string,int> >::iterator it = map2.begin();it!=NULL;it++) {
        for (MyMap<string,int>::iterator it2 = (*it).second.begin();it2!=NULL;it2++) {
            m2[(*it).first].sortedInsert(make_pair((*it2).second,(*it2).first));
        }
    }

    // Exemplo de acesso em m3:
    // [como][voce].size() fala quantas opções depois de "como voce"
    MyMap<string,MyMap<string,MyVec<pair<int,string> > > > m3;

    for (MyMap<string, MyMap<string, MyMap<string,int> > >::iterator it = map3.begin();it!=NULL;it++) {
        for (MyMap<string,MyMap<string,int> >::iterator it2 = (*it).second.begin();it2!=NULL;it2++) {
            for (MyMap<string,int>::iterator it3 = (*it2).second.begin();it3!=NULL;it3++) {
                m3[(*it).first][(*it2).first].sortedInsert(make_pair((*it3).second,(*it3).first));
            }
        }
    }

    // Leitura dos comandos ------------------------------------------------
    srand(time(NULL));

    string st;
    while (cin >> st) {
        if (st == "consultar") {
            int k;
            MyVec<string> valores;

            cin >> k;
            cin.ignore();
            
            getline(cin, st);
            stringstream sConsulta(st);
            while (sConsulta >> st) {
                valores.push_back(st);
            }

            consultar(map1,map2,map3,m1,m2,m3,k,valores);

        } else {
            string modo;
            int k;
            MyVec<string> valores;

            cin >> k;
            cin >> modo;
            cin.ignore();

            getline(cin,st);
            stringstream sGerar(st);
            while (sGerar >> st) {
                valores.push_back(st);
            }
            
            gerar(map1,map2,map3,m1,m2,m3,k,modo,valores);
            cout << "\n";
        }
    }
    
    return 0;
}