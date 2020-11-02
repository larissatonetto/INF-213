#include "Snake.h"
#include <iostream>

Snake::Snake(int size) {
    dataFirst = dataLast = NULL;
    for (int i = 0; i < size; i++) {
        push_back(0,i);
    }
}

Snake::~Snake() {
    if (dataFirst == NULL) {
        return;
    }
    destroy(dataFirst);
}

void Snake::destroy(Node *curr) {
    if (curr == NULL) {
        return;
    }

    destroy(curr->next);
    delete curr;
}

int Snake::getLength() {
    if (dataFirst == NULL) return 0;

    int cont = 0;
    Node *curr = dataFirst;
    while(curr != NULL) {
        cont++;
        curr = curr->next;
    }

    return cont;
}

void Snake::push_back(int r, int c) {
    if (dataFirst == NULL) {
        dataFirst = dataLast = new Node(r,c);
        dataLast->next = NULL;
    } else {
        Node *newLast = new Node(r,c);
        dataLast->next = newLast;
        dataLast = newLast;
        newLast->next = NULL;
    }
}

void Snake::pop() {
    Node *aux = dataFirst;
    dataFirst = dataFirst->next;
    delete aux;
}

void Snake::draw(Screen &s, int state) {
    Node *aux = dataFirst;
    for (int i = 0; i < getLength(); i++) {
        s.set((aux->y),(aux->x),state);
        aux = aux->next;
    }
}

void Snake::move(int dr, int dc, bool eating) {
    push_back(( dataLast->y+dr ), ( dataLast->x+dc ));
    // Quando a cobra come um alimento seu último pixel não se move
    if (!eating) pop();
}

void Snake::print() {
    Node *aux = dataFirst;
    std::cout << "Size: " << getLength() << "\n";
    while(aux != NULL) {
        std::cout << aux->y << "," << aux->x << " ";
        aux = aux->next;
    }
    std::cout << "\n";
}