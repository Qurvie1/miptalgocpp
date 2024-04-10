#include <stdexcept>

#ifndef RATIONAL
#define RATIONAL

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 private:
  int32_t numerator_;
  int32_t denominator_;
 public:
  Rational();

  Rational(int32_t); // NOLINT

  Rational(int32_t, int32_t);

  int32_t GetNumerator() const;

  int32_t GetDenominator() const;

  void SetNumerator(int32_t);
  
  void SetNumeratorAndDenominator(int32_t, int32_t);

  void SetDenominator(int32_t);

  Rational operator+() const;

  Rational operator-() const;

  void Reduce();
};

std::ostream& operator<<(std::ostream&, const Rational&);

std::istream& operator>>(std::istream&, Rational&);

Rational& operator++(Rational&);

Rational& operator--(Rational&);

Rational operator++(Rational&, int32_t);

Rational operator--(Rational&, int32_t);

Rational& operator+=(Rational&, const Rational&);

Rational& operator-=(Rational&, const Rational&);

Rational& operator*=(Rational&, const Rational&);

Rational& operator/=(Rational&, const Rational&);

Rational operator+(const Rational&, const Rational&);

Rational operator-(const Rational&, const Rational&);

Rational operator*(const Rational&, const Rational&);

Rational operator/(const Rational&, const Rational&);

bool operator==(const Rational&, const Rational&);

bool operator!=(const Rational&, const Rational&);

bool operator>(const Rational&, const Rational&);

bool operator<(const Rational&, const Rational&);

bool operator<=(const Rational&, const Rational&);

bool operator>=(const Rational&, const Rational&);

#endif