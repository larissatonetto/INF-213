#include "Snake.h"
#include <iostream>

Snake::Snake(int size) {
    dataFirst = dataLast = NULL;
    for (int i = 0; i < size; i++) {
        push_front(0,i);
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

void Snake::push_front(int r, int c) {
    if (dataFirst == NULL) {
        dataFirst = dataLast = new Node(r,c);
        dataLast->next = NULL;
    } else {
        Node *newNode = new Node(r,c);
        newNode->next = dataFirst;
        dataFirst = newNode;
    }
}

void Snake::draw(Screen &s, int state) {
    Node *aux = dataFirst;
    for (int i = 0; i < getLength(); i++) {
        s.set((aux->y),(aux->x),state);
        aux = aux->next;
    }
}

void Snake::move(int dr, int dc, bool eating) {
    if (eating) {
        push_front(( dataFirst->y+dr ), ( dataFirst->x+dc ));
        return;
    } else {
        Node *aux = dataFirst;
        aux->y+= dr;
        aux->x+= dc;
        while (aux != NULL) {
            aux->y+= dr;
            aux->x+= dc;
            aux = aux->next;
        }
    }
}