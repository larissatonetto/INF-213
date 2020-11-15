#ifndef MyPriorityQueue2_H
#define MyPriorityQueue2_H


#include "MyVecNewIterator.h"
#include "MyList2NewIterator.h"
#include <iostream>
using namespace std;

//Nao altere nada na interface!
template<class T>
class MyPriorityQueue2 {
public:
	void push(const T&el);
	T & top() ;
	void pop() ;
	int size() ;
private:
	MyList2<T> elementos;
};



//Altere apenas daqui para baixo...

//ATENCAO: propositalmente nao temos funcoes constantes, visto que nao implementamos iteradores
// constantes na nossa classe lista...
template<class T>	// OK
void MyPriorityQueue2<T>::push(const T&el) {
	elementos.push_back(el);
}

template<class T>	// OK
T & MyPriorityQueue2<T>::top() {
	typename MyList2<T>::iterator it1 = elementos.begin();	// Guarda o elemento que será retornado
	typename MyList2<T>::iterator it2 = elementos.begin();	// Percorre a lista

	while(it2 != elementos.end()) {
		if (*it2 > *it1) it1 = it2;
		it2++;
	}

	return *it1;
}

template<class T>
void MyPriorityQueue2<T>::pop() {
	typename MyList2<T>::iterator it1 = elementos.begin();
	typename MyList2<T>::iterator it2 = elementos.begin();

	while(it2 != elementos.end()) {
		if (*it2 > *it1) it1 = it2;
		it2++;
	}

	elementos.erase(it1);
}

template<class T>
int MyPriorityQueue2<T>::size() {
	int size = 0;
	typename MyList2<T>::iterator it = elementos.begin();

	while(it != elementos.end()) {
		size++;
		it++;
	}

	return size;
}

#endif