#include <iostream>
#include <vector>
using namespace std;



//returns the location of an element
int bsearchlocal(vector<int>& arr, int x){
    int cost = 2;
    int low = 0;
    int high = arr.size()-1;
    while(low <= high){
        cost++;
        int mid = low + (high - low)/2;
        
        if(arr[mid] == x){
            cout <<"Cost: " << cost << endl;
            return mid;
        }
        if(arr[mid] < x){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    cout <<"Cost: " << cost << endl;
    return -1;
}
int binarygameCPU(){
    int cost = 0;
    srand(time(0));
    cout << "Number guessing game" << endl;
    

    int awnser = (rand() % 1024)+ 1; //between 1 and 1024
    
    int low = 1;
    int high = 1024;
    int usernum = -1;
    while(usernum != awnser){
        cost++;
        usernum = low + (high - low)/2;
        if(usernum == awnser){
            cout << "guessing " << usernum << ", Correct!!" << endl;
        }
        else if(usernum < awnser){
            cout << "guessing " << usernum << ", Too small!" << endl;
            low = usernum + 1;
        }else{
            cout << "guessing " << usernum << ", Too big!" << endl;
            high = usernum - 1;
        }
    }
    cout << "Guessed in " << cost << endl;
    return cost;
}

int binarygame(){
    int cost = 0;
    srand(time(0));
    cout << "Number guessing game" << endl;
    int awnser = (rand() % 1024)+1;
    int usernum;
    while(usernum != awnser){
        cost++;
        cin >> usernum;
        if(usernum == awnser){
            cout << "Correct!" << endl;
        }
        else if(usernum > awnser){
            cout << "Too big!" << endl;
        }else{
            cout << "Too small!" << endl;
        }
    }
    return cost;
}

int main(){
    //vector<int> a = {2, 4, 6, 10, 20, 21, 30,50, 70, 77, 80, 92, 100};
    vector<int> a;
    for(int i = 0; i < 100000; i++){ //0 - 99999
        a.push_back(i);
    }
    
    cout << a.size() << endl;
    
    cout << bsearchlocal(a, 463) << endl;
    
    /*int guess = rand() % 100000; //random between 0 and 99999
    int input;
    while(input != guess){
        cout << "guess a number: ";
        cin >> input; cout << endl;

        
    }*/
    int userguess = binarygame();
    int compguess = binarygameCPU();
    cout << "User guessed in "<< userguess << endl;
    cout << "Computer guessed in " << compguess << endl;
    



    return 0;
}