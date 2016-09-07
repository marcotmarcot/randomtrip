#ifndef RANGE_H
#define RANGE_H

#include <cmath>
#include "point.h"
#include "visited.h"

constexpr int processing = 100;

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

double NewLat(Visited visited, Point start, Point end, int base, int picked) {
  if (picked == 0) {
    return start.lat_;
  }
  if (picked == base) {
    return end.lat_;
  }
  auto probability = [&visited, &start, &end] (double lat) {
    auto weight = [&visited, &start, &end] (double lat) {
      auto min_distance = [&visited, lat] (double lon) {
        return visited.MinDistance(Point(lat, lon)) * cos(Radians(lat));
      };
      return Integral(start.lon_, end.lon_, processing, min_distance);
    };
    return Integral(start.lat_, lat, processing, weight);
  };
  auto total = probability(end.lat_);
  auto goal = total / base * picked;
  return BinarySearch(start.lat_, end.lat_, goal, total/processing, probability);
}

double NewLon(Visited visited, Point start, Point end, int base, int picked) {
  if (picked == 0) {
    return start.lon_;
  }
  if (picked == base) {
    return end.lon_;
  }
  auto probability = [&visited, &start, &end] (double lon) {
    auto weight = [&visited, &start, &end] (double lon) {
      auto min_distance = [&visited, lon] (double lat) {
        return visited.MinDistance(Point(lat, lon));
      };
      return Integral(start.lat_, end.lat_, processing, min_distance);
    };
    return Integral(start.lon_, lon, processing, weight);
  };
  auto total = probability(end.lon_);
  auto goal = total / base * picked;
  return BinarySearch(start.lon_, end.lon_, goal, total/processing, probability);
}

void AddPicked(Visited visited, int base, int picked, int is_lat, Point start, Point end, Point *new_start, Point *new_end) {
  *new_start = start;
  *new_end = end;
  if (is_lat) {
    new_start->lat_ = NewLat(visited, start, end, base, picked - 1);
    new_end->lat_ = NewLat(visited, start, end, base, picked);
  } else {
    new_start->lon_ = NewLon(visited, start, end, base, picked - 1);
    new_end->lon_ = NewLon(visited, start, end, base, picked);
  }
}

Point Highest(Visited visited, Point start, Point end) {
  Point point((end.lat_+start.lat_)/2, (end.lon_+start.lon_)/2);
  auto value = visited.MinDistance(point);
  auto lat_step = (end.lat_-start.lat_) / 1000;
  for (auto lat = start.lat_; lat <= end.lat_; lat += lat_step) {
    auto lon_step = (end.lon_-start.lon_) / 1000;
    for (auto lon = start.lon_; lon <= end.lon_; lon += lon_step) {
      Point p(lat, lon);
      auto v = visited.MinDistance(p);
      if (v > value) {
        point = p;
        value = v;
      }
    }
  }
  return point;
}

#endif
