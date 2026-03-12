// polynomial_tests_student.cpp
// Reference tests for students (NOT exhaustive).
//
// Compile:
//   g++ -std=c++17 polynomial.cpp polynomial_tests_student.cpp -o poly_test
//
// Run:
//   ./poly_test

#include <iostream>
#include <sstream>
#include "polynomial.h"

using std::cerr;
using std::cout;
using std::endl;

static void fail(const char* msg) {
  cerr << "FAILED: " << msg << endl;
}

int main() {
  // ===== default constructor =====
  Polynomial p;
  if (p.size() != 1) { fail("default size should be 1"); return 1; }
  if (p.coefficient(0) != 0) { fail("default coeff[0] should be 0"); return 1; }

  // ===== size constructor =====
  Polynomial p2(3);
  if (p2.size() != 3) { fail("Polynomial(3) size should be 3"); return 1; }
  if (p2.coefficient(0) != 0 || p2.coefficient(1) != 0 || p2.coefficient(2) != 0) {
    fail("Polynomial(3) coefficients should start at 0");
    return 1;
  }

  // ===== bounds behavior (reference) =====
  if (p2.coefficient(-1) != 0 || p2.coefficient(3) != 0) {
    fail("coefficient(out-of-bounds) should return 0");
    return 1;
  }

  // ===== set_coefficient / coefficient =====
  p2.set_coefficient(0, 1);
  p2.set_coefficient(1, 2);
  p2.set_coefficient(2, 3);
  if (p2.coefficient(0) != 1 || p2.coefficient(1) != 2 || p2.coefficient(2) != 3) {
    fail("set_coefficient or coefficient incorrect");
    return 1;
  }

  // out-of-bounds set should do nothing
  p2.set_coefficient(-1, 99);
  p2.set_coefficient(3, 99);
  if (p2.coefficient(0) != 1 || p2.coefficient(1) != 2 || p2.coefficient(2) != 3) {
    fail("set_coefficient(out-of-bounds) should do nothing");
    return 1;
  }

  // ===== copy constructor (deep copy) =====
  Polynomial p3(p2);
  p2.set_coefficient(0, 99);
  if (p3.coefficient(0) != 1) { fail("copy constructor should deep copy"); return 1; }

  // ===== assignment operator (deep copy) =====
  Polynomial p4(1);
  p4 = p3;
  p3.set_coefficient(1, 77);
  if (p4.coefficient(1) != 2) { fail("operator= should deep copy"); return 1; }

  // ===== operator+ and operator- (same size) =====
  Polynomial sum = p3 + p4;
  if (sum.size() != 3) { fail("sum size should be 3"); return 1; }
  if (sum.coefficient(0) != (p3.coefficient(0) + p4.coefficient(0))) { fail("sum coeff[0] wrong"); return 1; }

  Polynomial diff = p4 - p3;
  if (diff.coefficient(0) != (p4.coefficient(0) - p3.coefficient(0))) { fail("diff coeff[0] wrong"); return 1; }

  // ===== operator+ with different sizes =====
  Polynomial a(2);
  a.set_coefficient(0, 5);
  a.set_coefficient(1, 6);
  Polynomial b(4);
  b.set_coefficient(0, 1);
  b.set_coefficient(2, 7);
  b.set_coefficient(3, 8);

  Polynomial c = a + b;
  if (c.size() != 4) { fail("different-size + result size should be max"); return 1; }
  if (c.coefficient(0) != 6 || c.coefficient(1) != 6 || c.coefficient(2) != 7 || c.coefficient(3) != 8) {
    fail("different-size + coefficients incorrect");
    return 1;
  }

  // ===== equality / inequality =====
  Polynomial e1(3);
  e1.set_coefficient(0, 1);
  e1.set_coefficient(1, 2);
  e1.set_coefficient(2, 3);

  Polynomial e2(3);
  e2.set_coefficient(0, 1);
  e2.set_coefficient(1, 2);
  e2.set_coefficient(2, 3);

  if (!(e1 == e2)) { fail("operator== should be true for equal polys"); return 1; }
  if (e1 != e2) { fail("operator!= should be false for equal polys"); return 1; }

  // ===== stream output format =====
  std::ostringstream oss;
  oss << e1;
  if (oss.str() != "[ 1 2 3 ]") {
    cerr << "FAILED: operator<< format mismatch.\n"
         << "Expected: [ 1 2 3 ]\n"
         << "Got:      " << oss.str() << endl;
    return 1;
  }

  // ===== resize grow =====
  Polynomial r1(3);
  r1.set_coefficient(0, 1);
  r1.set_coefficient(1, 2);
  r1.set_coefficient(2, 3);

  r1.resize(5);
  if (r1.size() != 5) { fail("resize grow: size should be 5"); return 1; }
  if (r1.coefficient(0) != 1 || r1.coefficient(1) != 2 || r1.coefficient(2) != 3) {
    fail("resize grow: old coefficients not preserved");
    return 1;
  }
  if (r1.coefficient(3) != 0 || r1.coefficient(4) != 0) {
    fail("resize grow: new coefficients should be 0");
    return 1;
  }

  // ===== resize shrink + invalid size normalization =====
  Polynomial r2(5);
  r2.set_coefficient(0, 10);
  r2.set_coefficient(1, 20);
  r2.set_coefficient(2, 30);
  r2.set_coefficient(3, 40);
  r2.set_coefficient(4, 50);

  r2.resize(3);
  if (r2.size() != 3) { fail("resize shrink: size should be 3"); return 1; }
  if (r2.coefficient(0) != 10 || r2.coefficient(1) != 20 || r2.coefficient(2) != 30) {
    fail("resize shrink: kept coefficients incorrect");
    return 1;
  }
  if (r2.coefficient(3) != 0 || r2.coefficient(4) != 0) {
    fail("resize shrink: discarded coeffs should read as 0 (out-of-bounds)");
    return 1;
  }

  r2.resize(0); // normalize to size 1
  if (r2.size() != 1) { fail("resize(0) should normalize to size 1"); return 1; }
  if (r2.coefficient(0) != 10) { fail("resize(0): coeff[0] should be preserved"); return 1; }

  cout << "ALL REFERENCE TESTS PASSED (student version)" << endl;
  
  Polynomial test(e2);
  cout << e2 << endl << test << endl;
  cout << (test == e2) << endl;
  test = r2;
  cout << r2 << endl << test << endl;
  cout << test.coefficient(1) << endl;
  Polynomial r3(5);
  r3.set_coefficient(0, 10);
  r3.set_coefficient(1, 20);
  r3.set_coefficient(2, 30);
  r3.set_coefficient(3, 40);
  r3.set_coefficient(4, 50);
  cout << r3 << endl;
  Polynomial empty;
  cout << empty.coefficient(0) << endl;
  cout << r3 - r3 << endl << r3+r3 << endl << endl;
  cout << endl;
  Polynomial g1(3);
  Polynomial g2(3);
  g1.set_coefficient(2, 4);
  g2.set_coefficient(2, 3);
  cout << g1+g2 << endl;

  return 0;
}
