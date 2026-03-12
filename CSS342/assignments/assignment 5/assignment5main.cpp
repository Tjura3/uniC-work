//Thomas S Juranich
//Assignment 5
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>

using namespace std;
using namespace chrono;

void analyzeBubbleSort(int power);
void analyzeInsertionSort(int power);
void analyzeMergeSort(int power);
void analyzeQuickSort(int power);

void populateVectorOrdered(vector<int>& v, int s);
void populateVectorReverse(vector<int>& v, int s);
void populateVectorRandom(vector<int>& v, int s);

void bubbleSort(vector<int>& v);
void insertionSort(vector<int>& v);
void mergeSort(vector<int>& v, int left, int right);
void merge(vector<int>& v, int left, int mid, int right);
int partition(vector<int> &v, int low, int high);
void quickSort(vector<int> &v, int low, int high);

void printvector(vector<int>& v);

//evaluate from 12, 13, 14, 15, 16
//csv's are oganized like so:
//Case, Size, t1, t2, t3, t4, t5, Average
const int MAXR = 1000;
const int MINR = 0;
const int STARTFROM = 15;
int main(){
    srand(time(0));
    /*
    vector<int> a;
    populateVectorReverse(a, 15);
    printvector(a);
    mergeSort(a, 0, a.size()-1);
    printvector(a);
    */
    
    //for(int i = 0; i < 5; i++) analyzeBubbleSort(i+STARTFROM);
    //for(int i = 0; i < 5; i++) analyzeInsertionSort(i+STARTFROM);
    for(int i = 0; i < 5; i++) analyzeMergeSort(i+STARTFROM);
    //for(int i = 0; i < 5; i++) analyzeQuickSort(i+STARTFROM);
    
    
    return 0;
}

