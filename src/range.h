#ifndef RANGE_H
#define RANGE_H

#include <cmath>
#include "point.h"
#include "visited.h"

template<typename Func>
double BinarySearch(double start, double end, double goal, double precision, Func f) {
  while (true) {
    double middle = (start + end) / 2;
    double current = f(middle);
    if (fabs(current - goal) < precision) {
      return middle;
    }
    if (current < goal) {
      start = middle;
    } else {
      end = middle;
    }
  }
}

template<typename Func>
double Integral(double start, double end, int steps, Func f) {
  double step = (end - start) / steps;
  double total = 0;
  for (double i = start; i <= end; i += step) {
    total += f(i) * step;
  }
  return total;
}

double LatWeight(Visited &visited, Point &start, Point &end, double lat) {
}

class Range {
public:
  Range(int base, Visited visited)
    : base_(base), visited_(visited), start_(-90, -180), end_(90, 180) {
  }

  Point Center() {
    return Point((start_.lat_+end_.lat_)/2, (start_.lon_+end_.lon_)/2);
  }

  double NewLat(int picked) {
    if (picked == 0) {
      return start_.lat_;
    }
    if (picked == base_) {
      return end_.lat_;
    }
    auto& visited = visited_;
    auto& start = start_;
    auto& end = end_;
    auto probability = [&visited, &start, &end] (double lat) {
      auto weight = [&visited, &start, &end] (double lat) {
        auto min_distance = [&visited, lat] (double lon) {
          return visited.MinDistance(Point(lat, lon)) * cos(Radians(lat));
        };
        return Integral(start.lon_, end.lon_, 1000, min_distance);
      };
      return Integral(start.lat_, lat, 1000, weight);
    };
    auto total = probability(end_.lat_);
    auto goal = total / base_ * picked;
    return BinarySearch(start_.lat_, end_.lat_, goal, total/1000, probability);
  }

  double NewLon(int picked) {
    if (picked == 0) {
      return start_.lon_;
    }
    if (picked == base_) {
      return end_.lon_;
    }
    auto& visited = visited_;
    auto& start = start_;
    auto& end = end_;
    auto probability = [&visited, &start, &end] (double lon) {
      auto weight = [&visited, &start, &end] (double lon) {
        auto min_distance = [&visited, lon] (double lat) {
          return visited.MinDistance(Point(lat, lon)) * cos(Radians(lat));
        };
        return Integral(start.lat_, end.lat_, 1000, min_distance);
      };
      return Integral(start.lon_, lon, 1000, weight);
    };
    auto total = probability(end_.lon_);
    auto goal = total / base_ * picked;
    return BinarySearch(start_.lon_, end_.lon_, goal, total/1000, probability);
  }
private:
  int base_;
  Visited visited_;
  Point start_;
  Point end_;
};

#endif
