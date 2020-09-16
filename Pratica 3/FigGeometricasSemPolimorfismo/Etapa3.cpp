#include <iostream>
using namespace std;

#include "FigBase.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "Segmento.h"

 int main() {
   Circulo c1, c2;
   Retangulo r;
   Segmento s1, s2;

   FigBase *a[5];
     
   a[0] = &c1;
   a[1] = &c2;
   a[2] = &r;
   a[3] = &s1;
   a[4] = &s2;

   for (int i = 0; i < 5; i++) {
     cin >> *(a[i]);
   }

   for (int i = 0; i < 5; i++) {
     cout << *(a[i]);
   }
    
   return 0;
 }