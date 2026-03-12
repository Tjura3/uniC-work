#include <iostream> 
#include <vector> 
using namespace std;

int BinarySearch(const vector<int>& arr, int target, int left, int right){
    
    if(left > right){
        return -1;
    }
    int mid = left + (right - left) / 2;
    if(arr.at(mid) == target) return mid;
    if(target > arr.at(mid)){
        return BinarySearch(arr, target, mid, right);
    } else return BinarySearch(arr, target, left, mid);
}

int main(){
    vector<int> vec;
    for(int i = 0; i < 200; i+=2){
        vec.push_back(i);
    }
    cout << vec.at(vec.size()-1) << endl << vec.size() << endl;
    cout << BinarySearch(vec, 172, 0, vec.size()-1) << endl;
    return 0;
}