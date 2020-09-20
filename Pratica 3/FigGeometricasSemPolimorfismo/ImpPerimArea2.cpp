#include <iostream>
#include <typeinfo>
using namespace std;

#include "FigBase.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "Segmento.h"
      
int main() {
    Retangulo r(13, 7, 2, 4, 1, 1, 1);
    Circulo c(5, 2, 4, 2, 2, 2);
    Segmento s(3, 7, 8, 5, 3, 3, 3);
    FigBase *figuras[3];

    figuras[0] = &r;
    figuras[1] = &c;
    figuras[2] = &s;

    int i;
    for (i=0; i < 3; i++) {
        cout << "Objeto " << i+1 << " eh do tipo " << typeid(*(figuras[i])).name() << endl;
        cout << "Perimetro = " << figuras[i]->perimetro() << endl;
        cout << "Area = " << figuras[i]->area() << endl;
        cout << endl;
     }

    return 0;
    
} // fim de main


/* ----------------------------------------------------------
                 RESULTADO ESPERADO

Objeto 1
Perimetro = 12
Area = 8

Objeto 2
Perimetro = 25.1327
Area = 50.2655

Objeto 3
Perimetro = 5.38516
Area = 0

---------------------------------------------------------------
*/