#include "polynomial.h"
#include <cmath>
Polynomial::Polynomial(){
    size_ = 1;
    coeffs_ = new double[1];
}
Polynomial::Polynomial(int size){
    if(size <= 0){
        size_ = 1;
        coeffs_ = new double[1];
    }else{
        size_ = size;
        coeffs_ = new double[size];
    }
}
Polynomial::Polynomial(const Polynomial& other){
    size_ = other.size();
    coeffs_ = new double[size_];
    for(int i = 0; i < size_; i++){
        coeffs_[i] = other.coefficient(i);
    }
}

Polynomial::~Polynomial(){
    delete[] coeffs_;
    coeffs_ = nullptr;
}
Polynomial& Polynomial::operator=(const Polynomial& rhs){
    delete[] coeffs_;
    coeffs_ = nullptr;
    size_ = rhs.size();
    coeffs_ = new double[size_];
    for(int i = 0; i < size_; i++){
        coeffs_[i] = rhs.coefficient(i);
    }
    return *this;
}
int Polynomial::size() const{
    return size_;
}
double Polynomial::coefficient(int power) const{
    if(power < 0 || power >= size_){
        return 0;
    }
    return coeffs_[power];
}
void Polynomial::set_coefficient(int power, double value){
    if(power < 0 || power >= size_){
        return;
    }
    coeffs_[power] = value;
}
void Polynomial::resize(int new_size){
    if(new_size <= 0){
        new_size = 1;
    }
    double* temp_ = new double[new_size];
    int min = std::min(size_ , new_size);
    for(int i = 0; i < min; i++){
        temp_[i] = coeffs_[i];
    }
    delete[] coeffs_;
    coeffs_ = nullptr;
    coeffs_ = temp_;
    size_ = new_size;
}
Polynomial Polynomial::operator+(const Polynomial& rhs) const{
    Polynomial temp_(std::max(rhs.size() , size_));
    for(int i = 0; i < temp_.size(); i++){
        temp_.set_coefficient(i , (rhs.coefficient(i) + coeffs_[i]));
    }
    return temp_;
}
Polynomial Polynomial::operator-(const Polynomial& rhs) const{
    Polynomial temp_(std::max(rhs.size() , size_));
    for(int i = 0; i < temp_.size(); i++){
        temp_.set_coefficient(i , (coeffs_[i] - rhs.coefficient(i)));
    }
    return temp_;
}
bool Polynomial::operator==(const Polynomial& rhs) const{
    if(rhs.size() != size_){
        return false;
    }
    for(int i = 0; i < size_; i++){
        if(coeffs_[i] != rhs.coefficient(i)) return false;
    }
    return true;
}
bool Polynomial::operator!=(const Polynomial& rhs) const{
    return !(*this==rhs);
}
std::ostream& operator<<(std::ostream& out, const Polynomial& poly){
    out << "[ ";
    for(int i = 0; i < poly.size(); i++){
        out << poly.coefficient(i) << " ";
    }
    out << "]";
    return out;
}