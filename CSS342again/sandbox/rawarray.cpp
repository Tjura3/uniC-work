#include <iostream>
using namespace std;

double average(const int a[], int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum+=a[i];
    }
    double avg = sum*1.0/size;
    return avg;
} 

int main(){
    int size = 5;
    int arr[5] = {1,2,3,4,5};
    cout << average(arr,size-1) << endl;

    //HEAP ARRAY TESTING
    //remember that if you NEW something, you have to pair with a delete later.
    int *heaparray = new int[size]; //star cause pointer
    for(int i = 0; i < size; i++){
        arr[i] = 10;
    }
    cout << "Address: " << heaparray << endl;

    //resizing
    int newSize = 10;
    int* bigger = new int[newSize];
    for(int i = 0; i < size; i++){
        bigger[i] = arr[i];
    }
    delete []heaparray;
    heaparray = bigger;
    cout << "Address after resize: " << heaparray << endl;
    for(int i = 0; i < newSize; i++){
        cout << heaparray[i] << " ";
    }
    cout << endl;
    delete []heaparray;
    return 0;
}