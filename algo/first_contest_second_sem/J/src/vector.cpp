#include "../vector.h"
namespace geometry {

Vector::Vector() : x(0), y(0) {
}

Vector::Vector(int64_t x1, int64_t y1) : x(x1), y(y1) {
}

Vector Vector::operator+() const {
  return {x, y};
}

Vector Vector::operator-() const {
  return {-x, -y};
}

Vector& Vector::operator+=(const Vector& other) {
  x += other.x;
  y += other.y;
  return *this;
}

Vector& Vector::operator-=(const Vector& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

Vector& Vector::operator*=(int64_t val) {
  x *= val;
  y *= val;
  return *this;
}

Vector& Vector::operator/=(int64_t val) {
  x /= val;
  y /= val;
  return *this;
}

int64_t Vector::DotProduct(const Vector& other) const {
  return x * other.x + y * other.y;
}

int64_t Vector::OuterProduct(const Vector& other) const {
  return x * other.y - y * other.x;
}

Vector operator+(const Vector& first, const Vector& second) {
  return {first.x + second.x, first.y + second.y};
}

Vector operator-(const Vector& first, const Vector& second) {
  return {first.x - second.x, first.y - second.y};
}

Vector operator*(int64_t val, const Vector& vector) {
  return {val * vector.x, val * vector.y};
}

Vector operator*(const Vector& vector, int64_t val) {
  return {val * vector.x, val * vector.y};
}

Vector operator/(const Vector& vector, int64_t val) {
  return {vector.x / val, vector.y / val};
}

}