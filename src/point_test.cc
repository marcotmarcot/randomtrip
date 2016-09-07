#include <cmath>
#include <iostream>

#include "test.h"

#include "point.h"

int main(int argc, char **argv) {
  eq("radians", Radians(90), M_PI/2);

  Point bh("-19.9178576,-44.0305233");
  Point rio("-22.9111718,-43.5887611");
  eq("distance", bh.Distance(rio), 335.967);
  return 0;
}
