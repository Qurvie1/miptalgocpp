#ifndef POINT_H_
#define POINT_H_

#include "ishape.h"

namespace geometry {
class Point : public IShape {
 public:
  int64_t x;
  int64_t y;
  Point();

  ~Point() override;

  Point(int64_t x1, int64_t y1);

  Point& Move(const Vector& vec) override;

  bool ContainsPoint(const Point& pt) const override;

  bool CrossesSegment(const Segment& seg) const override;

  Point* Clone() const override;

  std::string ToString() const override;

  Point& operator+=(Point& other);

};

Vector operator-(const Point& first, const Point& second);

bool operator==(const Point& first, const Point& second);

}

#endif