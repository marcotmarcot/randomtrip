#include <iostream>

#include "../randomtrip/visited.h"
#include "../randomtrip/range.h"

int main(int argc, char **argv) {
  Visited visited = Visited::FromFile(argv[1]);
  std::cout
    << Highest(visited, Point(-90, -180), Point(90, 180), 10000).String()
    << std::endl;
  return 0;
}
