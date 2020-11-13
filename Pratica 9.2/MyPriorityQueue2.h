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
template<class T>
void MyPriorityQueue2<T>::push(const T&el) {

}

template<class T>
T & MyPriorityQueue2<T>::top() {
	
}

template<class T>
void MyPriorityQueue2<T>::pop() {
	
}

template<class T>
int MyPriorityQueue2<T>::size() {
	
}

#endif