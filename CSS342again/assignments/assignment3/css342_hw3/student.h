#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

// Student records are used as the data stored in List342.
// Sorting order (increasing): //Im pretty sure z is last and is also bigger
//   1) last_name
//   2) first_name
//   3) age
//
// Duplicate definition:
//   same first_name, last_name, and age.
//
// I/O format:
//   operator>> reads:  first last age
//   operator<< prints: first last age   (single spaces, no trailing newline)
class Student {
public:
  Student() = default;
  Student(std::string first, std::string last, int age);

  const std::string& first_name() const { return first_name_; }
  const std::string& last_name() const { return last_name_; }
  int age() const { return age_; }

  bool operator<(const Student& rhs) const;
  bool operator==(const Student& rhs) const;
  bool operator!=(const Student& rhs) const { return !(*this == rhs); }

  friend std::ostream& operator<<(std::ostream& os, const Student& s);
  friend std::istream& operator>>(std::istream& is, Student& s);

private:
  std::string first_name_;
  std::string last_name_;
  int age_ = 0;
};

#endif  // STUDENT_H
