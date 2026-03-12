#include <iostream>
#include <vector>

using namespace std;

void printvector(vector<int>& v){
    int b = 0;
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
        b++;
        if(b == 10){
            cout << endl;
            b = 0;
        }
    }
    cout << endl;
}

int main(){
    vector<int> v;
    for(int i = 0; i < 20; i++){
        v.push_back(i);
        cout << v.size() << " " << v.capacity() << " " << &v[0] << endl; 
    }
    return 0;
}