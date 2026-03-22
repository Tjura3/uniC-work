#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;


// ------------------------------------------------------------
// swapValues
// ------------------------------------------------------------
// We implement our own swap function so that it is clear
// what happens during the swap.
//
// a and b are passed by reference so the values can change.
//
void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}


// ------------------------------------------------------------
// print helper
// ------------------------------------------------------------
void printVector(const vector<int>& nums) {
    for (int x : nums) {
        cout << x << " ";
    }
    cout << endl;
}


// ------------------------------------------------------------
// TODO 1: partitionOddEven
// ------------------------------------------------------------
//
// Rearrange the vector so that:
//
//   EVEN numbers go LEFT
//   ODD numbers go RIGHT
//
// Use the Lomuto-style pattern:
//
//   i = last index of even region
//   j scans from left to right
//
// When nums[j] is even:
//   i++
//   swap(nums[i], nums[j])
//
// ------------------------------------------------------------
void partitionOddEven(vector<int>& nums) {
    // TODO:
    int i = -1;
    for(int j = 0; j < nums.size(); j++){
        if((nums[j] % 2) != 1){
            i++;
            swapValues(nums[i], nums[j]);
        }
    }

}


// ------------------------------------------------------------
// isOddEvenPartitioned
// ------------------------------------------------------------
// This function verifies the required property:
//
//   [ EVEN EVEN EVEN ... EVEN | ODD ODD ODD ... ODD ]
//
// Once we start seeing odd numbers, we should never see
// an even number again.
//
bool isOddEvenPartitioned(const vector<int>& nums) {

    bool seenOdd = false;

    for (int x : nums) {

        // If we see an odd number,
        // we are now inside the odd section
        if (x % 2 != 0) {
            seenOdd = true;
        }

        // If we see an even number AFTER
        // we have already seen an odd number,
        // the partition is incorrect
        if (x % 2 == 0 && seenOdd) {
            return false;
        }
    }

    return true;
}


// ------------------------------------------------------------
// Lomuto partition helper for quickSelect
// ------------------------------------------------------------
// This is provided for you.
//
// It places the pivot into its final sorted position
// and returns the pivot index.
//
int partition(vector<int>& nums, int left, int right) {

    int pivot = nums[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {

        if (nums[j] <= pivot) {
            i++;
            swapValues(nums[i], nums[j]);
        }
    }

    swapValues(nums[i + 1], nums[right]);

    return i + 1;
}


// ------------------------------------------------------------
// TODO 2: quickSelectHelper
// ------------------------------------------------------------
//
// targetIndex is 0-based.
//
// Strategy:
//
//   1. Partition the vector
//   2. If pivotIndex == targetIndex, return nums[pivotIndex]
//   3. If targetIndex < pivotIndex, recurse only on the LEFT
//   4. Otherwise recurse only on the RIGHT
//
// This is why quickSelect is faster than sorting:
// it only explores ONE side each time.
//
int quickSelectHelper(vector<int>& nums, int left, int right, int targetIndex) {

    // TODO:
    // Implement the recursive quickselect logic
    
    if (left == right) {
        return nums[left];
    }
    int pivotIndex = partition(nums, left, right);
    
    if (pivotIndex == targetIndex) {
        return nums[pivotIndex];
    } else if (targetIndex < pivotIndex) {
        //only left recursion
        return quickSelectHelper(nums, left, pivotIndex - 1, targetIndex);
    } else {
        //only right recursion
        return quickSelectHelper(nums, pivotIndex + 1, right, targetIndex);
    }

}


// ------------------------------------------------------------
// quickSelect
// ------------------------------------------------------------
//
// k is 1-based:
//
//   k = 1 means smallest element
//   k = 2 means 2nd smallest
//   ...
//
// So:
//
//   targetIndex = k - 1
//
int quickSelect(vector<int>& nums, int k) {

    if (k < 1 || k > nums.size()) {
        throw invalid_argument("k is out of range.");
    }

    // TODO:
    // Finish the quickSelect function
    return quickSelectHelper(nums, 0, nums.size()-1, k-1);
}


// ------------------------------------------------------------
// main
// ------------------------------------------------------------
// This main function provides small tests for both problems.
// You should add more tests while developing.
//
int main() {

    cout << "===== Part 2 Partition Algorithms =====" << endl;
    cout << endl;

    vector<int> nums1 = {3, 2, 8, 5, 7, 4, 10, 11, 6, 1};

    cout << "Original vector for partitionOddEven:" << endl;
    printVector(nums1);

    partitionOddEven(nums1);

    cout << "After partitionOddEven:" << endl;
    printVector(nums1);

    if (isOddEvenPartitioned(nums1)) {
        cout << "Partition check passed." << endl;
    }
    else {
        cout << "Partition check failed." << endl;
    }

    cout << endl;

    vector<int> nums2 = {9, 4, 7, 1, 3, 6};
    int k = 4;

    cout << "Vector for quickSelect:" << endl;
    printVector(nums2);
    cout << "k = " << k << endl;

    int answer = quickSelect(nums2, k);

    cout << k << "rd smallest element = " << answer << endl;
    cout << "Expected answer = 6" << endl;

    cout << endl;

    return 0;
    
}