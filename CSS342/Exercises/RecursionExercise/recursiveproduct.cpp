#include <iostream>
using namespace std;

int product(int ad, int sub){
    if (ad == 0 || sub == 0) return 0; //is zero if multiply by zero
    if (ad < sub){ //checks what is bigger in case for efficiency
        return sub + product(sub, ad-1);
    }else{
        if (sub == 0) return ad - ad;
        return ad + product(ad, sub-1);
    }
}

int main(){
    cout << "product test" << endl;
    cout << product(4,5) << endl;
    cout << product(3,7) << endl;
    cout << product(5,8) << endl;
    cout << product(4,0) << endl;

    return 0;
}