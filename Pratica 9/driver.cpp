#include <iostream>
#include <string>
#include "MyQueue.h"
#include "MyStack.h"

using namespace std;


// Insira aqui o codigo para a etapa 1....

//Voce pode adicionar includes como o abaixo...
//#include "MyStack.h"


void etapa1() {
	MyQueue<int> fila;
	MyStack<int> pilha;
	int num;
	for (int i = 0; i < 6; i++) {
		cin >> num;
		fila.push(num);
		pilha.push(num);
	}

	for (int i = 0; i < 6; i++) {
		cout << pilha.top() << " ";
		pilha.pop();
	}
	cout << "\n";
	for (int i = 0; i < 6; i++) {
		cout << fila.front() << " ";
		fila.pop();
	}
	cout << "\n";

	// A pilha imprime os números de na ordem contrária a que eles foram adicionados (LIFO)
	// A fila imprime os números na mesma ordem em que foram adicionados (FIFO)
}

//---------------------------------------

// Insira aqui o codigo para a etapa 2....

void etapa2() {
	MyStack<char> pilha;
	string linha;

	cin.ignore();
	getline(cin, linha);
	for (int i = 0; i < linha.size(); i++) {
		char c = linha[i];
		
		if (c == '(' || c == '[' || c == '{') pilha.push(c);
		else if (c == ')') {
			if (pilha.empty() || pilha.top() != '(') {
				cout << "Inconsistente\n";
				return;
			}
			else pilha.pop();
		} else if (c == ']') {
			if (pilha.empty() || pilha.top() != '[') {
				cout << "Inconsistente\n";
				return;
			}
			else pilha.pop();
		} else if (c == '}') {
			if (pilha.empty() || pilha.top() != '{') {
				cout << "Inconsistente\n";
				return;
			}
			else pilha.pop();
		}
	}
	
	if (!pilha.empty()) cout << "Inconsistente\n";
	else cout << "Consistente\n";
}

//---------------------------------------

// Na etapa 3 voce deve implementar MyQueue2.h e descomentar os codigos de teste abaixo...


#include "MyQueue2.h"
void etapa3() {
	char operacao;
	MyQueue2<string> q;

	//le um arquivo contendo "comandos" para a fila e aplica-os a fila criada com sua classe...
	while(cin>> operacao) {
		if(operacao=='p') {
			string st;
			cin >> st;
			q.push(st); //insere um novo elemento na sua fila...
		} else if(operacao=='f') {
			cout << q.front() << "\n";
		} else if(operacao=='P') {
			q.pop();
		} else if(operacao=='e') {
			cout << ((q.empty())?"vazia":"cheia") << "\n";
		} else cout << q.size() << "\n";
	}
}

//---------------------------------------

// Insira aqui o codigo para a etapa 4....


void etapa4() {
	MyStack<int> pilha;
	int tam, max = 1;
	int n;
	
	cin >> tam;
	if (tam == 0) {
		cout << "SIM\n";
		return;
	}

	// A primeira operação sempre adicionará números
	for (int i = 1; i <= tam; i++) {
		cin >> n;

		if (n > max) {
			for (int i = max; i <= n; i++) {
				pilha.push(i);
				max++;
			}
			pilha.pop();
		} else if (n <= max) {
			if (n == pilha.top()) pilha.pop();

			else {
				cout << "NAO\n";
				return;
			}
		}
	}

	cout << "SIM\n";
}

//---------------------------------------


int main() {
	int etapa;
	cin >> etapa;
	switch(etapa) {
		case 1:
			cout << "Etapa 1" << endl;
			etapa1();
			break;
		case 2:
			cout << "Etapa 2" << endl;
			etapa2();
			break;
		case 3:
			cout << "Etapa 3" << endl;
			etapa3();
			break;
		case 4:
			cout << "Etapa 4" << endl;
			etapa4();
			break;
	}
}