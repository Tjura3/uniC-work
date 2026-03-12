#include <iostream>
using namespace std;

//int factorial(int a, int b);
/*
int factorial(int n){
    if (n==0){
        return 1;
    }
    else{
        return factorial(n , n-1); //why is this not choosing the right overload?
    }
}
int factorial(int a, int b){
    if(b==0){
        return 1;
    }
    else{
        return a * factorial(b, b-1);
    }
}
*/

int factorial(int n){
    if(n==0){
        return 1;
    }
    else return n * factorial(n-1);
}

int factorialtail(int n, int total = 1){
    if(n == 0) return total;
    n--;
    return factorialtail(n , n * total);
}

int main(){

    int a;
    cin >> a;
    cout << factorial(a) << endl;

    int b;
    cout << "tail recursion" << endl;
    cin >> b;
    cout << factorialtail(b) << endl;
    cout << "got to here" << endl;
    return 0;
}