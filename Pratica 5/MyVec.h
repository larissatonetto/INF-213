/*
TAD MyVec
- Representa uma lista implementada por contiguidade
- Interface similar a da classe Vector do STL
- Criado por Salles Magalhaes em 19/02/2018

*/

#ifndef MyVec_H__
#define MyVec_H__

#include <iostream>
#include <string>
#include <ostream>


//Excessao usada pela classe MyVec
class MyVecException {
private:
	std::string msg;
public:
	MyVecException (const std::string &msg0): msg(msg0) { }
	const std::string & what() const { return msg; }
};


template<class T>
class MyVec {
public:
	template<class T2>
	friend std::ostream& operator<<(std::ostream &, const MyVec<T2> &);

	//construtores/destrutures/etc
	MyVec();
	MyVec(int n, const T&init=T());

	//destrutor
	~MyVec() { destroy(); };

	//Construtor de copia
	MyVec(const MyVec &);
	MyVec & operator=(const MyVec &);

	//funcoes de acesso
	T &operator[](int pos) {return data[pos];}
	const T &operator[](int pos) const {return data[pos];}
	void push_back(const T&);
	void resize(int newSize);
	void insert(const T&,int pos);
	void clear();
	int eraseMatchingElements(const T&);
	void sortedInsert(const T&);

	void empty() const {return size() == 0;};
	int size() const {return dataSize;};

private:
	T* data; //declare o membro de dados data, que devera armazenar os elementos da lista
	int dataSize; //quantos elementos ha na lista?
	int dataCapacity; //quantos elementos atualmente cabem na lista? 

	void create();
	void destroy();
	void resizeCapacity(int newCapacity);
};

template<class T>
void MyVec<T>::push_back(const T&elem) {
	//Implemente esta funcao! (nao reutilize a funcao "insere")

	if (dataCapacity == dataSize) {
		if (dataCapacity == 0) resizeCapacity(1);
		else resizeCapacity(2*dataCapacity);
	}

	data[dataSize] = elem;
	dataSize++;
}

template<class T>
void MyVec<T>::resize(int newSize) {
	if(newSize >= dataCapacity) { //primeiro temos que realocar o vector...
		resizeCapacity(newSize); //para o resize vamos usar o tamanho exato caso seja necessario realocar o vector..
	}
	for(int i=dataSize;i<newSize;i++) { //preencha a parte "extra" do vector com valores "em branco"
		data[i] = T();
	}
	dataSize = newSize;
}

//insere o elemento na posicao pos e move os elementos ja presentes no vetor
// pos pode ser:
//   uma posicao apos o final do vetor (para inserir na ultima posicao) 
//   ou uma posicao ja existente (nesse caso os elementos nessa posicao e apos ela serao movidos "para a frente")
template<class T>
void MyVec<T>::insert(const T&elem,int pos) {
	if(pos > dataSize || pos < 0) {
		throw MyVecException("Erro na funcao insert: posicao invalida");
	}

	if(dataSize == dataCapacity) { //preciso redimensionar?
		if(dataCapacity ==0) //Exercicio: Por que e' preciso testar isso?
			resizeCapacity(1);
		else
			resizeCapacity(dataCapacity*2);
	}	

	for(int i=dataSize;i>pos;i--)
		data[i] = data[i-1];
	data[pos] = elem;
	dataSize++;
}


template<class T>
void MyVec<T>::clear() {
	destroy();
	create();
}

template <class T>
int MyVec<T>::eraseMatchingElements(const T &elem) {
	int del = 0, ultimo = dataSize-1;
	
	if (size() == 0) return 0;

	// Move o iterador para o último elemento que não será removido
	while (data[ultimo] == elem) {
		del++;
		ultimo--;
		dataSize--;

		// std::cout << "del no while\n";

		// Se apagou todos os elementos do array, retorna
		if ((ultimo) == -1) return del;
	}
	// dataSize = dataSize - del;

	int i = 0;
	while (i < dataSize-1) {
	// for (int i = 0; i < dataSize-1; i++) {
		if (data[i] == elem) {

			// std::cout << "data[" << i << "] = " << elem << "\n";

			// Remove o elemento i e move os restantes para trás
			for (int j = i; j < dataSize-1; j++) {
				data[j]= data[j+1];
			}
			del++;
			dataSize--;
			// std::cout << "del\n";
		} else i++;
	}

	// dataSize = dataSize - del;

	return del;
}

template <class T>
void MyVec<T>::sortedInsert(const T &elem) {		// OK
	if (dataSize == 0) {
		push_back(elem);
		return;
	}

	for (int i = 0; i < dataSize; i++) {
		if (data[i] >= elem) {
			insert(elem, i);
			return;
		}
	}

	push_back(elem);
}

template<class T>
void MyVec<T>::resizeCapacity(int newCapacity) {
	//implemente esta funcao
	//Ela deve redimensionar o vetor de modo que ele tenha capacidade newCapacity
	//Se newCapacity for menor do que a capacidade atual voce devera ignorar a chamada a esta funcao (i.e., nunca reduziremos a capacidade do vetor)
	//Nao se esqueca de liberar (deletar) a memoria que nao for mais necessaria (para evitar vazamentos de memoria)
	//Exemplo de execucao:
	//data=[1,2,3,,], dataSize=3, dataCapacity=5 (vetor de capacidade 5, com 3 elementos ocupados)
	//se chamarmos resizeCapacity(10), os membros de dados deverao ter os seguintes valores:
	//data=[1,2,3,,,,,,,], dataSize=3, dataCapacity=10

	if (newCapacity <= dataCapacity) return;

	dataCapacity = newCapacity;
	T *temp = new T[newCapacity];

	for (int i = 0; i < this->size(); i++) {
		temp[i] = this->data[i];
	}

	delete[] data;
	data = temp;
}

template<class T>
void MyVec<T>::destroy() {
	delete []data;
	dataSize = dataCapacity = 0;
}

template<class T>
void MyVec<T>::create() {
	data = NULL;
	dataSize = dataCapacity = 0;
}

template<class T>
MyVec<T>::MyVec() {
	create();
}

template<class T>
MyVec<T>::MyVec(int n, const T&init) {		// OK
	//Implemente esta funcao:
	//Cria um vetor de tamanho e capacidade n, onde todos os n elementos valem "init"

	create();
	dataCapacity = n;
	data = new T[n];

	for (int i = 0; i < n; i++) {
		data[i] = init;
		dataSize++;
	}

}


//Construtor de copia
template<class T>
MyVec<T>::MyVec(const MyVec &other) {		// OK
	//Implemente esta funcao
	//Dica: nao duplique codigo! (esta funcao deve ser escrita utilizando apenas 2 linhas de codigo!)

	create();
	*this = other;

}

template<class T>
MyVec<T> & MyVec<T>::operator=(const MyVec &other) {
	if(this==&other) return *this; 
	destroy(); //Exercicio: por que precisamos disso?	// Caso não apagasse aqui, a memória alocada anteriormente seria perdida
	dataCapacity = other.dataCapacity;
	dataSize = other.dataSize;
	//data = other.data; //por que nao podemos fazer isso?
	data = new T[dataCapacity];
	for(int i=0;i<dataSize;i++) data[i] = other.data[i];
	return *this;
}

template<class T2>
std::ostream& operator<<(std::ostream &out, const MyVec<T2> &v) {
	out << "Size: " << v.size() << "\n";
	out << "Capacity: " << v.dataCapacity << "\n";
	for(int i=0;i<v.size();i++) out << v.data[i] << " ";
	out << "\n";
	return out;
}

#endif