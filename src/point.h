#ifndef POINT_H
#define POINT_H

#include <sstream>

double Radians(double degrees) {
  return degrees / 180 * M_PI;
}

class Point {
public:
  Point(double lat, double lon) : lat_(lat), lon_(lon) {}

  Point(std::string arg) {
      std::stringstream coordinates;
      coordinates.str(arg);
      std::string lat;
      getline(coordinates, lat, ',');
      std::string lon;
      getline(coordinates, lon, ',');
      lat_ = stod(lat);
      lon_ = stod(lon);
  }

  std::string String() {
    std::ostringstream ss;
    ss << lat_ << "," << lon_;
    return ss.str();
  }

  double Distance(Point o) {
    // From http://www.movable-type.co.uk/scripts/latlong.html.
    auto p1 = Radians(lat_);
    auto p2 = Radians(o.lat_);
    auto dl = Radians(o.lon_ - lon_);
    auto r = 6371;
    return acos(sin(p1)*sin(p2) + cos(p1)*cos(p2)*cos(dl)) * r;
  }
  double lat_;
  double lon_;
};

#endif
