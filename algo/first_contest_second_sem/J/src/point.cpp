#include "../segment.h"

namespace geometry {
Point::Point() : x(0), y(0) {
}

Point::Point(int64_t x1, int64_t y1) : x(x1), y(y1) {
}

Point::~Point() = default;

IShape::~IShape() = default;

Point& Point::Move(const Vector& vec) {
  x += vec.x;
  y += vec.y;
  return *this;
}

bool Point::ContainsPoint(const Point& pt) const {
  return pt.x == x && pt.y == y;
}

bool Point::CrossesSegment(const Segment& seg) const {
  return seg.ContainsPoint(*this);
}

Point* Point::Clone() const {
  auto* point = new Point{x, y};
  return point;
}

std::string Point::ToString() const {
  std::string string = "Point(" + std::to_string(x) + ", " + std::to_string(y) + ")";
  return string;
}

Point& Point::operator+=(Point& other) {
  x += other.x;
  y += other.y;
  return *this;
}

Vector operator-(const Point& first, const Point& second) {
  return {first.x - second.x, first.y - second.y};
}
bool operator==(const Point& first, const Point& second) {
  return first.x == second.x && first.y == second.y;
}

}