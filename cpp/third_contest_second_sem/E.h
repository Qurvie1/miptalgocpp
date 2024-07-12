#ifndef TYPE_VECTOR_H
#define TYPE_VECTOR_H

#define ALGORITHMS_IMPLEMENTED

#define SORT_IMPLEMENTED

#include <iostream>
#include <type_traits>
#include <algorithm>
#include <vector>

template <typename... Types>
struct TypeVector {};

template <typename TV>
struct Size;

template <typename... Types>
struct Size<TypeVector<Types...>> {
  static constexpr size_t Value = sizeof...(Types);  // NOLINT
};

template <typename TV>
struct Empty;

template <typename... Types>
struct Empty<TypeVector<Types...>> : std::false_type {};

template <>
struct Empty<TypeVector<>> : std::true_type {};

template <typename TV>
struct Front;

template <typename T, typename... Rest>
struct Front<TypeVector<T, Rest...>> {
  using Type = T;
};

template <typename TV>
struct Back;

template <typename T, typename... Rest>
struct Back<TypeVector<T, Rest...>> {
  using Type = typename Back<TypeVector<Rest...>>::Type;
};

template <typename T>
struct Back<TypeVector<T>> {
  using Type = T;
};

template <typename TV, size_t Idx, typename = void>
struct At;

template <typename T, typename... Types>
struct At<TypeVector<T, Types...>, 0> {
  using Type = T;
};

template <size_t Idx, typename T, typename... Types>
struct At<TypeVector<T, Types...>, Idx, std::void_t<typename At<TypeVector<Types...>, Idx - 1>::Type>> {
  using Type = typename At<TypeVector<Types...>, Idx - 1>::Type;
};

template <typename TV, typename T>
struct Contains;

template <typename T, typename U, typename... Types>
struct Contains<TypeVector<U, Types...>, T> {
  static constexpr bool value = (std::is_same_v<T, U> || Contains<TypeVector<Types...>, T>::value);  // NOLINT
};

template <typename T, typename U>
struct Contains<TypeVector<U>, T> {
  static constexpr bool value = std::is_same_v<T, U>;  // NOLINT
};

template <typename T>
struct Contains<TypeVector<>, T> : std::false_type {};

template <typename TV, typename T>
struct Count;

template <typename T, typename U, typename... Types>
struct Count<TypeVector<U, Types...>, T> {
  static constexpr size_t value = (std::is_same_v<T, U> + Count<TypeVector<Types...>, T>::value);  // NOLINT
};

template <typename T, typename U>
struct Count<TypeVector<U>, T> {
  static constexpr size_t value = std::is_same_v<T, U>;  // NOLINT
};

template <typename T>
struct Count<TypeVector<>, T> : std::integral_constant<size_t, 0> {};

template <typename TV, typename T>
struct PushFront;

template <typename T, typename... Types>
struct PushFront<TypeVector<Types...>, T> {
  using Type = TypeVector<T, Types...>;
};

template <typename TV, typename T>
struct PushBack;

template <typename T, typename... Types>
struct PushBack<TypeVector<Types...>, T> {
  using Type = TypeVector<Types..., T>;
};

template <typename TV>
struct PopFront;

template <typename T, typename... Types>
struct PopFront<TypeVector<T, Types...>> {
  using Type = TypeVector<Types...>;
};

template <typename TV>
struct PopBack;

template <typename T>
struct PopBack<TypeVector<T>> {
  using Type = TypeVector<>;
};

template <typename T, typename... Types>
struct PopBack<TypeVector<T, Types...>> {
  using Type = typename PushFront<typename PopBack<TypeVector<Types...>>::Type, T>::Type;
};

template <typename TV1, typename TV2>
struct Concatenate;

template <typename... Types1, typename... Types2>
struct Concatenate<TypeVector<Types1...>, TypeVector<Types2...>> {
  using Type = TypeVector<Types1..., Types2...>;
};

template <typename TV, size_t Idx, typename T, typename = void>
struct Insert;

template <typename T, typename... Args>
struct Insert<TypeVector<Args...>, 0, T> {
  using Type = TypeVector<T, Args...>;
};

template <size_t Idx, typename T, typename... Args>
struct Insert<TypeVector<Args...>, Idx, T, std::enable_if_t<(Idx && Idx <= sizeof...(Args))>> {
  using Type = typename PushFront<typename Insert<typename PopFront<TypeVector<Args...>>::Type, Idx - 1, T>::Type,
                                  typename Front<TypeVector<Args...>>::Type>::Type;
};

template <typename TV, typename T>
struct EraseFirst;

