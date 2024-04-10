#include "../circle.h"
#include "../line.h"
#include <cmath>
#include <algorithm>

namespace geometry {
Circle::Circle() : radius(0), center(Point()) {
}

Circle::~Circle() = default;

Circle::Circle(const Point& pt, int64_t radius1) : radius(radius1), center(pt) {
}

Circle& Circle::Move(const Vector& vector) {
  center.Move(vector);
  return *this;
}

bool Circle::ContainsPoint(const Point& pt) const {
  return ((pt.x - center.x) * (pt.x - center.x) + (pt.y - center.y) * (pt.y - center.y)) <= radius * radius;
}

bool Circle::CrossesSegment(const Segment& seg) const {
  if (this->ContainsPoint(seg.a) && !this->ContainsPoint(seg.b)) {
    return true;
  }
  if ((seg.a.x - center.x) * (seg.a.x - center.x) + (seg.a.y - center.y) * (seg.a.y - center.y) < radius * radius &&
      (seg.b.x - center.x) * (seg.b.x - center.x) + (seg.b.y - center.y) * (seg.b.y - center.y) < radius * radius) {
    return false;
  }
  if ((seg.a.x - center.x) * (seg.a.x - center.x) + (seg.a.y - center.y) * (seg.a.y - center.y) == radius * radius ||
      (seg.b.x - center.x) * (seg.b.x - center.x) + (seg.b.y - center.y) * (seg.b.y - center.y) == radius * radius) {
    return true;
  }
  int64_t dx = seg.b.x - seg.a.x;
  int64_t dy = seg.b.y - seg.a.y;
  int64_t a = dx * dx + dy * dy;
  int64_t b = 2 * (dx * (seg.a.x - center.x) + dy * (seg.a.y - center.y));
  int64_t c = center.x * center.x + center.y * center.y + seg.a.x * seg.a.x + seg.a.y * seg.a.y
             - 2 * (center.x * seg.a.x + center.y * seg.a.y) - radius * radius;

  int64_t disc = b * b - 4 * a * c;
  if (disc < 0) {
    return false;
  }
  if (disc == 0) {
    return ((b >= 0 && a < 0 && b <= -2 * a) || (b <= 0 && a > 0 && -b <= 2 * a));
  }
  double sqdisc = sqrt(static_cast<double>(disc));
  double t1 = (static_cast<double>(-b) + sqdisc) / (static_cast<double>(2 * a));
  double t2 = (static_cast<double>(-b) - sqdisc) / (static_cast<double>(2 * a));

  return (t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1);
}

Circle* Circle::Clone() const {
  auto* circle = new Circle{center, radius};
  return circle;
}

std::string Circle::ToString() const {
  std::string string = "Circle(" + center.ToString() + ", " + std::to_string(radius) + ")";
  return string;
}

}