#ifndef ARRAY_TRAITS_H
#define ARRAY_TRAITS_H

#include <cstddef>
#include <type_traits>

template <class T>
struct kIsArray : std::integral_constant<bool, false> {};  // NOLINT

template <class T>
struct kIsArray<T[]> : std::integral_constant<bool, true> {};

template <class T, size_t N>
struct kIsArray<T[N]> : std::integral_constant<bool, true> {};

template <class T>
constexpr inline bool kIsArrayV = kIsArray<T>::value;

template <class T>
struct KRank : std::integral_constant<size_t, 0> {};

template <class T>
struct KRank<T[]> : std::integral_constant<size_t, KRank<T>::value + 1> {};

template <class T, size_t N>
struct KRank<T[N]> : std::integral_constant<size_t, KRank<T>::value + 1> {};

template <class T>
constexpr inline size_t kRankV = KRank<T>::value;

template <class T>
struct kSize : std::integral_constant<size_t, 1> {};  // NOLINT

template <class T>
struct kSize<T[]> : std::integral_constant<size_t, 0> {};

template <class T, size_t N>
struct kSize<T[N]> : std::integral_constant<size_t, N> {};

template <class T>
constexpr inline size_t kSizeV = kSize<T>::value;

template <class T>
struct kTotalSize : std::integral_constant<size_t, 1> {};  // NOLINT

template <class T>
struct kTotalSize<T[]> : std::integral_constant<size_t, 0> {};

template <class T, size_t N>
struct kTotalSize<T[N]> : std::integral_constant<size_t, N * kTotalSize<T>::value> {};

template <class T>
constexpr inline size_t kTotalSizeV = kTotalSize<T>::value;

template <class T>
struct RemoveArray {
  using Type = T;
};

template <class T>
struct RemoveArray<T[]> {
  using Type = T;
};

template <class T, size_t N>
struct RemoveArray<T[N]> {
  using Type = T;
};

template <class T>
using RemoveArrayT = typename RemoveArray<T>::Type;

template <class T>
struct RemoveAllArrays {
  using Type = T;
};

template <class T>
struct RemoveAllArrays<T[]> {
  using Type = typename RemoveAllArrays<T>::Type;
};

template <class T, size_t N>
struct RemoveAllArrays<T[N]> {
  using Type = typename RemoveAllArrays<T>::Type;
};

template <class T>
using RemoveAllArraysT = typename RemoveAllArrays<T>::Type;

#endif