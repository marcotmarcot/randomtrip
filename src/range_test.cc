#include <cmath>
#include <iostream>

#include "test.h"

#include "range.h"

int main(int argc, char **argv) {
  auto y = BinarySearch(0, 10, 4, 0.000001, [] (double x) {
      return x * x;
    });
  eq("binary search square", y, 2);

  y = BinarySearch(0, 100, 9, 0.000001, [] (double x) {
      auto s = sqrt(x + 7);
      return s * s;
    });
  eq("binary search complex", y, 2);

  y = Integral(0, 10, 1000000, [] (double x) {
      return x;
    });
  eq("integral x", y, 50);

  y = Integral(0, M_PI, 1000000, [] (double x) {
      return cos(x);
    });
  eq("integral cos", y, 0);

  Visited vno({});
  eq("latno 0", NewLat(vno, Point(-90, -180), Point(90, 180), 6, 0), -90);
  eq("latno 1", NewLat(vno, Point(-90, -180), Point(90, 180), 6, 1), -41.8);
  eq("latno 2", NewLat(vno, Point(-90, -180), Point(90, 180), 6, 2), -19.5);
  eq("latno 3", NewLat(vno, Point(-90, -180), Point(90, 180), 6, 3), -0);
  eq("latno 4", NewLat(vno, Point(-90, -180), Point(90, 180), 6, 4), 19.5);
  eq("latno 5", NewLat(vno, Point(-90, -180), Point(90, 180), 6, 5), 41.8);
  eq("latno 6", NewLat(vno, Point(-90, -180), Point(90, 180), 6, 6), 90);

  Point bh(-19.9178576, -44.0305233);
  Visited vbh({bh});
  eq("latbh 0", NewLat(vbh, Point(-90, -180), Point(90, 180), 6, 0), -90);
  ne("latbh 1", NewLat(vbh, Point(-90, -180), Point(90, 180), 6, 1), -41.8);
  ne("latbh 2", NewLat(vbh, Point(-90, -180), Point(90, 180), 6, 2), -19.5);
  ne("latbh 3", NewLat(vbh, Point(-90, -180), Point(90, 180), 6, 3), -0);
  ne("latbh 4", NewLat(vbh, Point(-90, -180), Point(90, 180), 6, 4), 19.5);
  ne("latbh 5", NewLat(vbh, Point(-90, -180), Point(90, 180), 6, 5), 41.8);
  eq("latbh 6", NewLat(vbh, Point(-90, -180), Point(90, 180), 6, 6), 90);

  eq("lonno 0", NewLon(vno, Point(-90, -180), Point(90, 180), 6, 0), -180);
  eq("lonno 1", NewLon(vno, Point(-90, -180), Point(90, 180), 6, 1), -120);
  eq("lonno 2", NewLon(vno, Point(-90, -180), Point(90, 180), 6, 2), -60);
  eq("lonno 3", NewLon(vno, Point(-90, -180), Point(90, 180), 6, 3), -0);
  eq("lonno 4", NewLon(vno, Point(-90, -180), Point(90, 180), 6, 4), 60);
  eq("lonno 5", NewLon(vno, Point(-90, -180), Point(90, 180), 6, 5), 120);
  eq("lonno 6", NewLon(vno, Point(-90, -180), Point(90, 180), 6, 6), 180);

  eq("lonbh 0", NewLon(vbh, Point(-90, -180), Point(90, 180), 6, 0), -180);
  ne("lonbh 1", NewLon(vbh, Point(-90, -180), Point(90, 180), 6, 1), -120);
  ne("lonbh 2", NewLon(vbh, Point(-90, -180), Point(90, 180), 6, 2), -60);
  ne("lonbh 3", NewLon(vbh, Point(-90, -180), Point(90, 180), 6, 3), -0);
  ne("lonbh 4", NewLon(vbh, Point(-90, -180), Point(90, 180), 6, 4), 60);
  ne("lonbh 5", NewLon(vbh, Point(-90, -180), Point(90, 180), 6, 5), 120);
  eq("lonbh 6", NewLon(vbh, Point(-90, -180), Point(90, 180), 6, 6), 180);
  return 0;
}
