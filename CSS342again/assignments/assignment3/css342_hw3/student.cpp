#include "student.h"

#include <utility>

Student::Student(std::string first, std::string last, int age)
    : first_name_(std::move(first)), last_name_(std::move(last)), age_(age) {}

bool Student::operator<(const Student& rhs) const {
  if (last_name_ != rhs.last_name_) return last_name_ < rhs.last_name_;
  if (first_name_ != rhs.first_name_) return first_name_ < rhs.first_name_;
  return age_ < rhs.age_;
}

bool Student::operator==(const Student& rhs) const {
  return first_name_ == rhs.first_name_ &&
         last_name_ == rhs.last_name_ &&
         age_ == rhs.age_;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
  os << s.first_name_ << " " << s.last_name_ << " " << s.age_;
  return os;
}

std::istream& operator>>(std::istream& is, Student& s) {
  is >> s.first_name_ >> s.last_name_ >> s.age_;
  return is;
}
