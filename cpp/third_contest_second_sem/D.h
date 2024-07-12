#ifndef ITERATOR_TRAITS_H
#define ITERATOR_TRAITS_H

#include <type_traits>
#include <list>
#include <vector>
#include <iterator>
#include <forward_list>
#include <iostream>

template <class T, class = void>
struct KIsDereferenceable : public std::false_type {};

template <class T>
struct KIsDereferenceable<T, std::void_t<decltype(*std::declval<T>())>> : public std::true_type {};

template <class T>
constexpr inline bool kIsDereferenceableV = KIsDereferenceable<T>::value;

template <class T, class = void>
struct KIsIncrementable : public std::false_type {};

template <class T>
struct KIsIncrementable<T, std::void_t<decltype(++std::declval<T&>())>> : public std::true_type {};

template <class T, class = void>
struct KIsIncrementable2 : public std::false_type {};

template <class T>
struct KIsIncrementable2<T, std::void_t<decltype(std::declval<T&>()++)>> : public std::true_type {};

template <class T>
constexpr inline bool kIsIncrementableV = KIsIncrementable2<T>::value && KIsIncrementable<T>::value;

template <class T, class = void>
struct KIsDecrementable : public std::false_type {};

template <class T>
struct KIsDecrementable<T, std::void_t<decltype(--std::declval<T&>())>> : public std::true_type {};

template <class T, class = void>
struct KIsDecrementable2 : public std::false_type {};

template <class T>
struct KIsDecrementable2<T, std::void_t<decltype(std::declval<T&>()--)>> : public std::true_type {};

template <class T>
constexpr inline bool kIsDecrementableV = KIsDecrementable2<T>::value && KIsDecrementable<T>::value;

template <class T, class = void>
struct KIsArrowDereferenceable : public std::false_type {};

template <class T>
struct KIsArrowDereferenceable<T, std::void_t<decltype(std::declval<T>().operator->())>> : public std::true_type {};

template <class T>
struct KIsArrowDereferenceable<T*> : public std::true_type {};

template <class T>
constexpr inline bool kIsArrowDereferenceableV = KIsArrowDereferenceable<T>::value;

template <class T, class = void>
struct KIsEqualityComparable : public std::false_type {};

template <class T>
struct KIsEqualityComparable<T, std::void_t<decltype(static_cast<bool>(std::declval<T>() == std::declval<T>()))>>
    : public std::true_type {};  // NOLINT

template <class T>
constexpr inline bool kIsEqualityComparableV = KIsEqualityComparable<T>::value;

template <class T, class = void>
struct KIsOrdered : public std::false_type {};

template <class T>
struct KIsOrdered<T, std::void_t<decltype(static_cast<bool>(std::declval<T>() < std::declval<T>()))>>
    : public std::true_type {};

template <class T>
constexpr inline bool kIsOrderedV = KIsOrdered<T>::value;

template <class T, class = void>
struct KIsSubtractable : public std::false_type {};

template <class T>
struct KIsSubtractable<T, std::void_t<decltype(std::declval<T>() - std::declval<T>())>> : public std::true_type {};

template <class T>
constexpr inline bool kIsSubtractableV = KIsSubtractable<T>::value;

template <class T, class = void>
struct Difference {
  using Type = void;
};

template <class T>
struct Difference<T, std::void_t<decltype(std::declval<T>() - std::declval<T>())>> {
  using Type = decltype(std::declval<T>() - std::declval<T>());
};

template <typename T>
using DifferenceType = typename Difference<T>::Type;

template <class T, class = void>
struct KHasIntegralArithmetic1 : public std::false_type {};

template <class T>
struct KHasIntegralArithmetic1<T, std::void_t<decltype(std::declval<T&>() += std::declval<DifferenceType<T>>())>>
    : public std::true_type {};

template <class T, class = void>
struct KHasIntegralArithmetic2 : public std::false_type {};

template <class T>
struct KHasIntegralArithmetic2<T, std::void_t<decltype(std::declval<T&>() -= std::declval<DifferenceType<T>>())>>
    : public std::true_type {};

template <class T>
constexpr inline bool kHasIntegralArithmeticV =
    KHasIntegralArithmetic1<T>::value && KHasIntegralArithmetic2<T>::value && std::is_integral_v<DifferenceType<T>>;

template <class T, class = void>
struct KIsSubscriptable : public std::false_type {};

template <class T>
struct KIsSubscriptable<T, std::void_t<decltype(std::declval<T>()[1])>> : public std::true_type {};

template <class T>
constexpr inline bool kIsSubscriptableV = KIsSubscriptable<T>::value && std::is_integral_v<DifferenceType<T>>;

template <class T, class = void>
struct KHasDestructor : public std::false_type {};

template <class T>
struct KHasDestructor<T, std::void_t<decltype(std::declval<T>().~T())>> : public std::true_type {};

template <class T, class = void>
struct KHasCopyAssigment : public std::false_type {};

template <class T>
struct KHasCopyAssigment<T, std::void_t<decltype(std::declval<T&>() = std::declval<const T&>())>>
    : public std::true_type {};

template <class T, class = void>
struct KHasCopyConstructor : public std::false_type {};

template <class T>
struct KHasCopyConstructor<T, std::void_t<decltype(T(std::declval<T>()))>> : public std::true_type {};

template <class T>
constexpr inline bool kIsIteratorV = KHasDestructor<T>::value && KHasCopyAssigment<T>::value &&
                                     KHasCopyConstructor<T>::value && kIsIncrementableV<T> && kIsDereferenceableV<T>;

template <class T>
constexpr inline bool kIsInputIteratorV = kIsIteratorV<T> && kIsArrowDereferenceableV<T> && kIsEqualityComparableV<T>;

template <class T, class = void>
struct KHasDefaultConstructor : public std::false_type {};

template <class T>
struct KHasDefaultConstructor<T, std::void_t<decltype(T())>> : public std::true_type {};

template <class T>
constexpr inline bool kIsForwardIteratorV = kIsInputIteratorV<T> && KHasDefaultConstructor<T>::value;

template <class T>
constexpr inline bool kIsBidirectionalIteratorV = kIsForwardIteratorV<T> && kIsDecrementableV<T>;

template <class T>
constexpr inline bool kIsRandomAccessIteratorV = kIsBidirectionalIteratorV<T> && kIsSubtractableV<T> &&
                                                 kHasIntegralArithmeticV<T> && kIsOrderedV<T> && kIsSubscriptableV<T>;

#endif