void analyzeBubbleSort(int power){
    
    vector<int> a;
    ofstream bubblefile("bubblesort.csv", ios::app);
    cout << "Evaluating Bubble Sort at size 2^" << power << endl;
    cout << "Evaluating ordered: ";
    bubblefile << "Ordered, " << power << ", ";
    int avg = 0;
    for(int i = 0; i < 5; i++){
        a.clear();
        populateVectorOrdered(a, pow(2, power));
        auto start = high_resolution_clock::now();
        bubbleSort(a);
        auto end = high_resolution_clock::now();
        auto microint = duration_cast<microseconds>(end - start);
        cout << microint.count() << "us, ";
        bubblefile << microint.count() << ", ";
        avg += microint.count();
    }
    bubblefile << avg/5 << endl;

    cout << endl << "Evaluating random: ";
    bubblefile << "Random, " << power << ", ";
    avg = 0;
    for(int i = 0; i < 5; i++){
        
        a.clear();
        populateVectorRandom(a, pow(2, power));
        auto start = high_resolution_clock::now();
        bubbleSort(a);
        auto end = high_resolution_clock::now();
        auto microint = duration_cast<microseconds>(end - start);
        cout << microint.count() << "us, ";
        bubblefile << microint.count() << ", ";
        avg += microint.count();
    }
    bubblefile << avg/5 << endl;

    cout << endl << "Evaluating reverse: ";
    bubblefile << "Reverse, " << power << ", ";
    avg = 0;
    for(int i = 0; i < 5; i++){
        a.clear();
        populateVectorReverse(a, pow(2, power));
        auto start = high_resolution_clock::now();
        bubbleSort(a);
        auto end = high_resolution_clock::now();
        auto microint = duration_cast<microseconds>(end - start);
        cout << microint.count() << "us, ";
        bubblefile << microint.count() << ", ";
        avg += microint.count();
    }
    bubblefile << avg/5 << endl;
    cout << endl << endl;
    bubblefile.close();
}
void analyzeInsertionSort(int power){
    vector<int> a;
    ofstream insertfile("insertsort.csv", ios::app);
    cout << "Evaluating Insertion Sort at size 2^" << power << endl;
    cout << "Evaluating ordered: ";
    insertfile << "Ordered, " << power << ", ";
    int avg = 0;
    for(int i = 0; i < 5; i++){
        a.clear();
        populateVectorOrdered(a, pow(2, power));
        auto start = high_resolution_clock::now();
        insertionSort(a);
        auto end = high_resolution_clock::now();
        auto microint = duration_cast<microseconds>(end - start);
        cout << microint.count() << "us, ";
        insertfile << microint.count() << ", ";
        avg += microint.count();
    }
    insertfile << avg/5 << endl;

    cout << endl << "Evaluating random: ";
    insertfile << "Random, " << power << ", ";
    avg = 0;
    for(int i = 0; i < 5; i++){
        
        a.clear();
        populateVectorRandom(a, pow(2, power));
        auto start = high_resolution_clock::now();
        insertionSort(a);
        auto end = high_resolution_clock::now();
        auto microint = duration_cast<microseconds>(end - start);
        cout << microint.count() << "us, ";
        insertfile << microint.count() << ", ";
        avg += microint.count();
    }
    insertfile << avg/5 << endl;

    cout << endl << "Evaluating reverse: ";
    insertfile << "Reverse, " << power << ", ";
    avg = 0;
    for(int i = 0; i < 5; i++){
        a.clear();
        populateVectorReverse(a, pow(2, power));
        auto start = high_resolution_clock::now();
        insertionSort(a);
        auto end = high_resolution_clock::now();
        auto microint = duration_cast<microseconds>(end - start);
        cout << microint.count() << "us, ";
        insertfile << microint.count() << ", ";
        avg += microint.count();
    }
    insertfile << avg/5 << endl;
    cout << endl << endl;
    insertfile.close();
}
void analyzeMergeSort(int power){
    //mergeSort(a, 0, a.size()-1);
    vector<int> a;
    ofstream mergefile("mergesort.csv", ios::app);
    cout << "Evaluating Merge Sort at size 2^" << power << endl;
    cout << "Evaluating ordered: ";
    mergefile << "Ordered, " << power << ", ";
    int avg = 0;
    for(int i = 0; i < 5; i++){
        a.clear();
        populateVectorOrdered(a, pow(2, power));
        auto start = high_resolution_clock::now();
        mergeSort(a, 0, a.size()-1);
        auto end = high_resolution_clock::now();
        auto microint = duration_cast<microseconds>(end - start);
        cout << microint.count() << "us, ";
        mergefile << microint.count() << ", ";
        avg += microint.count();
    }
    mergefile << avg/5 << endl;

    cout << endl << "Evaluating random: ";
    mergefile << "Random, " << power << ", ";
    avg = 0;
    for(int i = 0; i < 5; i++){
        
        a.clear();
        populateVectorRandom(a, pow(2, power));
        auto start = high_resolution_clock::now();
        mergeSort(a, 0, a.size()-1);
        auto end = high_resolution_clock::now();
        auto microint = duration_cast<microseconds>(end - start);
        cout << microint.count() << "us, ";
        mergefile << microint.count() << ", ";
        avg += microint.count();
    }
    mergefile << avg/5 << endl;

    cout << endl << "Evaluating reverse: ";
    mergefile << "Reverse, " << power << ", ";
    avg = 0;
    for(int i = 0; i < 5; i++){
        a.clear();
        populateVectorReverse(a, pow(2, power));
        auto start = high_resolution_clock::now();
        mergeSort(a, 0, a.size()-1);
        auto end = high_resolution_clock::now();
        auto microint = duration_cast<microseconds>(end - start);
        cout << microint.count() << "us, ";
        mergefile << microint.count() << ", ";
        avg += microint.count();
    }
    mergefile << avg/5 << endl;
    cout << endl << endl;
    mergefile.close();
}
void analyzeQuickSort(int power){
    //quickSort(a, 0, a.size()-1);
    int p = power;
    vector<int> a;
    ofstream quickfile("quicksort.csv", ios::app);
    quickfile << "Ordered, " << power << ", ";
    int avg = 0;
    cout << "Evaluating Quick Sort at size 2^" << p << endl;
    cout << "Evaluating ordered: ";
    for(int i = 0; i < 5; i++){
        a.clear();
        populateVectorOrdered(a, pow(2, p));
        auto start = high_resolution_clock::now();
        quickSort(a, 0, a.size()-1);
        auto end = high_resolution_clock::now();
        auto microint = duration_cast<microseconds>(end - start);
        cout << microint.count() << "us, ";
        quickfile << microint.count() << ", ";
        avg += microint.count();
    }
    quickfile << avg/5 << endl;

    cout << endl << "Evaluating random: ";
    quickfile << "Random, " << power << ", ";
    avg = 0;
    for(int i = 0; i < 5; i++){
        
        a.clear();
        populateVectorRandom(a, pow(2, p));
        auto start = high_resolution_clock::now();
        quickSort(a, 0, a.size()-1);
        auto end = high_resolution_clock::now();
        auto microint = duration_cast<microseconds>(end - start);
        cout << microint.count() << "us, ";
        quickfile << microint.count() << ", ";
        avg += microint.count();
    }
    quickfile << avg/5 << endl;

    cout << endl << "Evaluating reverse: ";
    quickfile << "Reverse, " << power << ", ";
    avg = 0;
    for(int i = 0; i < 5; i++){
        a.clear();
        populateVectorReverse(a, pow(2, p));
        auto start = high_resolution_clock::now();
        quickSort(a, 0, a.size()-1);
        auto end = high_resolution_clock::now();
        auto microint = duration_cast<microseconds>(end - start);
        cout << microint.count() << "us, ";
        quickfile << microint.count() << ", ";
        avg += microint.count();
    }
    quickfile << avg/5 << endl;
    cout << endl << endl;
    quickfile.close();
}

