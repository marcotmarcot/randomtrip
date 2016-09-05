#ifndef TEST_H
#define TEST_H

#include <cmath>
#include <iostream>

void eq(std::string name, double val, double exp) {
  if (fabs(val - exp) > 1) {
    std::cout << "ERROR: " << name << ": " << val << " != " << exp << std::endl;
    return;
  }
  std::cout << "PASSED: " << name << std::endl;
}

void ne(std::string name, double val, double exp) {
  if (fabs(val - exp) <= 1) {
    std::cout << "ERROR: " << name << ": " << val << " != " << exp << std::endl;
    return;
  }
  std::cout << "PASSED: " << name << std::endl;
}

#endif
