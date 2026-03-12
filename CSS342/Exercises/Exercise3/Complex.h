#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Complex{
    private:
    double real;
    double imagine;
    public:
    Complex();
    ~Complex();
    Complex(const Complex& c);
    Complex(const double& real, const double& imagery = 0.0);
    void setReal(const double& r);
    void setImaginary(const double& i);
    double getReal();
    double getImaginary();
    //Complex &opperator+(const Complex& a, const complex& b);
    Complex& operator+(const Complex& c);
    Complex& operator-(const Complex& c);
    Complex& operator*(const Complex& c);




    
}; //why do we need the semicolon here?
Complex::Complex(){
}
Complex::~Complex(){
}
Complex::Complex(const Complex& c){
    
}