#pragma once
#include <vector>

using namespace std;
template <typename T, typename Comparator>
class Heap{
    private:
    vector<T> data;
    Comparator comp;
    
    //OK so here, we are condensing the tree into a vector
    //parent = (i-1)/2
    //left = 2i+1
    //right = 2i+2
    void upheap(int idx){
        T value = data[idx];
        while(idx > 0 && comp(data[(idx - 1) /2], value) == false){
            data[idx] = data[(idx - 1) / 2];
            idx = (idx - 1) / 2;
        }
        data[idx] = value;
    }
    void downheap(int idx) {
        if (data.empty()) return;
        T value = data[idx];

        while (idx * 2 + 1 < data.size()) {
            int idxChild = idx * 2 + 1; 
            
            //If right exists and is cheaper, pick right
            if (idxChild + 1 < data.size() && comp(data[idxChild + 1], data[idxChild])) {
                idxChild++;
            }
    
            //If value is already cheaper than cheapest child we are done
            if (comp(value, data[idxChild])) {
                break;
            }
            
            //if not, pull the cheap child up and move down
            data[idx] = data[idxChild];
            idx = idxChild;
        }
        data[idx] = value;
    }

    public:
    void add(const T& item) {
        data.push_back(item);
        upheap(data.size() - 1);
    }
    

    T remove() {
        if (data.empty()) {
            throw runtime_error("Hot dogs are empty!");
        }
        T ret = data[0];
        data[0] = data.back(); 
        data.pop_back();
        if (!data.empty()) {
            downheap(0);
        }
        return ret;
    }
    size_t size() const {
        return data.size();
    }
    bool empty() const {
        return data.empty();
    }
};