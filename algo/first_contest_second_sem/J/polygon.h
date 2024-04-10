#ifndef POLYGON_H_
#define POLYGON_H_

#include "segment.h"

namespace geometry {
class Polygon : public IShape {
 public:
  std::vector<Point> points;
  Polygon();

  ~Polygon() override;

  explicit Polygon(const std::vector<Point>&);

  Polygon& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  Polygon* Clone() const override;

  std::string ToString() const override;
};

}

#endif