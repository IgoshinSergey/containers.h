#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;
  array() = default;
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array() = default;

  array &operator=(array &&a);
  array &operator=(const array &a);

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  iterator data();
  const_iterator data() const;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  bool empty();
  size_type size();
  size_type max_size();

  void swap(array &other);
  void fill(const_reference value);

 private:
  value_type arr_[N]{};
};

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  if (items.size() > N)
    throw std::invalid_argument(
        "Initializer list size larger than size of the array");
  std::copy(items.begin(), items.end(), arr_);
}

template <typename T, std::size_t N>
array<T, N>::array(const array &a) {
  std::copy(a.begin(), a.end(), arr_);
}

template <typename T, std::size_t N>
array<T, N>::array(array &&a) {
  std::move(a.begin(), a.end(), arr_);
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  if (this != &a) {
    std::swap(arr_, a.arr_);
  }
  return *this;
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(const array &a) {
  if (this != &a) std::copy(a.arr_, a.arr_ + N, arr_);
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return *(arr_ + pos);
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return *(arr_ + pos);
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  return arr_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::front() {
  return *(arr_);
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return *(arr_);
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::back() {
  return *(arr_ + N - 1);
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return *(arr_ + N - 1);
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return arr_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::data() const {
  return arr_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return arr_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return arr_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return arr_ + N;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return arr_ + N;
}

template <typename T, std::size_t N>
bool array<T, N>::empty() {
  return N == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return N;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return N;
}

template <typename T, std::size_t N>
void array<T, N>::swap(array &other) {
  std::swap(arr_, other.arr_);
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(arr_, arr_ + N, value);
}
}  // namespace s21

#endif