template <typename T, typename... Args, typename U>
struct EraseFirst<TypeVector<T, Args...>, U> {
  using Type = std::conditional_t<
      std::is_same_v<T, U>, TypeVector<Args...>,
      typename PushFront<typename EraseFirst<typename PopFront<TypeVector<T, Args...>>::Type, U>::Type, T>::Type>;
};

template <typename T, typename U>
struct EraseFirst<TypeVector<T>, U> {
  using Type = std::conditional_t<std::is_same_v<T, U>, TypeVector<>, TypeVector<T>>;
};

template <typename U>
struct EraseFirst<TypeVector<>, U> {
  using Type = TypeVector<>;
};

template <typename TV, typename T>
struct EraseAll;

template <typename T, typename... Args, typename U>
struct EraseAll<TypeVector<T, Args...>, U> {
  using Type = std::conditional_t<
      std::is_same_v<U, T>, typename EraseAll<typename PopFront<TypeVector<T, Args...>>::Type, U>::Type,
      typename PushFront<typename EraseAll<typename PopFront<TypeVector<T, Args...>>::Type, U>::Type, T>::Type>;
};

template <typename T, typename U>
struct EraseAll<TypeVector<T>, U> {
  using Type = std::conditional_t<std::is_same_v<T, U>, TypeVector<>, TypeVector<T>>;
};

template <typename U>
struct EraseAll<TypeVector<>, U> {
  using Type = TypeVector<>;
};

template <typename TV>
struct Reverse;

template <typename T, typename... Args>
struct Reverse<TypeVector<T, Args...>> {
  using Type = typename PushBack<typename Reverse<typename PopFront<TypeVector<T, Args...>>::Type>::Type, T>::Type;
};

template <>
struct Reverse<TypeVector<>> {
  using Type = TypeVector<>;
};

template <typename TV>
struct Unique;

template <typename T, typename... Args>
struct Unique<TypeVector<T, Args...>> {
  using Type = typename PushFront<typename Unique<typename EraseAll<TypeVector<T, Args...>, T>::Type>::Type, T>::Type;
};

template <>
struct Unique<TypeVector<>> {
  using Type = TypeVector<>;
};

template <typename TV, template <class> class F>
struct Transform;

template <typename T, template <class> class F, typename... Args>
struct Transform<TypeVector<T, Args...>, F> {
  using Type =
      typename PushFront<typename Transform<typename PopFront<TypeVector<T, Args...>>::Type, F>::Type, F<T>>::Type;
};

template <template <class> class F>
struct Transform<TypeVector<>, F> {
  using Type = TypeVector<>;
};

template <typename TV, template <class> class Predicate>
struct AllOf;

template <typename T, template <class> class Predicate, typename... Args>
struct AllOf<TypeVector<T, Args...>, Predicate> {
  static constexpr bool value = Predicate<T>::value && AllOf<TypeVector<Args...>, Predicate>::value;  // NOLINT
};

template <template <class> class Predicate>
struct AllOf<TypeVector<>, Predicate> {
  static constexpr bool value = true;  // NOLINT
};

template <typename TV, template <class> class Predicate>
struct AnyOf;

template <typename T, template <class> class Predicate, typename... Args>
struct AnyOf<TypeVector<T, Args...>, Predicate> {
  static constexpr bool value = Predicate<T>::value || AnyOf<TypeVector<Args...>, Predicate>::value;  // NOLINT
};

template <template <class> class Predicate>
struct AnyOf<TypeVector<>, Predicate> {
  static constexpr bool value = false;  // NOLINT
};

template <typename TV, template <class, class> class Compare>
struct MinElement;

template <typename T, typename... Args, template <class, class> class Compare>
struct MinElement<TypeVector<T, Args...>, Compare> {
  using Type = std::conditional_t<Compare<T, typename MinElement<TypeVector<Args...>, Compare>::Type>::value, T,
                                  typename MinElement<TypeVector<Args...>, Compare>::Type>;
};

template <typename T, typename U, template <class, class> class Compare>
struct MinElement<TypeVector<T, U>, Compare> {
  using Type = std::conditional_t<Compare<T, U>::value, T, U>;
};

template <typename T, template <class, class> class Compare>
struct MinElement<TypeVector<T>, Compare> {
  using Type = T;
};

template <typename TV, template <class, class> class Compare>
struct MaxElement;

template <typename T, typename... Args, template <class, class> class Compare>
struct MaxElement<TypeVector<T, Args...>, Compare> {
  using Type = std::conditional_t<Compare<typename MaxElement<TypeVector<Args...>, Compare>::Type, T>::value, T,
                                  typename MaxElement<TypeVector<Args...>, Compare>::Type>;
};

