#include <iostream>

#include "../randomtrip/visited.h"
#include "../randomtrip/range.h"

int main(int argc, char **argv) {
  Visited visited = Visited::FromFile(argv[1]);
  Point point = Point(argv[2]);
  std::cout.precision(6);
  std::cout
    << visited.MinDistance(point)
    << std::endl;
  return 0;
}
