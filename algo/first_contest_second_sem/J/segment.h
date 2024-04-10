#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"
#include "ishape.h"

namespace geometry {
class Segment : public IShape {
 public:
  Point a;
  Point b;
  Segment();

  ~Segment() override;

  Segment(const Point&, const Point&);

  Segment& Move(const Vector& vec) override;

  bool OnSegment(const Point& p) const;

  bool ContainsPoint(const Point& pt) const override;

  bool Intersect(const Segment& other) const;

  bool CrossesSegment(const Segment& seg) const override;

  Segment* Clone() const override;

  std::string ToString() const override;

};

}

#endif