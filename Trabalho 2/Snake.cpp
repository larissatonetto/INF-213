#include "Snake.h"
#include <iostream>

Snake::Snake(int size) {
    create();
    for (int i = 0; i < size; i++) {
        push_back(0,i);
    }
}

Snake::Snake(const Snake &other) {
    create();
    *this = other;
}

Snake::~Snake() {
    destroy();
}

void Snake::create() {
    dataFirst = dataLast = NULL;
}

void Snake::destroy(Node *curr) {
    if (curr == NULL) {
        return;
    }

    destroy(curr->next);
    delete curr;
}

void Snake::destroy() {
    if (dataFirst == NULL) return;

    destroy(dataFirst);
    dataFirst = dataLast = NULL;
}

Snake& Snake::operator=(const Snake &other) {
    destroy();

    Node *auxOther = other.dataFirst;
    while(auxOther != NULL) {
        push_back(( auxOther->y ),( auxOther->x ));
        auxOther = auxOther->next;
    }

    return *this;
}

int Snake::getLength() const {
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

// Retorna a posição da cabeça da cobra
int Snake::head(char c) {
    return (c == 'y' ? dataLast->y : dataLast->x);
}

void Snake::draw(Screen &s, int state) {
    Node *aux = dataFirst;
    for (int i = 0; i < getLength(); i++) {
        s.set((aux->y),(aux->x),state);
        aux = aux->next;
    }
}

void Snake::move(int dr, int dc, bool eating) {
    // Quando a cobra come um alimento seu último pixel não se move
    push_back(( dataLast->y+dr ), ( dataLast->x+dc ));
    if (!eating) pop();
}