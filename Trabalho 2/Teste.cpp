#include "Game.h"
#include <iostream>
using namespace std;

int main() {
    Game g(10,10,5);

    cout << g.step(1,0) << "\n";
    cout << g.step(1,0) << "\n";
    cout << g.step(-1,0) << "\n";
    cout << g.step(1,0) << "\n";
    cout << g.step(0,1) << "\n";
    cout << g.step(-1,0) << "\n";
    cout << g.step(0,1) << "\n";
    cout << g.step(0,-1) << "\n";

    return 0;
}