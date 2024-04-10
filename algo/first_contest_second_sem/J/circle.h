#ifndef CIRCLE_H
#define CIRCLE_H

#include "segment.h"
#include "line.h"

namespace geometry {
class Circle : public IShape {
 public:
  int64_t radius;
  Point center;
  Circle();

  ~Circle() override;

  Circle(const Point& pt, int64_t radius1);

  Circle& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  Circle* Clone() const override;

  std::string ToString() const override;

};

}

#endif