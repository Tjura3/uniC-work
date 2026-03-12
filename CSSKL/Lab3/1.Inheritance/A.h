/*
 *  A.h
 *  Inheritance Example
 *
 *  Created by Prof. Michael Stiber
 *  Modified by Yang Peng on 01/12/2018
 *
 */

#ifndef A_H   //header file guards what is the perpouse? if not defined, define it.
#define A_H

#include <string>
using namespace std;

class A
{
public:
    A();
    A(string name);
    A(string, int, int);
	~A();
    
    void setN(const char* s);
    string getN() const;
    
private:
    string n;
    int testData1, testData2;
};

#endif
