#ifndef Screen_H
#define Screen_H

class Screen {
public:
    const static int EMPTY = 0, SNAKE = 1, FOOD = 2, WALL = 3;

    Screen(int height = 1, int width = 1);
    Screen(const Screen &other);
    ~Screen();

    void create();
    void destroy();

    int getWidth() const;
    int getHeight() const;
    int get(int r, int c) const;

    void set(int r, int c, int val);

    Screen& operator= (const Screen &other);

private:
    int width, height;
    int **data;
    int *dataHeight;
};

#endif