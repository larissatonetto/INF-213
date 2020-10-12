#include <iostream>
#include "MyMatrix.h"
using namespace std;

int main() {
    int tams[] = {1,0,3,5,2};
    MyMatrix<int> m(5, tams, true);

    for(int i=0,ct=1;i<m.getNumRows();i++) {
		for(int j=0;j<m.getNumCols(i);j++,ct++) {
			m.set(i,j,ct); 
		}
	}

    cout << m.getNumElems() << "\n";
    // m.resizeRow(0, 6);
    m.print();

    return 0;
}


// TODO: resizeRow(), convert()