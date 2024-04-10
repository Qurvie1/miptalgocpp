#include "../line.h"
#include "../vector.h"
namespace geometry {

Line::Line() : a(0), b(0), c(0) {
}

Line::~Line() = default;

Line::Line(const Point& first, const Point& second) {
  first_ = first;
  second_ = second;
  a = first.y - second.y;
  b = second.x - first.x;
  c = first.x * second.y - second.x * first.y;
}

Line& Line::Move(const Vector& vec) {
  first_.Move(vec);
  second_.Move(vec);
  a = first_.y - second_.y;
  b = second_.x - first_.x;
  c = first_.x * second_.y - second_.x * first_.y;
  return *this;
}

bool Line::ContainsPoint(const Point& pt) const {
  return a * pt.x + b * pt.y + c == 0;
}

bool Line::CrossesSegment(const Segment& seg) const {
  return ((a * seg.a.x + b * seg.a.y + c) >= 0 && (a * seg.b.x + b * seg.b.y + c) <= 0) || 
         ((a * seg.a.x + b * seg.a.y + c) <= 0 && (a * seg.b.x + b * seg.b.y + c) >= 0);
}

Line* Line::Clone() const {
  auto* line = new Line{first_, second_};
  return line;
}

std::string Line::ToString() const {
  std::string string = "Line(" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ")";
  return string;
}

}