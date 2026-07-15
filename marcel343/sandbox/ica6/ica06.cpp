// CSS 343 · ICA 06 — binary heaps.  Fill in the TODOs, then run the application.
//
//   build:        g++ -std=c++17 -g -o ica06 ica06.cpp
//   run:          ./ica06
//   leak-check:   valgrind --leak-check=full ./ica06     (ICA 06 IS LEAK-GRADED)
//
// The MinHeap struct, insert and delMin (which USE swim and sink), and main()
// (a unit-test battery + heapsort application) are GIVEN — do not edit them.
// You implement FOUR primitives: swim, sink, heapify, and heapsort. 1-indexed
// array: a[0] is an unused sentinel, so parent(k)=k/2, children 2k and 2k+1.
// Run early and often: the tests report [PASS]/[FAIL] one by one.

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

struct MinHeap {
    vector<int> a;                          // 1-indexed: a[0] unused
    MinHeap() { a.push_back(0); }           // sentinel at index 0
    int  size()  const { return (int)a.size() - 1; }
    bool empty() const { return size() == 0; }
    int  min()   const { return a[1]; }     // precondition: non-empty
};

// ---- TODO 1 — swim -------------------------------------------------------
// Restore the heap after appending: while node k is SMALLER than its parent
// (index k/2), swap up. Stop at the root or when the parent dominates.
void swim(MinHeap& h, int k) {
    // TODO: while k is not the root (k > 1) AND a[k] < its parent a[k/2],
    //       swap them and move k up to k/2.

    //while k, the heaps position isn't root (index 1)
    //and the parent (k/2) is greater than the child (k)
    //swap the values at the positions,
    //and set the position the value we are now evaluating
    //to the parent that it just swapped with
    while(k > 1 && h.a[k/2] > h.a[k]){ 
        swap(h.a[k/2], h.a[k]); 
        k = k/2;
    }
}

// ---- TODO 2 — sink -------------------------------------------------------
// Restore the heap after replacing the root: while node k is LARGER than a
// child, swap with the SMALLER child. Stop at a leaf or when k dominates both.
void sink(MinHeap& h, int k) {
    // TODO: let n = h.size(); while node k has a left child (2k <= n): pick
    //       the SMALLER of its children; if a[k] <= that child, stop; else swap
    //       a[k] with it and move k down to that child.


    while(2*k <= h.size()){ 
        //we check if the node we are on has slots for children,
        //if outside of the array's bounds, we quit the loop.
        int j = 2*k; 
        //the left child

        if(j < h.size() && h.a[j] > h.a[j+1]){
            //if there is a right child within the bounds,
            //check if the right child is smaller
            //if so, increment j so we are working with the right child
            //because we are trying to bring the smaller number up as we sink
            j++;
        }
        if(h.a[k] <= h.a[j]) break;
        swap(h.a[k], h.a[j]);
        k = j;
    }
}

// ---- TODO 3 — heapify ----------------------------------------------------
// Build a heap from a RAW array in Θ(n): load the data (a complete tree, not
// yet a heap), then sink every internal node from n/2 down to 1 (bottom-up).
void heapify(MinHeap& h, const vector<int>& data) {
    // TODO: reset h.a to just the sentinel (h.a.resize(1)); push each value of
    //       `data`; then for k = size()/2 down to 1, sink(h, k).
    
    //I think I understand it now, we are resizing the vector,
    //then pushing the data,
    //(I wonder if there is a faster way to do this rather than building the array first)
    //and sinking from halfway and up because only children exist beyond the halfway point I think
    //actually nevermind the todo tells me what to do.
    h.a.resize(1);
    for(int dat : data) h.a.push_back(dat);
    for(int k = h.size()/2; k > 0; k--){
        sink(h, k);
    }
}

// ---- TODO 4 — heapsort ----------------------------------------------------
// Sort `data` ASCENDING, IN PLACE, using only this heap's primitives: heapify
// the data, then repeatedly swap the root (the current min) with the LAST
// element of the shrinking active range, and sink the new root within that
// smaller range — the same mechanical pattern as a max-heap's heapsort. On a
// MIN-heap this places the SMALLEST value last, next-smallest second-to-last,
// and so on, leaving the array DESCENDING; reverse it in place at the end
// (O(1) extra space) to get ascending. Note: sink(h,k) always bounds itself by
// h.size() (the FULL vector) — reusing it here would sink past the tail
// you've already placed, so do the shrinking-range sink inline instead.
vector<int> heapsort(const vector<int>& data) {
    // TODO: heapify(h, data) into a local MinHeap h; then repeatedly, for a
    //       shrinking `end` from h.size() down to 2: swap h.a[1] with h.a[end],
    //       decrement end, then sink node 1 but bounded by `end` (not h.size())
    //       — do NOT call sink(h,1) directly, write the bounded version inline.
    //       Finally build vector<int>(h.a.begin()+1, h.a.end()) and reverse it.
    //       Do NOT just call delMin() in a loop and collect into a new vector:
    //       that is O(n) extra space, not the in-place algorithm above.
    
    MinHeap h;
    heapify(h, data);
    for(int e = h.size(); e >= 2; e--){
        swap(h.a[1], h.a[e]);
        int k = 1;
        int rsize = e-1;

        while(2*k <= rsize){ //copying sink but like for the active size
            int j = 2*k;
            if(j < rsize && h.a[j] > h.a[j+1]){
                j++;
            }
            if(h.a[k] <= h.a[j]) break;
            swap(h.a[k], h.a[j]);
            k = j;
        }
    }
    
    vector<int> res(h.a.begin() + 1, h.a.end());
    //im so tired from work I just wanna cry at this pointtt
    //ahh shoot I was supposed to sort it in ascending
    reverse(res.begin(), res.end());
    return res;
}

