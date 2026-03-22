#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// ============================================================
// CSS342 Assignment 5 - Part 1
// Sorting Analysis: MergeSort vs QuickSort
// ============================================================
//
// OVERVIEW
// --------
// In this file you will analyze:
//
//   1. mergeSort
//   2. quickSortLastPivot
//   3. quickSortMedianThree
//
// The purpose of this part is to help you observe:
//
//   - how quicksort can degenerate on sorted input
//   - how recursion depth changes in good and bad cases
//   - how choosing a better pivot can improve performance
//
// ------------------------------------------------------------
// WHAT IS ALREADY PROVIDED
// ------------------------------------------------------------
//
//   - mergeSort
//   - quickSortLastPivot
//   - helper functions for generating test vectors
//   - automatic timing
//   - automatic table formatting
//
// ------------------------------------------------------------
// WHAT YOU MUST DO
// ------------------------------------------------------------
//
// TODO 1:
//   Implement medianOfThreeIndex
//
// TODO 2:
//   Implement partitionMedianThree
//
// TODO 3:
//   Implement quickSortMedianThreeHelper
//
// TODO 4:
//   Implement quickSortMedianThree
//
// ------------------------------------------------------------
// EXPERIMENTS YOU MUST RUN
// ------------------------------------------------------------
//
// You should test all three sorting algorithms on:
//
//   - random vectors
//   - sorted vectors
//   - reverse-sorted vectors
//   - nearly-sorted vectors
//
// You should test multiple sizes, for example:
//
//   - 10000
//   - 50000
//   - 100000
//
// ------------------------------------------------------------
// WHAT TO RECORD IN YOUR REPORT
// ------------------------------------------------------------
//
// For each run, record:
//
//   - algorithm name
//   - input type
//   - vector size
//   - runtime in milliseconds
//   - maximum recursion depth for quicksort
//
// mergeSort does not need recursion depth in this assignment.
// You may record "N/A" for mergeSort.
//
// ------------------------------------------------------------
// RECURSION DEPTH
// ------------------------------------------------------------
//
// For quicksort, recursion depth means:
//
//   how many active quicksort calls exist along one path
//   from the original call down to a base case
//
// We will track it like this:
//
//   - the first quicksort call has depth 1
//   - each recursive child call has depth + 1
//   - maxDepth stores the largest depth ever reached
//
// Balanced quicksort produces smaller depth.
// Degenerate quicksort produces much larger depth.
//
// ------------------------------------------------------------
// REQUIRED OUTPUT FORMAT
// ------------------------------------------------------------
//
// Your program should print rows in this format:
//
// Algorithm             Input           Size      Time(ms)    MaxDepth
// ---------------------------------------------------------------------
// mergeSort             random          10000     2.10        N/A
// quickSortLastPivot    random          10000     1.70        22
// quickSortMedianThree  random          10000     1.55        18
//
// This starter code already prints the table for you.
//
// ============================================================


// ------------------------------------------------------------
// swapValues
// ------------------------------------------------------------
// We implement our own swap function so that it is clear
// what happens during the swap.
//
void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}


// ------------------------------------------------------------
// Correctness check
// ------------------------------------------------------------
// We use this to verify that your sorting algorithm still works
// after you modify it.
//
bool isSorted(const vector<int>& nums) {
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i - 1] > nums[i]) {
            return false;
        }
    }
    return true;
}


// ------------------------------------------------------------
// Input generators
// ------------------------------------------------------------
// These functions create the different kinds of test vectors
// you will use in your experiments.
//
vector<int> makeRandomVector(int size) {
    vector<int> nums(size);

    for (int i = 0; i < size; i++) {
        nums[i] = rand();
    }

    return nums;
}

vector<int> makeSortedVector(int size) {
    vector<int> nums(size);

    for (int i = 0; i < size; i++) {
        nums[i] = i;
    }

    return nums;
}

vector<int> makeReverseSortedVector(int size) {
    vector<int> nums(size);

    for (int i = 0; i < size; i++) {
        nums[i] = size - i;
    }

    return nums;
}

vector<int> makeNearlySortedVector(int size, int swapCount) {
    vector<int> nums = makeSortedVector(size);

    for (int i = 0; i < swapCount; i++) {
        int a = rand() % size;
        int b = rand() % size;
        swapValues(nums[a], nums[b]);
    }

    return nums;
}


