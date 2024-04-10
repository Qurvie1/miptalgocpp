#include "A.h"
#include <iostream>
#include <numeric>
#include <sstream>

Rational::Rational() : numerator_(0), denominator_(1) {
}

Rational::Rational(int32_t number) : numerator_(number), denominator_(1) {
}

Rational::Rational(int32_t first, int32_t second) : numerator_(first), denominator_(second) {
  Reduce();
}

void Rational::Reduce() {
  if (denominator_ == 0) {
    throw RationalDivisionByZero{};
  }
  if (denominator_ < 0) {
    denominator_ = -denominator_;
    numerator_ = -numerator_;
  }
  int32_t gcd = std::gcd(denominator_, numerator_);
  denominator_ /= gcd;
  numerator_ /= gcd;
}

int32_t Rational::GetDenominator() const {
  return denominator_;
}

int32_t Rational::GetNumerator() const {
  return numerator_;
}


void Rational::SetNumerator(int32_t number) {
  numerator_ = number;
  Reduce();
}

void Rational::SetNumeratorAndDenominator(int32_t number1, int32_t number2) {
  numerator_ = number1;
  denominator_ = number2;
  Reduce();
}

void Rational::SetDenominator(int32_t number) {
  denominator_ = number;
  Reduce();
}

Rational& operator++(Rational& number) {
  int32_t first = number.GetNumerator();
  int32_t second = number.GetDenominator();
  number.SetNumerator(first + second);
  return number;
}

Rational& operator--(Rational& number) {
  int32_t first = number.GetNumerator();
  int32_t second = number.GetDenominator();
  number.SetNumerator(first - second);
  return number;
}

Rational operator++(Rational& number, int32_t) {
  Rational answer = number;
  int32_t first = number.GetNumerator();
  int32_t second = number.GetDenominator();
  number.SetNumerator(first + second);
  return answer;
}

Rational operator--(Rational& number, int32_t) {
  Rational answer = number;
  int32_t first = number.GetNumerator();
  int32_t second = number.GetDenominator();
  number.SetNumerator(first - second);
  return answer;
}

Rational& operator+=(Rational& first, const Rational& second) {
  int32_t den1 = first.GetDenominator();
  int32_t den2 = second.GetDenominator();
  int32_t num1 = first.GetNumerator();
  int32_t num2 = second.GetNumerator();
  first.SetNumeratorAndDenominator(num1 * den2 + num2 * den1, den1 * den2);
  return first;
}

Rational& operator-=(Rational& first, const Rational& second) {
  int32_t den1 = first.GetDenominator();
  int32_t den2 = second.GetDenominator();
  int32_t num1 = first.GetNumerator();
  int32_t num2 = second.GetNumerator();
  first.SetNumeratorAndDenominator(num1 * den2 - num2 * den1, den1 * den2);
  return first;
}

Rational& operator*=(Rational& first, const Rational& second) {
  int32_t den1 = first.GetDenominator();
  int32_t den2 = second.GetDenominator();
  int32_t num1 = first.GetNumerator();
  int32_t num2 = second.GetNumerator();
  first.SetNumeratorAndDenominator(num1 * num2, den1 * den2);
  return first;
}

Rational& operator/=(Rational& first, const Rational& second) {
  int32_t den1 = first.GetDenominator();
  int32_t den2 = second.GetDenominator();
  int32_t num1 = first.GetNumerator();
  int32_t num2 = second.GetNumerator();
  first.SetNumeratorAndDenominator(num1 * den2, den1 * num2);
  return first;
}

Rational operator+(const Rational& first, const Rational& second) {
  int32_t num1 = first.GetNumerator() * second.GetDenominator();
  int32_t num2 = second.GetNumerator() * first.GetDenominator();
  int32_t den = first.GetDenominator() * second.GetDenominator();
  return {num1 + num2, den};
}

Rational operator-(const Rational& first, const Rational& second) {
  int32_t num1 = first.GetNumerator() * second.GetDenominator();
  int32_t num2 = second.GetNumerator() * first.GetDenominator();
  int32_t den = first.GetDenominator() * second.GetDenominator();
  return {num1 - num2, den};
}

Rational operator*(const Rational& first, const Rational& second) {
  return {first.GetNumerator() * second.GetNumerator(), first.GetDenominator() * second.GetDenominator()};
}

Rational operator/(const Rational& first, const Rational& second) {
  return {first.GetNumerator() * second.GetDenominator(), first.GetDenominator() * second.GetNumerator()};
}

Rational Rational::operator+() const {
  return {numerator_, denominator_};
}

Rational Rational::operator-() const {
  return {-numerator_, denominator_};
}

bool operator==(const Rational& first, const Rational& second) {
  return (first.GetNumerator() == second.GetNumerator() && first.GetDenominator() == second.GetDenominator());
}

bool operator!=(const Rational& first, const Rational& second) {
  return (first.GetNumerator() != second.GetNumerator() || first.GetDenominator() != second.GetDenominator());
}

bool operator<(const Rational& first, const Rational& second) {
  return (first.GetNumerator() * second.GetDenominator() < first.GetDenominator() * second.GetNumerator());
}

bool operator>(const Rational& first, const Rational& second) {
  return (first.GetNumerator() * second.GetDenominator() > first.GetDenominator() * second.GetNumerator());
}

bool operator<=(const Rational& first, const Rational& second) {
  return (first.GetNumerator() * second.GetDenominator() <= first.GetDenominator() * second.GetNumerator());
}

bool operator>=(const Rational& first, const Rational& second) {
  return (first.GetNumerator() * second.GetDenominator() >= first.GetDenominator() * second.GetNumerator());
}

std::ostream& operator<<(std::ostream& out, const Rational& number) {
  int32_t num = number.GetNumerator();
  int32_t den = number.GetDenominator();
  if (den == 1) {
    out << num;
    return out;
  }
  out << num << '/' << den;
  return out;
}

std::istream& operator>>(std::istream& in, Rational& number) {
  int32_t first = 0;
  int32_t second = 0;
  char t = '0';
  in >> first;
  if (in.peek() != '/') {
    number = Rational(first);
    return in;
  }
  in >> t >> second;
  number = Rational(first, second);
  return in;
}