//empirical analysis of searching alysis of searching algorithems
//linearsearch, binarysearch, and binarysearchrecusrive
//estimate various preformances on arrays of intefers of various sizes
//  2^10, 2^13, 2^16, 2^19, 2^22
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
int LinearSearch(vector<int>& arr, int key);
int BinarySearch(vector<int>& arr, int key);
int BinarySearchRecusrive(vector<int> &arr, int low, int high, int key);

int main(){
    
}
int LinearSearch(vector<int> &arr, int key){
    for(int i : arr){
        if(i == key){
            return i;
        }
    }
    return -1;
}
int binarySearch(vector<int> &arr, int key) {
    int low = 0;
    int high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        // Check if x is present at mid
        if (arr[mid] == key)
            return mid;
        // If x greater, ignore left half
        if (arr[mid] < key)
            low = mid + 1;
        // If x is smaller, ignore right half
        else
            high = mid - 1;
    }
    // If we reach here, then element was not present
    return -1;
}
int BinarySearchRecusrive(vector<int> &arr, int low, int high, int key) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        // If the element is present at the middle
        // itself
        if (arr[mid] == key)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > key)
            return BinarySearchRecusrive(arr, low, mid - 1, key);

        // Else the element can only be present
        // in right subarray
        return BinarySearchRecusrive(arr, mid + 1, high, key);
    }
  return -1;
}