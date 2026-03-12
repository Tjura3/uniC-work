//this is just going to be the second verse, same as the first, im honestly already sick of this class because I have to take it again which is very unfortunate cause the professer seems so much better then murat.
#include <iostream>
#include <string>
using namespace std;
bool isPalindrome(const std::string& s);
int main(){
    string playerinput;
    cin >> playerinput;
    cout << ((isPalindrome(playerinput)) ? "True" : "False") << endl;
    
    return 0;
}

bool isPalindrome(const std::string& s){ //using the address means it sets it to read only at that address rather then creating a new instance. passing by refrence.
    int left = 0;
    int right = s.size()-1;
    while(left<right){
        if(s[left]!=s[right]){
            return false;
        }
        left++;
        right--;
    }
    return true;
}