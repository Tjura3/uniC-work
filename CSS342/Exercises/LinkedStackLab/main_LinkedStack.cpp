#include <iostream>
// #include <vector>
#include "stack.h"
using namespace std;
using namespace linkedstack;
// template <typename E>
// void reverse(vector<E>& V) { // reverse a vector
// LinkedStack<E> S(V.size());
// for (int i = 0; i < V.size(); i++){ // push elements onto stack
// S.push(V[i]);
// for (int i = 0; i < V.size(); i++) { // pop them in reverse order
// V[i] = S.top(); S.pop();
// }
// }
// }
void reverse(int *arr, int n)
{ // reverse a vector
    LinkedStack<int> S;
    for (int i = 0; i < n; i++)
    { // push elements onto stack
        S.push(*(arr + i));
    }
    for (int i = 0; i < n; i++)
    { // pop them in reverse order
        *(arr + i) = S.top();
        S.pop();
    }
}
int main()
{
    int V[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = 10;
    for (int i = 0; i < n; i++)
    {
        cout << *(V + i) << " ";
    }
    cout << endl;
    reverse(V, n);
    for (int i = 0; i < n; i++)
    {
        cout << *(V + i) << " ";
    }
    cout << endl;
    return 0;
}
