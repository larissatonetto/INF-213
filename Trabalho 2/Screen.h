#ifndef Screen_H
#define Screen_H

class Screen {
public:
    const static int EMPTY = 0, SNAKE = 1, FOOD = 2, WALL = 3;

    Screen(int = 1, int = 1);
    Screen(const Screen &);
    ~Screen();

    void destroy();

    int getWidth() const;
    int getHeight() const;
    int get(int, int) const;

    void set(int r, int c, int val);

    Screen& operator= (const Screen&);

private:
    int width, height;
    int **data;
    int *dataHeight;
};

#endif

/**********************************************************************************
 * Cada valor de data aponta para um array dinâmico
 * 
 *dataHeight[c] deverá conter 1 + a linha do pixel não vazio mais alto da tela (ou 0, caso
 * não tenha pixels na coluna) -- Contar quantos pixels != 0 (get) há na coluna?
 *
 *A matriz representando a tela deverá ser armazenada de forma compacta e
 *operações que chamam a função “set” na coluna “c” devem redimensionar a matriz
 *dinamicamente para que o elemento mais alto que não for EMPTY da coluna “c” deva
 *sempre estar armazenado na última posição de data[c]
 *********************************************************************************/