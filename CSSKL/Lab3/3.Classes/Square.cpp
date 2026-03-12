/*
 *  Square.cpp
 *  Class-example
 *
 */

#include "Square.h"

void Square::setSize(int newSize)
{
   theSize = newSize;
}


int Square::getSize(void) const
{
   return theSize;
}

Square& Square::operator = (const Square& other)//takes this square, the size field, and makes it equal to the other square's size field and returns itself
{
	theSize = other.getSize();
	return *this;
}

bool Square::operator < (const Square& square){ 
   return theSize < square.getSize();
}
//Does the Square class need an overloaded assignment operator?
//It doesnt need it, but its overall nice to have. it makes dealing with other squares in the code that uses it a bit easier.

