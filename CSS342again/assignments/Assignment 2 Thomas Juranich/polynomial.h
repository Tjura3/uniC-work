#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_
#include <iostream>
class Polynomial{
    private:
    int size_; //number of coeficients
    double* coeffs_; // heap array of size size_
    /**
     * at ALL TIMES
     * size_ >= 1
     * coeffs_ points to a valid heap-allocated array of size size_
     */
    public:
    Polynomial(); //creates a zero polynomial (size_ = 0, coeffs_[0] = 0)
    Polynomial(int size); //if size is <= 0, normalize to defult constructor, otherwise allocate size coefficients initialized to 0
    //basically, all constructors will be valid, it doesn't throw exceptions and has defult values if invalid.
    
    Polynomial(const Polynomial& other);//copy constructor
    ~Polynomial();
    Polynomial& operator=(const Polynomial& rhs);
    int size() const;
    double coefficient(int power) const; //If power < 0 or power >= size_, return 0
    void set_coefficient(int power, double value); //If power < 0 or power >= size_, do nothing
    void resize(int new_size);
    Polynomial operator+(const Polynomial& rhs) const;
    Polynomial operator-(const Polynomial& rhs) const;
    bool operator==(const Polynomial& rhs) const;
    bool operator!=(const Polynomial& rhs) const;
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
};
#endif