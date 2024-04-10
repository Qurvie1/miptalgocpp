#ifndef LINE_H_
#define LINE_H_

#include "segment.h"

namespace geometry {
class Line : public IShape {
 public:
  int64_t a;
  int64_t b;
  int64_t c;

  Point first_;
  Point second_;

  Line();

  ~Line() override;

  Line(const Point&, const Point&);

  Line& Move(const Vector&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const Segment&) const override;

  Line* Clone() const override;

  std::string ToString() const override;

};

}

#endif