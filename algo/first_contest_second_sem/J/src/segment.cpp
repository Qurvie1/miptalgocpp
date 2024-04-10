#include "../segment.h"

namespace geometry {

Segment::Segment(const Point& a1, const Point& b1) : a(a1), b(b1) {
}

Segment::Segment() : a(Point()), b(Point()) {
}

Segment::~Segment() = default;


Segment& Segment::Move(const Vector& vec) {
  a.Move(vec);
  b.Move(vec);
  return *this;
}

bool Segment::OnSegment(const Point& p) const {
  return (std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x)) &&
         (std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y));
}

bool Segment::ContainsPoint(const Point& pt) const {
  Vector first{pt.x - a.x, pt.y - a.y};
  Vector second{b.x - a.x, b.y - a.y};
  return first.OuterProduct(second) == 0 && OnSegment(pt);
}

bool Segment::Intersect(const Segment& other) const {
  Vector v1(a.x - other.a.x, a.y - other.a.y);
  Vector v2(other.b.x - other.a.x, other.b.y - other.a.y);
  Vector v3(b.x - a.x, b.y - a.y);
  Vector v4(other.a.x - a.x, other.a.y - a.y);
  Vector v5(b.x - other.a.x, b.y - other.a.y);
  Vector v6(other.b.x - a.x, other.b.y - a.y);
  int64_t d1 = v1.OuterProduct(v2);
  int64_t d2 = v5.OuterProduct(v2);
  int64_t d3 = v4.OuterProduct(v3);
  int64_t d4 = v6.OuterProduct(v3);
  if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
    return true;
  }
  return ((d1 == 0 && other.OnSegment(a)) || (d2 == 0 && other.OnSegment(b)) ||
          (d3 == 0 && this->OnSegment(other.a)) || (d4 == 0 && this->OnSegment(other.b)));
}

bool Segment::CrossesSegment(const Segment& seg) const {
  return Intersect(seg);
}

Segment* Segment::Clone() const {
  auto* segment = new Segment{a, b};
  return segment;
}

std::string Segment::ToString() const {
  std::string string = "Segment(" + a.ToString() + ", " + b.ToString() + ")";
  return string;
}

}