// ------------------------------------------------------------
// mergeSort
// ------------------------------------------------------------
// This implementation is provided for you.
// You do not need to change it.
//
void merge(vector<int>& nums, int left, int mid, int right) {
    vector<int> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            temp.push_back(nums[i]);
            i++;
        }
        else {
            temp.push_back(nums[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(nums[i]);
        i++;
    }

    while (j <= right) {
        temp.push_back(nums[j]);
        j++;
    }

    for (int k = 0; k < temp.size(); k++) {
        nums[left + k] = temp[k];
    }
}

void mergeSortHelper(vector<int>& nums, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSortHelper(nums, left, mid);
    mergeSortHelper(nums, mid + 1, right);

    merge(nums, left, mid, right);
}

void mergeSort(vector<int>& nums) {
    if (nums.empty()) {
        return;
    }

    mergeSortHelper(nums, 0, nums.size() - 1);
}


// ------------------------------------------------------------
// quickSort using LAST ELEMENT as pivot
// ------------------------------------------------------------
// This implementation is also provided for you.
//
// It uses the Lomuto partition style taught in class:
// We also track recursion depth using:
//   depth
//   maxDepth
//
int partitionLastPivot(vector<int>& nums, int left, int right) {
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

void quickSortLastPivotHelper(
    vector<int>& nums,
    int left,
    int right,
    int depth,
    int& maxDepth) {

    if (depth > maxDepth) {
        maxDepth = depth;
    }

    if (left >= right) {
        return;
    }

    int pivotIndex = partitionLastPivot(nums, left, right);

    quickSortLastPivotHelper(nums, left, pivotIndex - 1, depth + 1, maxDepth);
    quickSortLastPivotHelper(nums, pivotIndex + 1, right, depth + 1, maxDepth);
}

void quickSortLastPivot(vector<int>& nums, int& maxDepth) {
    maxDepth = 0;

    if (nums.empty()) {
        return;
    }

    quickSortLastPivotHelper(nums, 0, nums.size() - 1, 1, maxDepth);
}


// ------------------------------------------------------------
// TODO 1: medianOfThreeIndex
// ------------------------------------------------------------
//
// Return the index of the median value among:
//
//   nums[left], nums[mid], nums[right]
//
// where:
//
//   mid = left + (right - left) / 2
//
// Example:
//
//   values = 9, 3, 7
//   median value = 7
//   return the index of 7
//
// This function does NOT rearrange the vector.
// It only returns which index should be used as the pivot.
//
int medianOfThreeIndex(const vector<int>& nums, int left, int right) {
    int mid = left + (right - left) / 2;
    
    // TODO: implement this function
    int a = nums[left];
    int b = nums[mid];
    int c = nums[right];
    //if element is in between
    if((b <= a && a <= c) || (c <= a && a <= b)) return left;
    if((a <= c && c <= b) || (b <= c && c <= a)) return right;
    return mid;
}


// ------------------------------------------------------------
// TODO 2: partitionMedianThree
// ------------------------------------------------------------
//
// This should work similarly to partitionLastPivot, except:
//
//   1. first choose the pivot using medianOfThreeIndex
//   2. swap that pivot into nums[right]
//   3. then run the SAME Lomuto partition logic
//
// In other words:
//
//   pick better pivot -> move it to end -> partition
//
int partitionMedianThree(vector<int>& nums, int left, int right) {
    // TODO: implement this function
    int pivot = medianOfThreeIndex(nums, left, right);
    swapValues(nums[pivot], nums[right]);
    //recycle pivot to now hold the number at nums[right]
    pivot = nums[right];
    int i = left - 1;

    for(int j = left; j < right; j++){
        if(nums[j] <= pivot){
            i++;
            swapValues(nums[i], nums[j]);
        }
    }
    //because right is the index, that means j stops right before the number to pivot.

    swapValues(nums[i+1], nums[right]);
    return i + 1;
}


// ------------------------------------------------------------
// TODO 3: quickSortMedianThreeHelper
// ------------------------------------------------------------
//
// This should work just like quickSortLastPivotHelper,
// except it should call partitionMedianThree instead of
// partitionLastPivot.
//
// Remember to:
//
//   - update maxDepth
//   - stop when left >= right
//   - recurse on left and right parts
//
void quickSortMedianThreeHelper(
    vector<int>& nums,
    int left,
    int right,
    int depth,
    int& maxDepth) {
        

    // TODO: implement this function
    if(depth > maxDepth){
        maxDepth = depth;
    }
    if(left >= right){
        return;
    }
    int pivotIndex = partitionMedianThree(nums, left, right);
    quickSortMedianThreeHelper(nums, left, pivotIndex - 1, depth + 1, maxDepth);
    quickSortMedianThreeHelper(nums, pivotIndex + 1, right, depth + 1, maxDepth);
}


// ------------------------------------------------------------
// TODO 4: quickSortMedianThree
// ------------------------------------------------------------
//
// This should work just like quickSortLastPivot:
//
//   - reset maxDepth to 0
//   - return immediately if vector is empty
//   - call quickSortMedianThreeHelper with starting depth 1
//
void quickSortMedianThree(vector<int>& nums, int& maxDepth) {
    maxDepth = 0;

    if (nums.empty()) {
        return;
    }

    // TODO: call helper here
    quickSortMedianThreeHelper(nums, 0, nums.size() - 1, 1, maxDepth);
}


// ------------------------------------------------------------
// Table printing helper
// ------------------------------------------------------------
// This formats one row of output so that every student's
// program prints the same style of table.
//
void printRow(
    string algorithm,
    string input,
    int size,
    double time,
    string depth) {

    cout << left
         << setw(22) << algorithm
         << setw(16) << input
         << setw(10) << size
         << setw(12) << fixed << setprecision(2) << time
         << depth
         << endl;
}


// ------------------------------------------------------------
// Experiment runners
// ------------------------------------------------------------
// These functions:
//
//   - make a copy of the original vector
//   - run the sort
//   - measure time
//   - print one formatted table row
//
void runMergeExperiment(string inputType, vector<int> data) {
    vector<int> nums = data;

    auto start = chrono::high_resolution_clock::now();
    mergeSort(nums);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = end - start;

    if (!isSorted(nums)) {
        cout << "ERROR: mergeSort did not sort correctly." << endl;
    }

    printRow("mergeSort", inputType, nums.size(), elapsed.count(), "N/A");
}

void runQuickExperiment(
    string algorithmName,
    string inputType,
    vector<int> data,
    void (*sortFunc)(vector<int>&, int&)) {

    vector<int> nums = data;
    int maxDepth = 0;

    auto start = chrono::high_resolution_clock::now();
    sortFunc(nums, maxDepth);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = end - start;

    if (!isSorted(nums)) {
        cout << "ERROR: " << algorithmName << " did not sort correctly." << endl;
    }

    printRow(algorithmName, inputType, nums.size(), elapsed.count(), to_string(maxDepth));
}


// ------------------------------------------------------------
// main
// ------------------------------------------------------------
//
// INSTRUCTIONS:
//   1. Change size below and rerun experiments.
//   2. Record the table results in your report.
//   3. You should test multiple sizes.
//
// Suggested sizes:
//   10000
//   50000
//   100000
//
int main() {
    srand(42);

    int size = 100000;

    vector<int> randomData = makeRandomVector(size);
    vector<int> sortedData = makeSortedVector(size);
    vector<int> reverseData = makeReverseSortedVector(size);
    vector<int> nearlyData = makeNearlySortedVector(size, 10);

    cout << endl;
    cout << "Algorithm             Input           Size      Time(ms)    MaxDepth\n";
    cout << "---------------------------------------------------------------------\n";

    runMergeExperiment("random", randomData);
    runQuickExperiment("quickSortLastPivot", "random", randomData, quickSortLastPivot);
    runQuickExperiment("quickSortMedianThree", "random", randomData, quickSortMedianThree);

    runMergeExperiment("sorted", sortedData);
    runQuickExperiment("quickSortLastPivot", "sorted", sortedData, quickSortLastPivot);
    runQuickExperiment("quickSortMedianThree", "sorted", sortedData, quickSortMedianThree);

    runMergeExperiment("reverse", reverseData);
    runQuickExperiment("quickSortLastPivot", "reverse", reverseData, quickSortLastPivot);
    runQuickExperiment("quickSortMedianThree", "reverse", reverseData, quickSortMedianThree);

    runMergeExperiment("nearly", nearlyData);
    runQuickExperiment("quickSortLastPivot", "nearly", nearlyData, quickSortLastPivot);
    runQuickExperiment("quickSortMedianThree", "nearly", nearlyData, quickSortMedianThree);

    cout << endl;

    return 0;
}