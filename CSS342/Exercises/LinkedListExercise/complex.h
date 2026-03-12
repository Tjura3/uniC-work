//professor work
#include <iostream>

#ifndef _COMPLEX_H_
#define _COMPLEX_H_

using namespace std;

namespace mycomplex{

    class Complex{
        private:
            double real;
            double imaginary;
        public:
            Complex();
            Complex(const double& real, const double& imaginary = 0.0);
            Complex(const Complex& c);
            ~Complex();

            void setReal(const double& r);
            void setImaginary(const double& i);
            double getReal() const;
            double getImaginary() const;

            // Complex& operator=(const Complex& c);
            Complex* operator+(const Complex& c);
            Complex* operator-(const Complex& c);
            Complex* operator*(const Complex& c);
    };

    Complex::Complex(){        
    }

    Complex::Complex(const double& real, const double& imaginary){
        this->real = real;
        this->imaginary = imaginary;
    }

    Complex::Complex(const Complex& c){
        this->real = c.real;
        this->imaginary = c.imaginary;
    }
    Complex::~Complex(){
    }

    void Complex::setReal(const double& r){
        this->real = r;
    }

    void Complex::setImaginary(const double& i){
        this->imaginary = i;
    }

    double Complex::getReal() const{
        return this->real;
    }

    double Complex::getImaginary() const{
        return this->imaginary;
    }

    Complex* Complex::operator+(const Complex& c){            
        return new Complex(this->real+c.real, this->imaginary+c.imaginary);
    }

    Complex* Complex::operator-(const Complex& c){            
        return new Complex(this->real-c.real, this->imaginary-c.imaginary);;
    }

    Complex* Complex::operator*(const Complex& c){    
        return new Complex(this->real*c.real - this->imaginary*c.imaginary, this->real*c.imaginary + this->imaginary*c.real);
    }



}

#endif 