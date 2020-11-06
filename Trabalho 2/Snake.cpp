#include "Snake.h"
#include <iostream>

Snake::Snake(int size) {
    dataFirst = dataLast = NULL;
    for (int i = 0; i < size; i++) {
        push_back(0,i);
    }
}

Snake::Snake(const Snake &other) {
    dataFirst = NULL;
    *this = other;
}

Snake::~Snake() {
    destroy();
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
    dataFirst = NULL;
}

Snake& Snake::operator=(const Snake &other) {
    this->destroy();
    dataFirst = dataLast = NULL;

    Node *aux = other.dataFirst;
    while(aux != NULL) {
        this->push_back(( aux->y ),( aux->x ));
        aux = aux->next;
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

int Snake::head(char pos) {
    return (pos == 'y' ? dataLast->y : dataLast->x);
}

void Snake::draw(Screen &s, int state) {
    Node *aux = dataFirst;
    for (int i = 0; i < getLength(); i++) {
        s.set((aux->y),(aux->x),state);
        // std::cout << "set = " << s.get(aux->y, aux->x) << "\n";
        aux = aux->next;
    }
}

void Snake::move(int dr, int dc, bool eating) {
    push_back(( dataLast->y+dr ), ( dataLast->x+dc ));
    // Quando a cobra come um alimento seu último pixel não se move
    if (!eating) pop();
}