#ifndef ISHAPE_H_
#define ISHAPE_H_

#include "vector.h"

namespace geometry {
class Point;
class Segment;
class IShape {
 public:
  virtual IShape& Move(const Vector&) = 0;
  virtual bool ContainsPoint(const Point&) const = 0;
  virtual bool CrossesSegment(const Segment&) const = 0;
  virtual IShape* Clone() const = 0;
  virtual std::string ToString() const = 0;
  virtual ~IShape() = 0;
};

}

#endif