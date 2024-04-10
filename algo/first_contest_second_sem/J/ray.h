#ifndef RAY_H_
#define RAY_H_

#include "segment.h"

namespace geometry {
class Ray : public IShape {
 public:
  Point a;
  Point b;
  Ray();

  ~Ray() override;

  Ray(const Point&, const Point&);

  Ray& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  Ray* Clone() const override;

  std::string ToString() const override;

};

}

#endif