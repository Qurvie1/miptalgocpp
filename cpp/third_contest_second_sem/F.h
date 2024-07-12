#ifndef ZIP_H
#define ZIP_H

#define TEMPORARY_ZIP_IMPLEMENTED

#include <tuple>

template <class... Args>
class Wrapper {
 public:
  class Iterator {
   public:
    Iterator(std::tuple<  // NOLINT
             std::conditional_t<std::is_const_v<std::remove_reference_t<Args>> || !std::is_lvalue_reference_v<Args>,
                                typename std::remove_reference_t<Args>::const_iterator,
                                typename std::remove_reference_t<Args>::iterator>...>
                 tuple)
        : iterators_(tuple) {
    }

    auto operator*() {
      return std::apply([](auto&&... iter) -> auto { return std::forward_as_tuple(*iter...); }, iterators_);
    }

    Iterator& operator++() {
      std::apply([](auto&... iter) { (++iter, ...); }, iterators_);
      return *this;
    }

    bool operator!=(const Iterator& other) const noexcept {
      if (std::tuple_size<decltype(iterators_)>::value == 0) {
        return false;
      }
      bool fl1 = std::tuple_size<decltype(iterators_)>::value > 0 &&
                 (std::get<0>(iterators_) != std::get<0>(other.iterators_));
      bool fl2 = std::tuple_size<decltype(iterators_)>::value > 1 &&
                 (std::get<1>(iterators_) != std::get<1>(other.iterators_));
      return fl1 && fl2;
    }

   private:
    std::tuple<std::conditional_t<std::is_const_v<std::remove_reference_t<Args>> || !std::is_lvalue_reference_v<Args>,
                                  typename std::remove_reference_t<Args>::const_iterator,
                                  typename std::remove_reference_t<Args>::iterator>...>
        iterators_;
  };

  using iterator = Iterator;        // NOLINT
  using const_iterator = Iterator;  // NOLINT

  Iterator begin() {  // NOLINT
    return Iterator(std::apply([](auto&... iter) -> auto { return std::make_tuple(iter.begin()...); }, containers_));
  }

  Iterator end() {  // NOLINT
    return Iterator(std::apply([](auto&... iter) -> auto { return std::make_tuple(iter.end()...); }, containers_));
  }

  Iterator begin() const {  // NOLINT
    return Iterator(std::apply([](auto&... iter) -> auto { return std::make_tuple(iter.begin()...); }, containers_));
  }

  Iterator end() const {  // NOLINT
    return Iterator(std::apply([](auto&... iter) -> auto { return std::make_tuple(iter.end()...); }, containers_));
  }

  Wrapper(Args&&... args) : containers_{args...} {  // NOLINT
  }

 private:
  std::tuple<Args...> containers_;
};

template <typename... Args>
auto Zip(Args&&... args) {
  return Wrapper<std::conditional_t<std::is_lvalue_reference_v<Args>, Args, std::remove_reference_t<Args>>...>(
      std::forward<Args>(args)...);
}

#endif