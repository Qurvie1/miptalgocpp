#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

namespace geometry {
class Vector {
 public:
  int64_t x;
  int64_t y;

  Vector();

  Vector(int64_t x1, int64_t y1);

  Vector operator+() const;

  Vector operator-() const;

  Vector& operator+=(const Vector& other);

  Vector& operator-=(const Vector& other);

  Vector& operator*=(int64_t val);

  Vector& operator/=(int64_t val);

  int64_t DotProduct(const Vector& other) const;

  int64_t OuterProduct(const Vector& other) const;

};

Vector operator+(const Vector& first, const Vector& second);

Vector operator-(const Vector& first, const Vector& second);

Vector operator*(int64_t val, const Vector& vector);

Vector operator*(const Vector& vector, int64_t val);

Vector operator/(const Vector& vector, int64_t val);

}

#endif