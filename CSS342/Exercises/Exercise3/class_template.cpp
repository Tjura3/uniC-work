#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
/* *************************************************** */
// Class defitinion and members for Complex
/* *************************************************** */
class Complex
{
private:
    double real;
    double imagery;

public:
    Complex();
    Complex(const double &real, const double &imagery = 0.0);
    Complex(const Complex &c);
    ~Complex();
    void setReal(const double &r);  
    void setImagery(const double &i);
    double getReal() const;
    double getImagery() const;
    // Complex& operator=(const Complex& c);
    Complex &operator+(const Complex &c);
    Complex &operator-(const Complex &c);
    Complex &operator*(const Complex &c);
};
Complex::Complex()
{
}
Complex::Complex(const double &real, const double &imagery)
{
    this->real = real;
    this->imagery = imagery;
}
Complex::Complex(const Complex &c)
{
    this->real = c.real;
    this->imagery = c.imagery;
}
Complex::~Complex()
{
}
void Complex::setReal(const double &r)
{
    this->real = r; //why do you need to use the arrows again? what do the arrows do?
}
void Complex::setImagery(const double &i)
{
    this->imagery = i;
}
double Complex::getReal() const
{
    return this->real;
}
double Complex::getImagery() const
{
    return this->imagery;
}
// Complex& Complex::operator=(const Complex& c){
// if (this != &c){
// this->real = c.real;
// this->imagery = c.imagery;
// }
// return *this;
// }
Complex &Complex::operator+(const Complex &c)
{
    this->real += c.real;
    this->imagery += c.imagery;
    return *this;
}
Complex &Complex::operator-(const Complex &c)
{
    this->real -= c.real;
    this->imagery -= c.imagery;
    return *this;
}
Complex &Complex::operator*(const Complex &c)
{
    this->real = this->real * c.real - this->imagery * c.imagery;
    this->imagery = this->real * c.imagery + this->imagery * c.real;
    return *this;
}
/* *************************************************** */
// Class template defitinion and members for Vector
/* *************************************************** */
template <typename T>
class Vector
{
private:
    int capacity;
    T *arr;

public:
    Vector();
    Vector(int capacity);
    Vector(const Vector<T> &v);
    ~Vector();
    int getCapacity() const;
    T *getArray() const;
    T &getDataAt(int i) const;
    void setDataAt(int i, T v);
    T &operator[](int i);
    // T& operator=(const Vector<T>& v);
};
template <typename T>
Vector<T>::Vector()
{
}
template <typename T>
Vector<T>::Vector(int capacity)
{
    this->capacity = capacity;
    arr = new T[capacity];
}
template <typename T>
Vector<T>::Vector(const Vector<T> &v)
{
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
Vector<T>::~Vector()
{
    delete[] arr;
}
template <typename T>
int Vector<T>::getCapacity() const
{
    return capacity;
}
template <typename T>
T *Vector<T>::getArray() const
{
    return arr;
}
template <typename T>
T &Vector<T>::getDataAt(int i) const
{
    return arr[i];
}
template <typename T>
void Vector<T>::setDataAt(int i, T v)
{
    arr[i] = v;
}
template <typename T>
T &Vector<T>::operator[](int i)
{
    return arr[i];
}
// template <typename T>
// T& Vector<T>::operator=(const Vector<T>& v){
// if (this != &v){
// capacity = v.capacity;
// arr = new T[capacity];
// for (int i=0; i < capacity; i++){
// arr[i] = v[i];
// }
// }
// return *this;
// }
/* *************************************************** */
// Main function
/* *************************************************** */
int main()
{
    Complex c1 = Complex(3, 4);
    Complex c2 = Complex(-2, 3);
    Complex c3 = c1 + c2;
    Complex c4 = c1 - c2;
    Complex c5 = c1 * c2;
    Complex c6 = c5;
    Complex c7 = Complex(c1);
    srand(static_cast<unsigned int>(time(nullptr)));
    Vector<int> v1(5);
    for (int i = 0; i < 5; i++)
    {
        v1.setDataAt(i, rand() % 100);
        cout << v1[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << v1.getDataAt(i) << " ";
    }
    cout << endl;
    Vector<double> v2(5);
    for (int i = 0; i < 5; i++)
    {
        v2.setDataAt(i, rand() % 100 + 0.123);
        cout << v2[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << v2.getDataAt(i) << " ";
    }
    cout << endl;
    Vector<Complex> v3(5);
    for (int i = 0; i < 5; i++)
    {
        v3.setDataAt(i, Complex(rand() % 10, rand() % 10));
        cout << v3[i].getReal() << " + " << v3[i].getImagery() << "i ";
    }
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << v3.getDataAt(i).getReal() << " + " << v3.getDataAt(i).getImagery()
             << "i ";
    }
    cout << endl;
    // Copy construtor or operator=
    Vector<int> v4 = v1;
    for (int i = 0; i < 5; i++)
    {
        cout << v4[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << v4.getDataAt(i) << " ";
    }
    cout << endl;
    Vector<Complex> v5 = v3;
    for (int i = 0; i < 5; i++)
    {
        v5.setDataAt(i, Complex(rand() % 10, rand() % 10));
        cout << v5[i].getReal() << " + " << v5[i].getImagery() << "i ";
    }
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << v5.getDataAt(i).getReal() << " + " << v5.getDataAt(i).getImagery()
             << "i ";
    }
    cout << endl;
    return 0;
}