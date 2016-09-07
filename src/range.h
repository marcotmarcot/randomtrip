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
      return Integral(start.lon_, end.lon_, 1000, min_distance);
    };
    return Integral(start.lat_, lat, 1000, weight);
  };
  auto total = probability(end.lat_);
  auto goal = total / base * picked;
  return BinarySearch(start.lat_, end.lat_, goal, total/1000, probability);
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
      return Integral(start.lat_, end.lat_, 1000, min_distance);
    };
    return Integral(start.lon_, lon, 1000, weight);
  };
  auto total = probability(end.lon_);
  auto goal = total / base * picked;
  return BinarySearch(start.lon_, end.lon_, goal, total/1000, probability);
}

void AddPicked(Visited visited, int base, int picked, int is_lat, double slat, double slon, double elat, double elon, double* new_slat, double *new_slon, double *new_elat, double *new_elon) {
  Point start(slat, slon);
  Point end(elat, elon);
  if (is_lat) {
    *new_slat = NewLat(visited, start, end, base, picked - 1);
    *new_elat = NewLat(visited, start, end, base, picked);
    *new_slon = slon;
    *new_elon = elon;
  } else {
    *new_slat = slat;
    *new_elat = elat;
    *new_slon = NewLon(visited, start, end, base, picked - 1);
    *new_elon = NewLon(visited, start, end, base, picked);
  }
}

#endif
