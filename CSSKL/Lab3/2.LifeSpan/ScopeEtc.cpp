/*
 * ScopeEtc.cpp
 *
 * Code to show some things about scope, variable lifespan, and lvalues.
 *
 * Created by Michael Stiber
 * Modified by Yang Peng on 01/12/18
 */

#include <iostream>
#include "SuperInt.h"

using namespace std;

static SuperInt var(0, "global"); //this is very evil, do not use global variables.

int main()
{
  cout << "At start of main()" << endl;

  cout << "var's value is " << var.theValue() << endl << endl;

  SuperInt var2(1, "Main"); //
  cout << "var2's value is " << var2.theValue() << endl << endl;

  //int& ptr;
  cout << "Entering top block" << endl;
  {
    SuperInt var2(2, "block"); //created blovk variable
    cout << "var2's value is " << var2.theValue() << endl << endl;
    
  }

  cout << "Exiting top block" << endl << endl;;

  const int &r(var.theValue()); //value function returns a constant integer refrence

  cout << "Entering bottom block" << endl;
  {
    static SuperInt var2(2, "static"); 
    cout << "var2's value is " << var2.theValue() << endl << endl;
  }  
  cout << "Exiting bottom block" << endl << endl;

  int i = var2.theValue(); //I beceoms the value
  //var2.theValue() = 11231;
  
  SuperInt* pvar = new SuperInt(3, "dynamic");

  cout << "At end of main()" << endl;
  return 0;
}
