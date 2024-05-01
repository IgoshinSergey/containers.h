#ifndef CPP2_S21_CONTAINERS_SET
#define CPP2_S21_CONTAINERS_SET

#include <initializer_list>

#include "red_black_tree.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key>
class set {
 private:
  using value_type = Key;
  using key_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using BinaryTree = RBTree<Key, Key>;
  using iterator = typename BinaryTree::iterator;
  using const_iterator = typename BinaryTree::const_iterator;
  using size_type = std::size_t;

  RBTree<key_type, value_type> tree;

 public:
  set() : tree{} {}
  set(std::initializer_list<value_type> const& items) : set{} {
    for (const_reference i : items) {
      if (tree.search(i) == nullptr) {
        tree.insert(i, i);
      }
    }
  }
  set(const set& s) : set() {
    tree.root = tree.copyTree(s.tree.root);
    tree.size = s.tree.size;
  }
  set(set&& s) : tree{std::move(s.tree)} {};
  ~set() {}

  set operator=(set&& s) {
    tree.moveTree(std::move(s.tree));
    return *this;
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
    if (tree.search(value) == nullptr) {
      res = true;
      tree.insert(value, value);
    }
    iterator iter = iterator(tree.search(value), tree);
    return std::pair<iterator, bool>(iter, res);
  }
  void erase(iterator pos) {
    if (pos.current != nullptr) {
      key_type key = pos.current->key;
      if (tree.search(key) != nullptr) {
        tree.remove(key);
      }
    }
  }
  void swap(set& other) {
    auto tmp = other.tree.root;
    other.tree.root = tree.root;
    tree.root = tmp;

    unsigned size_tmp = other.tree.size;
    other.tree.size = tree.size;
    tree.size = size_tmp;
  }
  void merge(set& other) {
    for (auto iter = other.begin(); iter != other.end(); ++iter) {
      insert(*iter);
    }
    other.clear();
  }

  iterator find(const Key& key) { return iterator(tree.search(key), tree); }
  bool contains(const Key& key) { return (tree.search(key)) ? true : false; }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> res;
    if (sizeof...(Args) > 0) {
      (res.push_back(insert(std::forward<Args>(args))), ...);
    }
    return res;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SET