//takes the vector, and the size of the desired vector
void populateVectorOrdered(vector<int>& v, int s){
    for(int i = 0; i < s; i++){
        v.push_back(i);
    }
}
void populateVectorReverse(vector<int>& v, int s){
    for(int i = 0; i < s; i++){
        v.push_back(s-i);
    }
}
void populateVectorRandom(vector<int>& v, int s){
    for(int i = 0; i < s; i++){
        v.push_back(rand() % (MAXR - MINR + 1) + MINR);
    }
}


void bubbleSort(vector<int>& v){
    int n = v.size();
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}
void insertionSort(vector<int>& v){
    int n = v.size();
    for (int i = 1; i < n; i++) {
        int key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = key;
    }
}
//used https://www.geeksforgeeks.org/dsa/merge-sort/ to help me build this 
void merge(vector<int>& v, int left, int mid, int right){
    //size of vectors                   
    int size1 = mid - left + 1;
    int size2 = right - mid;
    //temp vectors
    vector<int> L(size1);
    vector<int> R(size2);
    //Copy data to temp vectors L and R
    for (int i = 0; i < size1; i++)   L[i] = v[left + i];
    for (int j = 0; j < size2; j++)   R[j] = v[mid + 1 + j];
    //iterator into values
    int i = 0;
    int j = 0;
    int k = left;

    // Merge the temp vectors back into single array
    while (i < size1 && j < size2) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            i++;
        }
        else {
            v[k] = R[j];
            j++;
        }
        k++;
    }
    // Copy the remaining elements into the vector
    while (i < size1) {
        v[k] = L[i];
        i++;
        k++;
    }
    while (j < size2) {
        v[k] = R[j];
        j++;
        k++;
    }
}
/**
 * mergeA is a more efficient version of merge.
 */
void mergeA(vector<int>& v, int left, int mid, int right){
    //range of vector to sort                   
    int size1 = mid - left + 1;
    int size2 = right - mid;
    //temp vector
    vector<int> temp(size1+size2);
    
    
    int i = 0;
    int j = 0;
    int k = 0;

    //sort from origional vector to temp vector
    while (i < size1 && j < size2) {
        if (v[i+left] <= v[j+mid+1]) {
            temp[k] = v[i+left];
            i++;
        }
        else {
            temp[k] = v[j+mid+1];
            j++;
        }
        k++;
    }
    // Copy elements into vector
    while (i < size1) {
        temp[k] = v[i+left];
        i++;
        k++;
    }
    while (j < size2) {
        temp[k] = v[j+mid+1];
        j++;
        k++;
    }
    //overwrite origional vector with temp
    for(int l = 0; l < temp.size(); l++){
        v[left+l] = temp[l];
        
    }
}
void mergeSort(vector<int>& v, int left, int right){
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(v, left, mid);
    mergeSort(v, mid + 1, right);
    mergeA(v, left, mid, right);
}
//used https://www.geeksforgeeks.org/cpp/cpp-program-for-quicksort/  to help me build this
int partition(vector<int> &v, int low, int high) {

    //last element as pivot
    int pivot = v[high];

    // Index of elemment just before the last element used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        // If element is less or equal to pivot
        if (v[j] <= pivot) {
            i++;
            swap(v[i], v[j]);
        }
    }

    // Put pivot to its position
    swap(v[i + 1], v[high]);

    // Return the point of partition
    return (i + 1);
}
void quickSort(vector<int> &v, int low, int high) {
    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        int pi = partition(v, low, high);

        // Separately sort elements before and after the
        // Partition Index pi
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

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
