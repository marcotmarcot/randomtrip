#include <iostream>

#include "../randomtrip/visited.h"
#include "../randomtrip/range.h"

int main(int argc, char **argv) {
  Point from = Point(argv[1]);
  Point to = Point(argv[2]);
  std::cout.precision(6);
  std::cout << std::fixed << from.Distance(to) << std::endl;
  return 0;
}
