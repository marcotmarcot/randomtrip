#ifndef VISITED_H
#define VISITED_H

#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>

#include "point.h"

class Visited {
public:
  Visited() {}

  Visited(std::string arg) {
    std::stringstream visiteds;
    visiteds.str(arg);
    std::string visited;
    while (getline(visiteds, visited, ';')) {
      points_.push_back({visited});
    }
  }

  std::string String() {
    std::ostringstream ss;
    for (int i = 0; i < points_.size(); i++) {
      if (i > 0) {
        ss << ";";
      }
      ss << points_[i].String();
    }
    return ss.str();
  }

  static Visited FromFile(std::string path) {
    std::ifstream file(path);
    std::string line;
    Visited visited;
    while(std::getline(file, line)) {
      if (line.empty() || line[0] == '#') {
        continue;
      }
      visited.points_.push_back(Point(line));
    }
    return visited;
  }

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

  std::vector<Point> points_;
};

#endif
