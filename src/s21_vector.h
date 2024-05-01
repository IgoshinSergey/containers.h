#ifndef CPP2_S21_CONTAINERS_VECTOR
#define CPP2_S21_CONTAINERS_VECTOR

#include <initializer_list>

namespace s21 {

template <typename T>
class vector {
 private:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

  value_type* values;
  size_type size_vector;
  size_type capacity_vector;

 public:
  vector() : size_vector{}, capacity_vector{} { values = nullptr; }

  vector(size_type n) : size_vector{n}, capacity_vector{n} {
    values = static_cast<T*>(::operator new(sizeof(T) * capacity_vector));
    for (unsigned i{}; i < capacity_vector; i++) {
      new (&values[i]) T();
    }
  }

  vector(std::initializer_list<value_type> const& items) {
    size_vector = capacity_vector = items.size();
    values = static_cast<T*>(::operator new(sizeof(T) * capacity_vector));
    std::copy(items.begin(), items.end(), values);
  }

  vector(const vector& v)
      : size_vector{v.size_vector}, capacity_vector{v.capacity_vector} {
    values = static_cast<T*>(::operator new(sizeof(T) * capacity_vector));
    for (unsigned i{}; i < capacity_vector; i++) {
      new (&values[i]) T(v.values[i]);
    }
  }

  vector(vector&& v) : vector() {
    std::swap(size_vector, v.size_vector);
    std::swap(capacity_vector, v.capacity_vector);
    std::swap(values, v.values);
  }

  ~vector() {
    size_vector = capacity_vector = 0;
    if (values) ::operator delete(values);
    values = nullptr;
  }

  vector operator=(vector&& v) {
    if (this != &v) {
      if (values) ::operator delete(values);
      capacity_vector = size_vector = 0;
      std::swap(capacity_vector, v.capacity_vector);
      std::swap(size_vector, v.size_vector);
      std::swap(values, v.values);
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_vector)
      throw std::out_of_range("Индекс за пределами вектора");
    return values[pos];
  }

  reference operator[](size_type pos) { return values[pos]; }

  const_reference front() { return values[0]; }

  const_reference back() { return values[size_vector - 1]; }

  T* data() { return values; }

  iterator begin() { return &values[0]; }

  iterator end() { return &values[size_vector]; }

  bool empty() { return size_vector == 0; }

  size_type size() { return size_vector; }

  size_type max_size() { return size_t(-1) / sizeof(value_type) / 2; }

  void reserve(size_type size) {
    if (size >= capacity_vector) {
      capacity_vector = size;
      T* tmp = static_cast<T*>(::operator new(sizeof(T) * capacity_vector));
      std::copy_n(values, size_vector, tmp);
      if (values) ::operator delete(values);
      values = tmp;
    }
  }

  size_type capacity() { return capacity_vector; }

  void shrink_to_fit() {
    if (capacity_vector > size_vector) {
      capacity_vector = size_vector;
      T* tmp = static_cast<T*>(::operator new(sizeof(T) * capacity_vector));
      std::copy_n(values, capacity_vector, tmp);
      ::operator delete(values);
      values = tmp;
    }
  }

  void clear() { size_vector = 0; }

  iterator insert(iterator pos, const_reference value) {
    iterator res = nullptr;
    if (size_vector == capacity_vector) {
      if (size_vector == 0) {
        capacity_vector += 1;
      } else {
        capacity_vector *= 2;
      }
    }
    size_vector++;
    value_type* tmp =
        static_cast<T*>(::operator new(sizeof(T) * capacity_vector));
    if (capacity_vector == 1) {
      new (&tmp[0]) T(value);
    } else {
      for (unsigned i{}, tmp_i{}; i < size_vector - 1; i++) {
        if (&values[i] == pos) {
          new (&tmp[tmp_i]) T(value);
          res = &tmp[tmp_i];
          tmp_i++;
        }
        new (&tmp[tmp_i]) T(values[i]);
        tmp_i++;
      }
    }
    if (values) ::operator delete(values);
    values = tmp;
    return res;
  }

  void erase(iterator pos) {
    value_type* tmp =
        static_cast<T*>(::operator new(sizeof(T) * capacity_vector));
    for (unsigned i{}, tmp_i{}; i < size_vector; i++) {
      if (&values[i] != pos) {
        new (&tmp[tmp_i]) T(values[i]);
        tmp_i++;
      }
    }
    size_vector--;
    ::operator delete(values);
    values = tmp;
  }

  void push_back(const_reference value) {
    if (size_vector == capacity_vector) {
      if (size_vector == 0) {
        capacity_vector += 1;
      } else {
        capacity_vector *= 2;
      }
    }
    size_vector++;
    value_type* tmp =
        static_cast<T*>(::operator new(sizeof(T) * capacity_vector));
    if (capacity_vector == 1) {
      new (&tmp[0]) T(value);
    } else {
      for (unsigned i{}; i < size_vector - 1; i++) {
        new (&tmp[i]) T(values[i]);
      }
      new (&tmp[size_vector - 1]) T(value);
    }
    if (values) ::operator delete(values);
    values = tmp;
  }

  void pop_back() { size_vector--; }

  void swap(vector& other) {
    std::swap(values, other.values);
    std::swap(size_vector, other.size_vector);
    std::swap(capacity_vector, other.capacity_vector);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    iterator res = nullptr;
    if (sizeof...(Args) > 0) {
      iterator iter = begin();
      unsigned delta = pos - iter;
      iter += delta;
      if (iter == pos) {
        ((iter = (insert(iter, std::forward<Args>(args)) + 1)), ...);
      }
      res = begin() + delta;
    }
    return res;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    if (sizeof...(Args) > 0) {
      ((push_back(std::forward<Args>(args))), ...);
    }
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_VECTOR
