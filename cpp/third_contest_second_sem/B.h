#ifndef PRIME_H_
#define PRIME_H_
#include <cstddef>
#include <type_traits>

template <size_t N, size_t Left, size_t Right>
struct Sqrt {
  static constexpr size_t kValue =
      Sqrt<N, (((((Right + Left + 1) / 2) * ((Right + Left + 1) / 2) <= N)) ? ((Right + Left + 1) / 2) : Left),
           (((((Right + Left + 1) / 2) * ((Right + Left + 1) / 2) <= N)) ? Right
                                                                         : ((Right + Left + 1) / 2) - 1)>::kValue;
};

template <size_t N, size_t Left>
struct Sqrt<N, Left, Left> {
  static constexpr size_t kValue = Left;
};

template <size_t N>
inline const size_t kSqrtV = Sqrt<N, 0, (N > 100000000000 ? 100000000000 : N)>::kValue;

template <size_t N, size_t Left, size_t Right, size_t Mid = (Left + Right) / 2>
struct HasDivisorOnV
    : std::bool_constant<HasDivisorOnV<N, Left, Mid>::value || HasDivisorOnV<N, Mid + 1, Right>::value> {};

template <size_t N, size_t Left>
struct HasDivisorOnV<N, Left, Left, Left> : std::bool_constant<N % Left == 0> {};

template <size_t N>
struct HasDivisorOnV<N, 0, 0, 0> : std::false_type {};

template <size_t N, size_t Left, size_t Right>
inline const bool kHasDivisorOnV = HasDivisorOnV<N, Left, Right>::value;

template <size_t N>
struct IsPrime : std::bool_constant<!kHasDivisorOnV<N, 2, kSqrtV<N>>> {};

template <>
struct IsPrime<1> : std::false_type {};

template <>
struct IsPrime<2> : std::true_type {};

template <>
struct IsPrime<3> : std::true_type {};

template <size_t N>
inline const bool kIsPrimeV = IsPrime<N>::value;

#endif