template <typename T, typename U, template <class, class> class Compare>
struct MaxElement<TypeVector<T, U>, Compare> {
  using Type = std::conditional_t<Compare<U, T>::value, T, U>;
};

template <typename T, template <class, class> class Compare>
struct MaxElement<TypeVector<T>, Compare> {
  using Type = T;
};

template <typename TV1, typename TV2, template <class, class> class Compare>
struct Merge;

template <typename T1, typename T2, typename... Args1, typename... Args2, template <class, class> class Compare>
struct Merge<TypeVector<T1, Args1...>, TypeVector<T2, Args2...>, Compare> {
  using Type = typename PushFront<
      std::conditional_t<Compare<T1, T2>::value,
                         typename Merge<TypeVector<Args1...>, TypeVector<T2, Args2...>, Compare>::Type,
                         typename Merge<TypeVector<T1, Args1...>, TypeVector<Args2...>, Compare>::Type>,
      std::conditional_t<Compare<T1, T2>::value, T1, T2>>::Type;
};

template <typename T, typename... Args, template <class, class> class Compare>
struct Merge<TypeVector<>, TypeVector<T, Args...>, Compare> {
  using Type = typename PushFront<typename Merge<TypeVector<>, TypeVector<Args...>, Compare>::Type, T>::Type;
};

template <typename T, typename... Args, template <class, class> class Compare>
struct Merge<TypeVector<T, Args...>, TypeVector<>, Compare> {
  using Type = typename PushFront<typename Merge<TypeVector<Args...>, TypeVector<>, Compare>::Type, T>::Type;
};

template <template <class, class> class Compare>
struct Merge<TypeVector<>, TypeVector<>, Compare> {
  using Type = TypeVector<>;
};

template <typename TV, template <class, class> class Compare>
struct Sort;

template <typename... Args, template <class, class> class Compare>
struct Sort<TypeVector<Args...>, Compare> {
  using Type = typename PushFront<
      typename Sort<
          typename EraseFirst<TypeVector<Args...>, typename MinElement<TypeVector<Args...>, Compare>::Type>::Type,
          Compare>::Type,
      typename MinElement<TypeVector<Args...>, Compare>::Type>::Type;
};

template <template <class, class> class Compare>
struct Sort<TypeVector<>, Compare> {
  using Type = TypeVector<>;
};

template <typename TV>
constexpr inline size_t kSizeV = Size<TV>::Value;

template <typename TV>
constexpr inline bool kEmptyV = Empty<TV>::value;

template <typename TV>
using FrontT = typename Front<TV>::Type;

template <typename TV>
using BackT = typename Back<TV>::Type;

template <typename TV, size_t Idx>
using AtT = typename At<TV, Idx>::Type;

template <typename TV, typename T>
constexpr inline bool kContainsV = Contains<TV, T>::value;

template <typename TV, typename T>
constexpr inline size_t kCountV = Count<TV, T>::value;

template <typename TV, typename T>
using PushFrontT = typename PushFront<TV, T>::Type;

template <typename TV, typename T>
using PushBackT = typename PushBack<TV, T>::Type;

template <typename TV>
using PopFrontT = typename PopFront<TV>::Type;

template <typename TV>
using PopBackT = typename PopBack<TV>::Type;

template <typename TV1, typename TV2>
using ConcatenateT = typename Concatenate<TV1, TV2>::Type;

template <typename TV, size_t Idx, typename T>
using InsertT = typename Insert<TV, Idx, T>::Type;

template <typename TV, typename T>
using EraseFirstT = typename EraseFirst<TV, T>::Type;

template <typename TV, typename T>
using EraseAllT = typename EraseAll<TV, T>::Type;

template <typename TV>
using ReverseT = typename Reverse<TV>::Type;

template <typename TV>
using UniqueT = typename Unique<TV>::Type;

template <typename TV, template <class> class F>
using TransformT = typename Transform<TV, F>::Type;

template <typename TV, template <class> class Predicate>
constexpr inline bool kAllOfV = AllOf<TV, Predicate>::value;

template <typename TV, template <class> class Predicate>
constexpr inline bool kAnyOfV = AnyOf<TV, Predicate>::value;

template <typename TV, template <class, class> class Compare>
using MinElementT = typename MinElement<TV, Compare>::Type;

template <typename TV, template <class, class> class Compare>
using MaxElementT = typename MaxElement<TV, Compare>::Type;

template <typename TV1, typename TV2, template <class, class> class Compare>
using MergeT = typename Merge<TV1, TV2, Compare>::Type;

template <typename TV, template <class, class> class Compare>
using SortT = typename Sort<TV, Compare>::Type;

#endif