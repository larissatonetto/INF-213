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
    Snake(int size = 1);
    Snake(const Snake &other);
    ~Snake();

    void create();
    void destroy();

    int getLength() const;

    void push_back(int r, int c);
    void pop();
    int head(char c); 

    void draw(Screen &s, int state);
    void move(int dr, int dc, bool eating);

    Snake& operator= (const Snake &other);

private:
    Node *dataFirst, *dataLast;

    void destroy(Node *);
};

#endif