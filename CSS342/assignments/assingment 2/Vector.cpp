#include <cmath>
#include "Vector.h"
Vector::Vector(){
    capacity = 3;
    arr = new int[capacity];
}

Vector::Vector(const int &a){
    capacity = a;
    arr = new int[a];
}
Vector::Vector(const Vector& b){
    capacity = b.capacity;
    for(int i = 0; i < capacity; i++){
        *(arr+i) = b.getDataAt(i);
    }
}
Vector::~Vector(){
    delete arr;
    arr = nullptr;
}


int Vector::getCapacity()const{
    return capacity;
}
int& Vector::getDataAt(int i) const{
    return *(arr+i);
}

void Vector::setDataAt(int i, int v){
    *(arr+i) = v;
}

float Vector::l2Normal(){
    float total = 0;
    for (int i = 0; i < capacity; ++i) {
		total += pow(*(arr + i), 2);
	}
    total = sqrt(total);
    return total;
}

float Vector::operator*(Vector& b){
    if(b.capacity != capacity) return -1.0f;

    int* holdvector = new int[capacity];
    for(int i = 0; i < capacity; ++i) {
		*(holdvector + i) = *(arr + i) * *(b.arr + i);
	}

    float sumOfVectors = 0;

    for(int i = 0; i < capacity; ++i){
        sumOfVectors += *(holdvector + i);
    }
    delete[] holdvector;
    holdvector = nullptr;

    return (sumOfVectors)/(l2Normal() * b.l2Normal());
}



