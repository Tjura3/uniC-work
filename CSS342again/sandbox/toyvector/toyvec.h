#pragma once
/**
 * Vector is great at:
 * random access
 * fast append / remove at back
 * easy iteration(index)
 */


template <typename T>
class ToyVector{
    private:
    int capacity_;
    int size_;
    T* data_;

    void grow();


    public:
    ToyVector(); 
    ~ToyVector();
    ToyVector(const ToyVector& other);
    ToyVector& operator=(const ToyVector& other);
    //is it only for the operators where you put in const after the parens of the method?
    //that makes it so it can't edit the origional object, so why dont we do it here?
    //is having the const before the same as the const after?
    //I know that const in size() here wont edit the size in this object.
    const int size(); //when you return something, that thing is not going to be changed (check)
    int capacity() const; 
    //if your returning by value, it doesnt really matter. if you return by refrence, THEN it matters.

    //setters should have it at the end of the name,


    //set, get, remove.
    void push_back(const T& value); //
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    void set(const T& value, const int& location); //sets value at
    T get(const int& location);
    void remove(const int& location);
    int erase_duplicates();
};

template <typename T>
ToyVector<T>::ToyVector(){
    capacity_ = 0;
    size_ = 0;
    data_ = nullptr;

}
template <typename T>
ToyVector<T>::~ToyVector(){
    delete[] data_;
    data_ = nullptr;
}

//Copy on creation
template <typename T>
ToyVector<T>::ToyVector(const ToyVector& other){
    capacity_ = other.capacity();
    size_ = other.size();
    data_ = new int[capacity_];
    for(int i = 0; i < size_; i++){
        data_[i] = other.get(i);
    }
    //return *this; //when you want to return the object, return itself;
}

//deep copy on assignment
template <typename T>
ToyVector<T>& ToyVector<T>::operator=(const ToyVector& other){
    if(this == &other){
        return *this;
    }

    delete[] data_;
    size_ = other.size();
    capacity_ = other.capacity();

    data_ = new int[capacity_];
    for(int i = 0; i < size_; i++){
        data_[i] = other.get(i);
    }

    return *this;
}


//WHY IN THE SLIDES ARE THE VARIABLES USING UPER CAMEL CASE
template <typename T>
void ToyVector<T>::grow(){
    int newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;

    int* newData = new T[newCapacity];

    for(int i = 0; i < size_; i++){
        newData[i] = data_[i];
    }

    delete[] data_;
    data_ = newData; //does this change where data is pointing to so we don't need to delete newData?
    capacity_ = newCapacity;
}

template <typename T>
void ToyVector<T>::push_back(const T& value){
    if(size_ == capacity_){
        grow();
    }
    data_[size_] = value;
    size_++;
}
template <typename T>
void ToyVector<T>::push_front(const T& value){
    if(size_ == capacity_){
        grow();
    }
    size++;
    T temp;
    for(int i = 0; i < size_ -1; i++){
        temp = data_[i+1];
        data_[i+1] = data_[i];
    }
    data_[0] = value;
}
template <typename T>
void ToyVector<T>::pop_back(){
    if(size_ == 0) return;
    size_--;
}
template <typename T>
void ToyVector<T>::pop_front(){
    if(size_ == 0) return;
    for(int i = 0; i < size_ -1; i++){
        data_[i] = data_[i+1];
    }
    size--;
}
template <typename T>
const int ToyVector<T>::size(){
    return size_;
}
template <typename T>
int ToyVector<T>::capacity() const{
    return capacity_;
}
template <typename T>
T ToyVector<T>::get(const int& location){
    //what happens if it gets called out of bounds?
    //if(location > size_) return data_[0];
    return data_[location];
}
template <typename T>
int ToyVector<T>::erase_duplicates(){
    if(size_ == 0) return 0;
    if(size_ == 1) return 1;
    for(int i = 0; i < size_ -1; i++){ //size will constantly decrease
        if(data_[i] == data_[i+1]){
            for(int j = i + 1; j < size_-1; j++){
                data_[j] = data_[j+1];
            }
            i--; //steps back by one.
            size_--;
        }
    }
    return size_;
}

