#ifndef CPP2_S21_CONTAINERS_MAP
#define CPP2_S21_CONTAINERS_MAP

#include <initializer_list>

#include "red_black_tree.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key, typename T>
class map {
 private:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using BinaryTree = RBTree<key_type, value_type>;
  using iterator = typename BinaryTree::iterator;
  using const_iterator = typename BinaryTree::const_iterator;
  using size_type = std::size_t;

  RBTree<key_type, value_type> tree;

 public:
  map() : tree{} {}
  map(std::initializer_list<value_type> const& items) : map{} {
    for (const_reference i : items) {
      if (tree.search(i.first) == nullptr) {
        tree.insert(i.first, i);
      }
    }
  }
  map(const map& s) : map() {
    tree.root = tree.copyTree(s.tree.root);
    tree.size = s.tree.size;
  }
  map(map&& s) : tree{std::move(s.tree)} {}
  ~map() {}
  map operator=(map&& s) {
    if (tree.root != nullptr) tree.freeTree(tree.root);
    tree.moveTree(std::move(s.tree));
    return *this;
  }

  T& at(const Key& key) {
    auto node = tree.search(key);
    if (node == nullptr) {
      throw std::out_of_range("This key is not in the map.");
    }
    return (node->value).second;
  }
  T& operator[](const Key& key) {
    auto node = tree.search(key);
    if (node == nullptr) {
      insert(key, mapped_type());
    }
    return tree.search(key)->value.second;
  }

  iterator begin() { return iterator(tree.minimum(tree.root), tree); }
  iterator end() { return iterator(nullptr, tree); }

  bool empty() { return tree.size == 0; }
  size_type size() { return tree.size; }
  size_type max_size() { return size_t(-1) / (sizeof(BinaryTree)) / 5; }

  void clear() {
    tree.freeTree(tree.root);
    tree.root = nullptr;
    tree.size = 0;
  }
  std::pair<iterator, bool> insert(const value_type& value) {
    bool res = false;
    if (tree.search(value.first) == nullptr) {
      res = true;
      tree.insert(value.first, value);
    }
    iterator iter = iterator(tree.search(value.first), tree);
    return std::pair<iterator, bool>(iter, res);
  }
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    bool res = false;
    if (tree.search(key) == nullptr) {
      res = true;
      std::pair<key_type, mapped_type> value{key, obj};
      tree.insert(key, value);
    }
    iterator iter = iterator(tree.search(key), tree);
    return std::pair<iterator, bool>(iter, res);
  }
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    auto node = tree.search(key);
    bool res = false;
    if (node == nullptr) {
      res = true;
      insert(key, obj);
    } else {
      node->value.second = obj;
    }
    return std::pair<iterator, bool>(iterator(tree.search(key), tree), res);
  }

  void erase(iterator pos) {
    if (pos.current != nullptr) {
      auto node = pos.current;
      tree.removeByNode(node);
    }
  }
  void swap(map& other) {
    auto tmp = other.tree.root;
    other.tree.root = tree.root;
    tree.root = tmp;

    auto size_tmp = other.tree.size;
    other.tree.size = tree.size;
    tree.size = size_tmp;
  }
  void merge(map& other) {
    for (auto iter = other.begin(); iter != other.end(); ++iter) {
      insert(*iter);
    }
    other.clear();
  }

  bool contains(const Key& key) { return (tree.search(key)) ? true : false; }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> res;
    if (sizeof...(Args) > 0) {
      (res.push_back(
           std::pair<iterator, bool>(insert(std::forward<Args>(args)))),
       ...);
    }
    return res;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_MAP
