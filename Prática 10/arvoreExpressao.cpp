#include <iostream>
#include "MyVec.h"
using namespace std;


class ArvoreExpressao {
public:
	void imprimeArrays() const;

	void leArvore();
	void imprimeExpressao() const;
	int avaliaValor() const;
	int altura() const;
	int nivelMaisNodos() const;

private:
	//Nao adicione nenhum membro de dados na sua classe!!!!
	//Funcoes auxiliares podem ser adicionadas se necessario.

	MyVec<int> filhoEsquerdo;
	MyVec<int> filhoDireito;
	MyVec<char> operador;

	void imprimeExpressao(int i) const;		// Imprime a partir do nodo i
	int avaliaValor(int i) const;
	int altura(int i) const;
	void nivelMaisNodos(int i, int nivel, int *largura) const;

	bool isOperator(char c) const;
};

void ArvoreExpressao::imprimeArrays() const {
	for(int i=0;i<filhoEsquerdo.size();i++) cout << i << " "; cout << "\n";
	for(int i=0;i<filhoEsquerdo.size();i++) cout << filhoEsquerdo[i] << " "; cout << "\n";
	for(int i=0;i<filhoDireito.size();i++) cout << filhoDireito[i] << " "; cout << "\n";
	for(int i=0;i<operador.size();i++) cout << operador[i] << " "; cout << "\n";
}

/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
//sua implementacao:
bool ArvoreExpressao::isOperator(char c) const {
	if (c == '+' || c == '-' || c == '*') return true;

	return false;
}

void ArvoreExpressao::leArvore() {
	MyVec<char> nodo;
	int v, n;
	char c;
	cin >> v;

	for (int i = 0; i < v; i++) {
		// Lê primeiro em que nodo estou -> filho da esquerda -> filho da direita -> nodo
		cin >> n;

		cin >> n;
		filhoEsquerdo.push_back(n);

		cin >> n;
		filhoDireito.push_back(n);

		cin >> c;
		operador.push_back(c);
	}
}

void ArvoreExpressao::imprimeExpressao(int i) const {
	// Se o filho do operador for outro operador, abrir parênteses
	if (isOperator(operador[i])) {
		if (isOperator(operador[filhoEsquerdo[i]])) cout << "(";
		imprimeExpressao(filhoEsquerdo[i]);
		cout << operador[i];

		if (isOperator(operador[filhoDireito[i]])) cout << "(";

		imprimeExpressao(filhoDireito[i]);
	} else {
		if (i%2 == 0) {
			cout << operador[i] << ")";
		} else {
			cout << operador[i];
		}
	}
}

void ArvoreExpressao::imprimeExpressao() const {
	// O filho esquerdo de op[i] é fEsq[i] = op[fEsq[i]]
	// O filho direito de op[i] é fDir[i] = op[fDir[i]]
	// Um operador sempre tem dois filhos

	imprimeExpressao(0);
}

int ArvoreExpressao::avaliaValor(int i) const {
	if (isOperator(operador[i])) {
		if (operador[i] == '+') {
			return (avaliaValor(filhoEsquerdo[i]) + avaliaValor(filhoDireito[i]));
		} else if (operador[i] == '-') {
			return (avaliaValor(filhoEsquerdo[i]) - avaliaValor(filhoDireito[i]));
		} else {
			return (avaliaValor(filhoEsquerdo[i]) * avaliaValor(filhoDireito[i]));
		}
		
	} else {
		return operador[i];
	}
}

int ArvoreExpressao::avaliaValor() const {
	return (avaliaValor(0));
}

int ArvoreExpressao::altura(int i) const {
	if (!isOperator(operador[i])) return 0;
	
	return 1+max(altura(filhoEsquerdo[i]),altura(filhoDireito[i]));
}

int ArvoreExpressao::altura() const {
	if (operador.size() == 1) return 0;

	return altura(0);
}

void ArvoreExpressao::nivelMaisNodos(int i, int nivel, int *largura) const {
	largura[nivel]++;

	if (!isOperator(operador[i])) return;

	nivelMaisNodos(filhoEsquerdo[i], nivel+1, largura);
	nivelMaisNodos(filhoDireito[i], nivel+1, largura);
}

int ArvoreExpressao::nivelMaisNodos() const {
	if (operador.size() == 1) return 1;

	int max = 0, h = altura();
	int largura[h] = {0};

	nivelMaisNodos(0, 0, largura);

	for (int i = 0; i < h; i++) {
		if (largura[i] > max) max = largura[i];
	}

	return max;
}




/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/

//Nao modifique aqui
//OBS: cada arquivo de teste começa com a descricao de uma arvore.
//A seguir, ha um numero indicando qual etapa sera testada...
int main() {
	ArvoreExpressao a;
	a.leArvore();

	int etapa;
	cin >> etapa; 
	switch(etapa) {
		case 1:
			cout << "Etapa 1:" << endl;
			a.imprimeArrays();
			break;
		case 2:
			cout << "Etapa 2:" << endl;
			a.imprimeExpressao();
			cout << endl;
			break;
		case 4:
			cout << "Etapa 4:" << endl;
			cout << a.avaliaValor() << endl;
			break;
		case 5:
			cout << "Etapa 5:" << endl;
			cout << a.altura() << endl;
			cout << a.nivelMaisNodos() << endl;
			break;
		default:
			cout << "Erro! Etapa invalida" << endl;
			break;
	}

}