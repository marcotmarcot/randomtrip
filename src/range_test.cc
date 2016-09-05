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

  Range latno(6, Visited({}));
  eq("latno 0", latno.NewLat(0), -90);
  eq("latno 1", latno.NewLat(1), -60);
  eq("latno 2", latno.NewLat(2), -30);
  eq("latno 3", latno.NewLat(3), 0);
  eq("latno 4", latno.NewLat(4), 30);
  eq("latno 5", latno.NewLat(5), 60);
  eq("latno 6", latno.NewLat(6), 90);

  Point bh(-19.9178576, -44.0305233);
  Range latbh(6, Visited({bh}));
  eq("latbh 0", latbh.NewLat(0), -90);
  ne("latbh 1", latbh.NewLat(1), -60);
  ne("latbh 2", latbh.NewLat(2), -30);
  ne("latbh 3", latbh.NewLat(3), 0);
  ne("latbh 4", latbh.NewLat(4), 30);
  ne("latbh 5", latbh.NewLat(5), 60);
  eq("latbh 6", latbh.NewLat(6), 90);

  Range lonno(6, Visited({}));
  eq("lonno 0", lonno.NewLon(0), -180);
  eq("lonno 1", lonno.NewLon(1), -120);
  eq("lonno 2", lonno.NewLon(2), -60);
  eq("lonno 3", lonno.NewLon(3), 0);
  eq("lonno 4", lonno.NewLon(4), 60);
  eq("lonno 5", lonno.NewLon(5), 120);
  eq("lonno 6", lonno.NewLon(6), 180);

  Range lonbh(6, Visited({bh}));
  eq("lonbh 0", lonbh.NewLon(0), -180);
  ne("lonbh 1", lonbh.NewLon(1), -120);
  ne("lonbh 2", lonbh.NewLon(2), -60);
  ne("lonbh 3", lonbh.NewLon(3), 0);
  ne("lonbh 4", lonbh.NewLon(4), 60);
  ne("lonbh 5", lonbh.NewLon(5), 120);
  eq("lonbh 6", lonbh.NewLon(6), 180);
  return 0;
}