// ---- GIVEN — insert and delMin use your primitives -----------------------
void insert(MinHeap& h, int x) {
    h.a.push_back(x);                        // append (keeps the tree complete)
    swim(h, h.size());                       // restore heap order
}
int delMin(MinHeap& h) {
    int mn = h.a[1];                         // the min is the root
    swap(h.a[1], h.a[h.size()]);             // move last element to the root
    h.a.pop_back();                          // remove the old min
    if (!h.empty()) sink(h, 1);              // restore heap order
    return mn;
}

// ==========================================================================
// UNIT TESTS + APPLICATION (given — do not edit).
// ==========================================================================
#ifndef ICA06_GRADER
static int passCnt = 0, failCnt = 0;
static void check(bool ok, const string& what) {
    (ok ? passCnt : failCnt)++;
    cout << (ok ? "  [PASS] " : "  [FAIL] ") << what << '\n';
}
static bool isHeap(const MinHeap& h) {            // every parent <= its children
    for (int k = 2; k <= h.size(); k++)
        if (h.a[k / 2] > h.a[k]) return false;
    return true;
}
static bool ascending(const vector<int>& v) { return is_sorted(v.begin(), v.end()); }
static vector<int> drainMin(MinHeap h) {          // delMin until empty (by value → copy)
    vector<int> out; while (!h.empty()) out.push_back(delMin(h)); return out;
}

int main() {
    cout << "T1 · insert (swim)\n";
    MinHeap h;
    for (int x : {30, 90, 20, 70, 10, 95, 50}) insert(h, x);
    check(h.size() == 7, "7 inserts → size 7");
    check(h.min() == 10, "min() is 10 (the root)");
    check(isHeap(h), "heap property holds after inserts");

    cout << "T2 · delMin (sink) returns items smallest-first\n";
    vector<int> out = drainMin(h);
    check((int)out.size() == 7 && out.front() == 10 && out.back() == 95, "7 removed, 10 first, 95 last");
    check(ascending(out), "delMin yields strictly ascending order");

    cout << "T3 · heapify a shuffled array (bottom-up, Θ(n))\n";
    MinHeap g; heapify(g, {30, 60, 50, 90, 85, 40, 70, 45, 20, 95, 10, 15});
    check(g.size() == 12, "all 12 keys loaded");
    check(isHeap(g), "heapify produced a valid heap");
    check(!g.empty() && g.min() == 10, "min() is 10");
    vector<int> gs = drainMin(g);
    check((int)gs.size() == 12 && ascending(gs), "the heapified heap drains ascending");

    cout << "T4 · heapify vs. repeated insert — same heap contents\n";
    vector<int> data = {8, 3, 5, 1, 9, 2, 7, 4, 6, 0};
    MinHeap byInsert; for (int x : data) insert(byInsert, x);
    MinHeap byHeapify; heapify(byHeapify, data);
    check(isHeap(byInsert) && isHeap(byHeapify), "both are valid heaps");
    check(drainMin(byInsert) == drainMin(byHeapify), "both drain to the same sequence");

    cout << "T5 · heapify descending input (worst case for a min-heap)\n";
    vector<int> desc(10); iota(desc.begin(), desc.end(), 1);
    reverse(desc.begin(), desc.end());        // 10..1 (looks like a max-heap)
    MinHeap m; heapify(m, desc);
    check(isHeap(m) && !m.empty() && m.min() == 1, "descending input heapifies correctly, min = 1");

    cout << "T6 · heapsort — in place, ascending\n";
    vector<int> unsorted = {8, 3, 5, 1, 9, 2, 7, 4, 6, 0};
    vector<int> sorted6 = heapsort(unsorted);
    check((int)sorted6.size() == 10, "heapsort returns all 10 elements");
    check(ascending(sorted6), "heapsort result is ascending");
    check(sorted6.front() == 0 && sorted6.back() == 9, "first is 0, last is 9");
    vector<int> want6 = unsorted; sort(want6.begin(), want6.end());
    check(sorted6 == want6, "heapsort matches std::sort on the same input");

    cout << "T7 · heapsort a large batch (2047 keys)\n";
    const int N = 2047;                       // 2^11 - 1
    vector<int> big(N); iota(big.begin(), big.end(), 1);
    for (int i = 0; i < N; i++) swap(big[i], big[(i * 7 + 3) % N]);   // deterministic shuffle
    vector<int> sortedBig = heapsort(big);
    check((int)sortedBig.size() == N, "heapsorted all 2047 keys");
    check(ascending(sortedBig), "sorts to ascending order");
    check(!sortedBig.empty() && sortedBig.front() == 1 && sortedBig.back() == N, "first is 1, last is 2047");

    cout << passCnt << " passed, " << failCnt << " failed"
         << (failCnt ? "" : "  —  now run it under valgrind (must be clean)") << '\n';
    return failCnt ? 1 : 0;
}
#endif
