#include <cmath>
#include <iostream>

#include "test.h"

#include "point.h"
#include "visited.h"

int main(int argc, char **argv) {
  Point bh("-19.9178576,-44.0305233");
  // Rio and London.
  Visited visited("-22.9111718,-43.5887611;51.5285578,-0.2420229");
  eq("distance", visited.MinDistance(bh), 335.967);
  return 0;
}
