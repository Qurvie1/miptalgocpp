#include "../polygon.h"

namespace geometry {
Polygon::Polygon() = default;

Polygon::~Polygon() = default;

Polygon::Polygon(const std::vector<Point>& array) : points(array) {
}

Polygon& Polygon::Move(const Vector& vector) {
  for (size_t i = 0; i < points.size(); ++i) {
    points[i].Move(vector);
  }
  return *this;
}

bool Polygon::ContainsPoint(const Point& point) const {
  int64_t min_x = 0;
  for (const Point& p : points) {
    if (p.x < min_x) {
      min_x = p.x;
    }
  }
  min_x -= 10;
  Point other{min_x, point.y + 1};
  Point first = points[0];
  Point second = points[1];
  int64_t intersections = 0;
  for (size_t i = 1; i < points.size() + 1; ++i) {
    Segment seg{first, second};
    Segment seg1{point, other};
    Vector v1{first.x - point.x, first.y - point.y};
    Vector v2{second.x - point.x, second.y - point.y};
    if (seg.OnSegment(point) && (v1.OuterProduct(v2) == 0)) {
      return true;
    }
    intersections += seg1.CrossesSegment(seg);
    first = second;
    second = points[(i + 1) % points.size()];
  }
  return intersections % 2;
}

bool Polygon::CrossesSegment(const Segment& seg) const {
  for (size_t i = 0; i < points.size(); ++i) {
    Segment border{points[i], points[(i + 1) % points.size()]};
    if (border.CrossesSegment(seg)) {
      return true;
    }
  }
  return false;
}

Polygon* Polygon::Clone() const {
  auto* polygon = new Polygon{points};
  return polygon;
}

std::string Polygon::ToString() const {
  std::string string = "Polygon(";
  for (size_t i = 0; i < points.size() - 1; ++i) {
    string += points[i].ToString() + ", ";
  }
  string += points[points.size() - 1].ToString() + ")";
  return string;
}

}