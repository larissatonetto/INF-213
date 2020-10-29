#ifndef MyQueue2_H__
#define MyQueue2_H__

#include "MyStack.h"
#include <iostream>
using namespace std;

template<class T>
class MyQueue2 {
public:
	MyQueue2() {} 

	void push(const T&el);
	const T front() ; //Nesta implementacao vamos permitir retorno por copia...
	void pop() ;

	bool empty() ;
	int size() ;

private:
	MyStack<T> pilha1; //nao mude nada nessa interface!!!
	MyStack<T> pilha2; //nao mude nada nessa interface!!!
};


/* Faca sua implementacao abaixo desta linha...*/
/* Faca sua implementacao abaixo desta linha...*/
/* Faca sua implementacao abaixo desta linha...*/
/* Faca sua implementacao abaixo desta linha...*/

// pilha1 só será usada em push

// O(N) - Única função que não é O(1)
template <class T>
void MyQueue2<T>::push(const T &el) {
	if (pilha2.empty()) pilha2.push(el);

	else {
		for (int i = 0; i < pilha2.size(); i++) {
			pilha1.push(pilha2.top());
			pilha2.pop();
		}
		pilha1.push(el);
		for (int i = 0; i <= pilha1.size(); i++) {
			pilha2.push(pilha1.top());
			pilha1.pop();
		}
	}
}

template <class T>
const T MyQueue2<T>::front() {
	return pilha2.top();
}

template <class T>
void MyQueue2<T>::pop() {
	pilha2.pop();
}

template <class T>
bool MyQueue2<T>:: empty() {
	return (pilha2.empty());
}

template <class T>
int MyQueue2<T>::size() {
	return (pilha2.size());
}

// pilha é LIFO, fila é FIFO



#endif