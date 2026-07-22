#include "bintree.h"
#include <fstream>
#include <chrono>

void loadcheck(const string& a, const string& b, const string& name){
    BinTree TA(Mode::AVL);
    BinTree TB(Mode::AVL);
    ifstream fa(a);
    ifstream fb(b);
    int val;
    while(fa >> val){
        TA.insert(val);
    }
    while(fb >> val){
        TB.insert(val);
    }
    int sizea = TA.size();
    int sizeb = TB.size();

    auto start = chrono::high_resolution_clock::now();
    TA.mergeWith(TB);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time = end - start;
    cout << name << endl;
    cout << "Time: " << time.count() << " ms" << endl;
    cout << "Auxbytes: " << TA.mergeAuxBytes() << endl;
    cout << "Size before (A, B): " << sizea << " " << sizeb << endl;
    cout << "Final size: " << TA.size() << endl << endl;
}

int main(){
    loadcheck("workloads/w1a.txt", "workloads/w1b.txt", "W1 equal");
    loadcheck("workloads/w2a.txt", "workloads/w2b.txt", "W2 tiny big");
    loadcheck("workloads/w3a.txt", "workloads/w3b.txt", "W3 overlap");
    loadcheck("workloads/w4a.txt", "workloads/w4b.txt", "W4 disjoint");
    return 0;
}