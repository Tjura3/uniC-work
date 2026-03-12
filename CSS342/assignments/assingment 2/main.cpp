#include "Matrix.h"
#include "Vector.h"
#include <iostream>

using namespace std;
void printVector(Vector v);
void printMatrix(Matrix m);
int main(){
    //get vector size
    cout << "enter the size for a vector ";
    int a;
    cin >> a;
    Vector v1 = Vector(a);
    int v1size = a;
    cout << "enter the size for a vector ";
    cin >> a;
    int v2size = a;
    Vector v2 = Vector(v2size);
    cout << endl;

    //populate both vectors
    for(int i = 0; i < v1size; i++){
        v1.setDataAt(i, rand() % 100);
    }
    for(int i = 0; i < v2size; i++){
        v2.setDataAt(i, rand() % 100);
    }
    //breaks when I try to print it, loosing hope in turning this in.
    printVector(v1);
    printVector(v2);
    
    

    return 0;
}


void printVector(Vector v){
    int capacity = v.getCapacity();
    for(int i=0; i < capacity; i++){
        v.getDataAt(i);
    }
}

void printMatrix(Matrix m){
    int rows = m.getRows();
    int cols = m.getColumns();
    for(int i=0; i < rows; i++){
        for(int j=0; j<cols; j++){
            cout << m.getData(i,j) << " ";
        }
        cout << endl;
    }
}