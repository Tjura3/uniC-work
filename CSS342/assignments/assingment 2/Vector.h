#pragma once
class Vector{
    private:
        int capacity;
        int* arr;
    public:
        Vector();
        
        Vector(const int& a);
        Vector(const Vector& b);
        ~Vector();

        int getCapacity() const;
        int& getDataAt(int i) const;
        void setDataAt(int i, int v);
        float l2Normal();

        float operator*(Vector& b);
};