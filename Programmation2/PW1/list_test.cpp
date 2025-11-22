#include "class_list.hpp"
#include <iostream>

int main() {

  // Testing pw1 list class
  // constructors
  list<int> intList1(5, 10);     // List of 5 integers, all initialized to 10
  list<int> intList2 = intList1; // Copy constructor
  list<int> intList3;
  list<std::string> strList1(
      3, "hello"); // List of 3 strings, all initialized to "hello"
  // Operator Overloading
  intList3 = std::move(intList1); // Move assignment
  strList1 = std::move(strList1); // Move assignment
  // Displaying contents using operator<<
  std::cout << "intList1 contents: " << intList1 << std::endl;
  std::cout << "intList2 contents: " << intList2 << std::endl;
  std::cout << "intList3 contents: " << intList3 << std::endl;
  std::cout << "strList1 contents: " << strList1 << std::endl;
  // Accessing elements using operator[]
  std::cout << "intList2[2]: " << intList2[2] << std::endl;
  std::cout << "strList1[1]: " << strList1[1] << std::endl;
  // Accessing elements and modifying them using operator()
  intList2(2) = 42;
  strList1(1) = "world";
  std::cout << "intList2[2] after modification: " << intList2[2] << std::endl;
  std::cout << "strList1[1] after modification: " << strList1[1] << std::endl;
  std::cout << "intList2 contents after modification: " << intList2
            << std::endl;
  std::cout << "strList1 contents after modification: " << strList1
            << std::endl;

  return 0;
}