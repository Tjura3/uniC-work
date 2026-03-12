#include <cassert>
#include <iostream>
#include <string>

#include "list342.h"
#include "student.h"

static void PrintHeader(const std::string& name) {
  std::cout << "\n=== " << name << " ===\n";
}
/*
int main() {
  PrintHeader("Insert / Sorted Order / Duplicate Reject");

  Student s1("Angie", "Ham", 7);
  Student s2("Pradnya", "Dhala", 8);
  Student s3("Bill", "Vollmann", 13);
  Student s4("Cesar", "Ruiz", 6);
  Student s5("Piqi", "Tangi", 7);
  Student s6("Russell", "Wilson", 13);
  Student s7("Hank", "Aaron", 3);
  Student s8("Miles", "Davis", 65);
  Student s9("John", "Zorn", 4);
  Student out;

  List342 class1;
  List342 class2;

  assert(class1.insert(&s1));
  assert(class1.insert(&s2));
  assert(class1.insert(&s3));
  assert(class1.insert(&s4));
  assert(class1.insert(&s5));
  assert(class1.insert(&s6));

  // duplicate
  assert(!class1.insert(&s5));

  std::cout << "class1: " << class1 << "\n";

  assert(class2.insert(&s4));
  assert(class2.insert(&s5));
  assert(class2.insert(&s6));
  assert(class2.insert(&s7));
  assert(class2.insert(&s8));
  assert(class2.insert(&s9));

  std::cout << "class2: " << class2 << "\n";

  PrintHeader("Merge (splice nodes, handle duplicates), other becomes empty, Self-merge safe");
  assert(class1.merge(class2));
  assert(class2.size() == 0);

  std::cout << "merged (class1): " << class1 << "\n";
  std::cout << "after merge, class2 size: " << class2.size() << "\n";

  // self merge should be safe no-op
  assert(class1.merge(class1));
  std::cout << "after self-merge: " << class1 << "\n";

  PrintHeader("Peek / Remove");

  std::cout << "class1 before: " << class1 << "\n";
  assert(class1.peek(s6, out));
  std::cout << "peek Russell => " << out << "\n";

  assert(class1.remove(s1, out));
  std::cout << "removed Angie => " << out << "\n";

  Student not_in_list("Not", "Here", 1);
  assert(!class1.remove(not_in_list, out));

  std::cout << "class1 now: " << class1 << "\n";

  PrintHeader("Copy Constructor / Assignment / Equality (deep copy)");

  List342 copy1(class1);  // copy constructor
  std::cout << "copy now: " << copy1 << "\n";
  assert(copy1 == class1);

  List342 copy2;
  copy2 = class1;  // assignment
  assert(copy2 == class1);

  // mutate original
  assert(class1.remove(s6, out));
  assert(copy1 != class1);
  assert(copy2 != class1);

  PrintHeader("DeleteList");

  copy1.deleteList();
  assert(copy1.size() == 0);

  PrintHeader("BuildList + Merge (from provided input files)");

  List342 file1;
  List342 file2;

  assert(file1.buildList("students_class1.txt"));
  assert(file2.buildList("students_class2.txt"));

  assert(file1.merge(file2));
  assert(file2.size() == 0);

  std::cout << "merged file list: " << file1 << "\n";

  PrintHeader("All tests passed");
  std::cout << "OK\n";

  return 0;
}
*/
int main() {
  std::cout << "Running extended testing" << std::endl;
  PrintHeader("Insert / Sorted Order / Duplicate Reject");

  Student s1("Angie", "Ham", 7);
  Student s2("Pradnya", "Dhala", 8);
  Student s3("Bill", "Vollmann", 13);
  Student s4("Cesar", "Ruiz", 6);
  Student s5("Piqi", "Tangi", 7);
  Student s6("Russell", "Wilson", 13);
  Student s7("Hank", "Aaron", 3);
  Student s8("Miles", "Davis", 65);
  Student s9("John", "Zorn", 4);
  Student out;

  List342 empty;
  std::cout << "Empty list: " << empty << "\n";
  assert(empty.size() == 0);

  List342 class1;
  List342 class2;

  List342 single;
  single.insert(&s1);
  std::cout << "Single student: " << single << "\n";
  assert(single.size() == 1);

  assert(!class1.insert(nullptr));
  assert(class1.insert(&s1));
  assert(!class1.insert(nullptr));
  assert(!class1.insert(&s1));
  assert(!class1.insert(nullptr));
  assert(class1.insert(&s2));
  assert(!class1.insert(nullptr));
  assert(!class1.insert(&s2));
  assert(!class1.insert(nullptr));
  assert(class1.insert(&s3));
  assert(class1.insert(&s4));
  assert(class1.insert(&s5));
  assert(class1.insert(&s6));
  assert(!class1.insert(nullptr));
  std::cout << "Class1: " << class1 << "\n";
  // duplicate
  assert(!class1.insert(&s5));
  assert(!class1.insert(nullptr));
  assert(!class1.insert(&s6));
  assert(!class1.insert(nullptr));
  assert(class1.size() == 6);

  assert(class2.insert(&s4));
  assert(class2.insert(&s5));
  assert(class2.insert(&s6));
  assert(class2.insert(&s7));
  assert(class2.insert(&s8));
  assert(class2.insert(&s9));

  std::cout << "Class2: " << class2 << "\n";

  PrintHeader("Merge (splice nodes, handle duplicates), other becomes empty, Self-merge safe");
  assert(class1.merge(class2));
  assert(class2.size() == 0);

  std::cout << "merged (class1): " << class1 << "\n";
  std::cout << "after merge, class2 size: " << class2.size() << "\n";

  // self merge should be safe no-op
  assert(class1.merge(class1));
  std::cout << "after self-merge: " << class1 << "\n";

  PrintHeader("Peek / Remove");

  assert(!empty.peek(s1, out));

  Student not_in_list("Not", "Here", 1);
  assert(!class1.peek(not_in_list, out));

  assert(class1.peek(s6, out));
  std::cout << "peek Russell => " << out << "\n";
  assert(s6 == out);

  assert(!class1.peek(not_in_list, out));
  assert(s6 == out);

  assert(!empty.remove(s1, out));

  assert(class1.remove(s1, out));
  std::cout << "removed Angie => " << out << "\n";

  assert(class1.remove(s2, out));
  std::cout << "removed Pradnya => " << out << "\n";
  assert(!class1.peek(s1, out));
  assert(s2 == out);

  assert(class1.remove(s9, out));
  std::cout << "removed John => " << out << "\n";
  assert(s9 == out);
  assert(!class1.peek(s9, out));
  assert(s9 == out);

  assert(!class1.remove(not_in_list, out));
  assert(s9 == out);

  std::cout << "class1 now: " << class1 << "\n";

  assert(single.remove(s1, out));
  std::cout << "removed lone element Angie => " << out << "\n";
  assert(s1 == out);
  assert(single.size() == 0);

  PrintHeader("Copy Constructor / Assignment / Equality (deep copy)");

  List342 copy1(class1);  // copy constructor
  assert(copy1 == class1);
  assert(copy1.remove(s3, out));
  assert(class1.peek(s3, out));

  List342 copy2;
  copy2 = class1;  // assignment
  assert(copy2 == class1);
  
  List342 copy3(copy3);
  std::cout << "(copy3): " << copy3 << "\n";
  assert(copy3.size() == 0);
  

  copy2 = copy2;
  assert(copy2 == class1);

  // mutate original
  assert(class1.remove(s6, out));
  std::cout << "removed Russell => " << out << "\n";
  assert(s6 == out);
  assert(copy1 != class1);
  assert(copy2 != class1);

  PrintHeader("DeleteList");

  copy1.deleteList();
  assert(copy1.size() == 0);

  PrintHeader("BuildList + Merge (from provided input files)");

  List342 file1;
  List342 file2;

  assert(file1.buildList("students_class1.txt"));
  assert(!file2.buildList("fake.txt"));
  assert(file2.buildList("students_class2.txt"));

  assert(file1.merge(file2));
  assert(file1.size() == 9);
  assert(file2.size() == 0);

  std::cout << "merged file1 list: " << file1 << "\n";

  List342 file3(file1);
  assert(file1.merge(file3));
  assert(file1.size() == 9);
  assert(file3.size() == 0);

  List342 file4;
  assert(file1.merge(file4));
  assert(file1.size() == 9);
  assert(file4.size() == 0);

  List342 file5;
  assert(file5.merge(file1));
  assert(file5.size() == 9);
  assert(file1.size() == 0);

  std::cout << "merged file5 list: " << file5 << "\n";

  PrintHeader("All tests passed");
  std::cout << "OK\n";

  return 0;
}
