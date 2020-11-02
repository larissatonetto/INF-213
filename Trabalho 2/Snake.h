#ifndef Snake_H
#define Snake_H

#include "Screen.h"

class Node {
public:
    Node(int r, int c) : x(c), y(r) {}

    int x, y;           // x = coluna, y = altura
    Node *next;
};

class Snake {
public:
    Snake(int = 1);
    ~Snake();

    void destroy();

    int getLength();

    void push_back(int, int);
    void pop();
    int head(char); 

    void draw(Screen &, int);
    void move(int, int, bool);  // Novo dataFirst caso haja comida no espaço, o final da cobra não se move

    void print();
private:
    Node *dataFirst, *dataLast;

    void destroy(Node *);
};

#endif