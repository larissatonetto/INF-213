#ifndef Snake_H
#define Snake_H

#include "Screen.h"

class Node {
public:
    Node(int r, int c) : x(c), y(r) {}

    int x, y, len;           // x = coluna, y = altura
    Node *next, *prev;
};

class Snake {
public:
    Snake(int = 1);
    ~Snake();

    int getLength();

    void push_front(int, int);

    void draw(Screen &, int);
    void move(int, int, bool);  // Novo dataFirst caso haja comida no espaço, o final da cobra não se move

private:
    Node *dataFirst, *dataLast;

    void destroy(Node *);
};

#endif