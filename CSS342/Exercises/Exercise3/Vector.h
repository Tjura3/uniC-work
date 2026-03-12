template <typename T>
class Vector{
    private:
        int capacity;
        T* arr;
    public:
        Vector();
        Vector(int capacity);
        //Vector(const int& capacity);
        Vector(const Vector<T>& v);
        ~Vector();

        int getCapacity() const;
        T* getArray() const; //its a pointer to the location in memory where the value of type T are being stored
        T& getdataAt(int i) const;
        void setDataAt(int i, T v);

        T& operator[](int i);
        T& operator=(const Vector<T>& v);

};
template <typename T>
Vector<T>::Vector(){
}
template <typename T>
Vector<T>::Vector(int capacity){
    this->capacity = capacity;
    arr = new T[capacity]
}
template <typename T>
Vector<T>::Vector(const Vector<T>& v){
    
    if (this != &v)
    {
        capacity = v.capacity;
        arr = new T[capacity];
        for (int i = 0; i < capacity; i++)
        {
            arr[i] = v.getDataAt(i);
        }
    }
}
template <typename T>
Vector<T>::~Vector(){
    delete[] arr;
}
