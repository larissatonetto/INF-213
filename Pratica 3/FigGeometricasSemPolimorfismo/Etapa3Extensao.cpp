#include <iostream>
#include <typeinfo>
using namespace std;

#include "FigBase.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "Segmento.h"

int main() {
    Circulo c1, c2;
    Retangulo r;
    Segmento s1, s2;

    FigBase *figuras[5];
     
    figuras[0] = &c1;
    figuras[1] = &c2;
    figuras[2] = &r;
    figuras[3] = &s1;
    figuras[4] = &s2;

    for (int i = 0; i < 5; i++) {
       cin >> *(figuras[i]);
    }

    for (int i = 0; i < 5; i++) {
       cout << *(figuras[i]);
    }

    cout << "\n\n";

    for (int i = 0; i < 5; i++) {
        if ( typeid( *(figuras[i]) ) == typeid( c1 ) ) {
            ( dynamic_cast<Circulo* >(figuras[i]) )->
              setRaio( (dynamic_cast<Circulo* >(figuras[i])->getRaio()) * 2 );
              
            cout << *figuras[i];
        }
    }
    
    return 0;
}