/*
 * MyClass.cpp
 *
 * Created by Michael Stiber
 * Modified by Yang Peng on 01/15/2018
 */

#include "MyClass.h"
#include <cassert>

using namespace std;

MyClass::MyClass() : i(0), d(0.0)
{
    ip = new int;
    *ip = 0;
}

MyClass::MyClass(const MyClass& orig) : ip(nullptr)
{
    ip = new int;
    *ip = 0;
    //needs to add the above because the pre-conditions need to be fulfilled
    // Note that this is a new object; no dynamic memory has been allocated
    copy(orig);
}

MyClass& MyClass::operator=(const MyClass& rhs)  //what is copy's method assuming? 
{
    // we have seen this before: a = a is a legal assignment, and shouldn't do anything
    if (this != &rhs) {
      copy(rhs);
    }
    return *this;
}

MyClass::~MyClass()
{
    clear();
}

void MyClass::setI(int newI)
{
    i = newI;
}

void MyClass::setD(double newD)
{
    d = newD;
}

void MyClass::setS(string newS)
{
    s = newS;
}

void MyClass::setIp(int newIp)
{
    *ip = newIp;
}

int MyClass::getI() const
{
    return i;
}

double MyClass::getD() const
{
    return d;
}

string MyClass::getS() const
{
    return s;
}

int MyClass::getIp() const
{
    return *ip;
}

void MyClass::copy(const MyClass& other)
{
    i = other.i;
    d = other.d;
    s = other.s;

    assert(ip != nullptr);
    // all deep copies need to allocate dynamic memory and it needs an assignment statement.
    // it needs to delete in the event of copying over something that already has values in the array.
    delete ip;
    ip = new int;   //this is assuming that ip is a nullpointer prior to adding delete.
    *ip = *(other.ip);
    
    //at the end of the day, its not a shallow copy because its not using the "this" keyword. and if you do, it will point at same location.
}

void MyClass::clear()
{
    i = 0;
    d = 0.0;
    s = "";

    assert(ip != nullptr);
    *ip = 0;
    delete ip;
    ip = nullptr;
}

class MySubClass : public MyClass{
    public:
    MySubClass() : data(0), MyClass(){} //data is initialized from zero
    

    //need to create a copy constructor, or else a shallow copy will happen. if you are implementing a class that has a copy constructor,
    //at the minimum you need to copy that copy constructor.
    MySubClass(const MySubClass& other) : data(0), MyClass(other){}  //you can pass the subclass to the parent because it will only take the data from the parent class of the other subclass.

    //the destructors are called blindly. we dont need to call it because we are not defining memory here
    //because there is always a defult constructor, if its not defined a defult constructor will always be called

    MySubClass& operator=(const MySubClass& other){ //if the super class has a copy constructor, you must implement it.
        if(this != &other){
            data = other.data;
            MyClass::operator=(other); //will copy the non-subclass part of it
        }
        return *this;
    }

    int data;
};
