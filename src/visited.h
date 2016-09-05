#ifndef VISITED_H
#define VISITED_H

#include <vector>

#include "point.h"

class Visited {
public:
  Visited(std::vector<Point> points) : points_(points) {}
  double MinDistance(Point p) {
    // Earth perimeter is 40000km, so there should be no distance larger than
    // this.
    double min = 100000;
    for (auto point : points_) {
      auto d = point.Distance(p);
      if (d < min) {
        min = d;
      }
    }
    return min;
  }
private:
  std::vector<Point> points_;
};

#endif
