#ifndef CPP2_S21_CONTAINERS_MULTISET
#define CPP2_S21_CONTAINERS_MULTISET

#include <initializer_list>

#include "red_black_tree.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key>
class multiset {
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
  multiset() : tree{} {}
  multiset(std::initializer_list<value_type> const& items) : multiset{} {
    for (const_reference i : items) {
      tree.insert(i, i);
    }
  }
  multiset(const multiset& s) : multiset() {
    tree.root = tree.copyTree(s.tree.root);
    tree.size = s.tree.size;
  }
  multiset(multiset&& s) : tree{std::move(s.tree)} {};
  ~multiset() {}

  multiset operator=(multiset&& s) {
    if (tree.root != nullptr) tree.freeTree(tree.root);
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
  iterator insert(const value_type& value) {
    auto node = tree.insert(value, value);
    iterator iter = iterator(node, tree);
    return iter;
  }
  void erase(iterator pos) {
    if (pos.current != nullptr) {
      auto node = pos.current;
      tree.removeByNode(node);
    }
  }
  void swap(multiset& other) {
    auto tmp = other.tree.root;
    other.tree.root = tree.root;
    tree.root = tmp;

    unsigned size_tmp = other.tree.size;
    other.tree.size = tree.size;
    tree.size = size_tmp;
  }
  void merge(multiset& other) {
    for (auto iter = other.begin(); iter != other.end(); ++iter) {
      insert(*iter);
    }
    other.clear();
  }

  size_type count(const Key& key) {
    return tree.count_elements_equal_to_key(tree.root, key);
  }
  iterator find(const Key& key) { return lower_bound(key); }
  bool contains(const Key& key) { return (tree.search(key)) ? true : false; }
  std::pair<iterator, iterator> equal_range(const Key& key) {
    std::pair<iterator, iterator> res = {lower_bound(key), upper_bound(key)};
    return res;
  }
  iterator lower_bound(const Key& key) {
    auto iter = begin();
    for (; iter != end(); ++iter) {
      if (*iter >= key) break;
    }
    return iter;
  }
  iterator upper_bound(const Key& key) {
    auto iter = lower_bound(key);
    for (; iter != end(); ++iter) {
      if (*iter > key) break;
    }
    return iter;
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> res;
    if (sizeof...(Args) > 0) {
      (res.push_back(
           std::pair<iterator, bool>(insert(std::forward<Args>(args)), true)),
       ...);
    }
    return res;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_MULTISET
