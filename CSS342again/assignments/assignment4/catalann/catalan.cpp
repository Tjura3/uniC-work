#include <iostream>
#include <cstdlib>
using namespace std;
//recursively call c(0)*c(2) O is 1, you need to break down a number
/*
𝐶(𝑛) = 𝑠𝑢𝑚(n-1/i=0) 𝐶(𝑖) ∗ 𝐶(𝑛 − 1 − 𝑖)
*/

int catalan(int n){
    if(n == 0) return 1;
    //can use for loops here, fix this later.   
    int i = 0;
    for(int k = 0; k < n; k++){
        i += catalan(k) * catalan(n - 1 - k);
    }
    return i;
}
int main(int argc, char* argv[]){
    if(argc > 2){
        cerr << "Too many arguments" << endl;
        return 1; 
    }
    int i;
    if(argc == 1){
        cout << "enter catalan ";
        cin >> i;
    }else{
        try{
            i = stoi(argv[1]);
        }catch(const exception& e){
            cerr << "Invalid integer entered" << endl;
            return 1;
        }
    }
    if (0 > i){
        cerr << "Error: n must be non-negative" << endl;
        return 1;
    }
    cout << catalan(i) << endl;
    return 0;
}