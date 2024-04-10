#include "../ray.h"

namespace geometry {
Ray::Ray() : a(Point()), b(Point()) {
}

Ray::~Ray() = default;

Ray::Ray(const Point& first, const Point& second) : a(first), b(second) {
}

Ray& Ray::Move(const Vector& vector) {
  a.Move(vector);
  b.Move(vector);
  return *this;
}

bool Ray::ContainsPoint(const Point& pt) const {
  Vector c{b.x - a.x, b.y - a.y};
  Vector d{pt.x - a.x, pt.y - a.y};
  bool fl1 = (b.x - a.x > 0 ? (pt.x - a.x) >= 0 : (a.x - pt.x) >= 0) && (b.x - a.x != 0);
  bool fl2 = (b.y - a.y > 0 ? (pt.y - a.y) >= 0 : (a.y - pt.y) >= 0) && (b.y - a.y != 0);
  return (c.OuterProduct(d) == 0) && (fl1 || fl2);
}

bool Ray::CrossesSegment(const Segment& seg) const {
  if (ContainsPoint(seg.a) || ContainsPoint(seg.b)) {
    return true;
  }
  Vector v1(a.x - seg.a.x, a.y - seg.a.y);
  Vector v2(seg.b.x - seg.a.x, seg.b.y - seg.a.y);
  Vector v3(b.x - a.x, b.y - a.y);
  Vector v4(seg.a.x - a.x, seg.a.y - a.y);
  Vector v5(seg.b.x - a.x, seg.b.y - a.y);
  Vector v6(seg.a.x - b.x, seg.a.y - b.y);
  Vector v7(seg.b.x - b.x, seg.b.y - b.y);
  return (v1.OuterProduct(v2) * v3.OuterProduct(v2) < 0) && (v4.OuterProduct(v5) * v6.OuterProduct(v7) < 0);
}

Ray* Ray::Clone() const {
  auto* ray = new Ray{a, b};
  return ray;
}

std::string Ray::ToString() const {
  std::string string = "Ray(" + a.ToString() + ", " + "Vector(" + std::to_string(b.x - a.x) + ", " +
                       std::to_string(b.y - a.y) + ")" + ")";
  return string;
}

}