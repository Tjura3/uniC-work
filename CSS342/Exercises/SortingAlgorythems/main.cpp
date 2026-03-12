#include <iostream>
#include <vector>
#include <limits>
using namespace std;
void printarr(int arr[], int length){
    
    for(int i = 0; i < length; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}
void printvector(vector<int>& arr){
    int b = 0;
    for(int i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
        b++;
        if(b == 10){
            cout << endl;
        }
    }
}
int Bubblesort(int* arr, int length){
    int c = 0;
    for(int i = 1; i < length-1; i++){
        for(int j = length; j > i-1; j--){
            if(arr[j] < arr[j-1]){
                int a = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = a;
            }
            c++;
        }
        c++;
    }
    return c;
}
int merge(vector<int>& arr, int left, int middle,int right){ //arr = A, p = left, q = middle, r = right  
    int N1 = middle-left+1;
    int N2 = right-middle;
    vector<int> L;
    vector<int> R;
    for(int i = 0; i < N1; i++){
        L[i] = arr[left+i-1];
    }
    for(int j = 0; j < N2; j++){
        R[j] = arr[middle+j];
    }
    L[N1 + 1] = numeric_limits<int>::max();
    R[N2+1] = numeric_limits<int>::max();
    int i = 1;
    int j = 1;
    for(int k = left; k <= right; k++){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j=j+1;
        }
    }
}
int Mergesort(vector<int>& vec, int p, int r){ //if p is r, and r is n, 
    int c = 0;
    if(p < r){
        int q = (p+r)/2;
        Mergesort(vec, p, q);
        Mergesort(vec, q+1, r);
        merge(vec, p, q, r);
    }
    return c;
}


int main(){
    int array[5] = {20, 30, 10, 50, 40}; 
    int arrsize = sizeof(array)/sizeof(array[0]);
    printarr(array, arrsize);
    int cost = Bubblesort(array, arrsize);
    cout <<"cost of bubblesort = "<<cost<<endl;
    printarr(array, arrsize);
    cout << endl<<"vector time"<<endl;

    vector<int> mergevector;
    int vecsize = 1000;
    for(int i = 0; i < vecsize; i++){
        mergevector.push_back(rand()% 10000);
    }
    printvector(mergevector);
    Mergesort(mergevector, 0, mergevector.size()-1);


    return 0;

}
