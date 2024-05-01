#ifndef CPP2_S21_CONTAINERS_BINARY_TREE
#define CPP2_S21_CONTAINERS_BINARY_TREE

namespace s21 {

enum node_colors { RED, BLACK };
using color_node = enum node_colors;

template <typename K, typename V>
class Node {
 public:
  K key;
  V value;
  Node *left;
  Node *right;
  Node *parent;
  color_node color;
  bool isLeftChild;
  Node()
      : key{},
        value{},
        left{nullptr},
        right{nullptr},
        parent{nullptr},
        color{RED},
        isLeftChild{} {};
  Node(K key, V value)
      : key{key},
        value{value},
        left{nullptr},
        right{nullptr},
        parent{nullptr},
        color{RED},
        isLeftChild{} {};
  Node(Node *node, K &key, V &value)
      : key{key},
        value{value},
        left{node->left},
        right{node->right},
        parent{node->parent},
        color{node->color},
        isLeftChild{node->isLeftChild} {
    if (this->left) this->left->parent = this;
    if (this->right) this->right->parent = this;
    if (this->parent) {
      if (isLeftChild) {
        this->parent->left = this;
      } else {
        this->parent->right = this;
      }
    }
  };
  Node(Node *node, Node *parent)
      : key{node->key},
        value{node->value},
        left{nullptr},
        right{nullptr},
        parent{parent},
        color{node->color},
        isLeftChild{node->isLeftChild} {};
};

template <typename K, typename V>
class RBTreeConstIterator;

template <typename K, typename V>
class RBTreeIterator;

template <typename K, typename V>
class RBTree {
 private:
  void leftRotate(Node<K, V> *node) {
    Node<K, V> *temp = node->right;
    node->right = temp->left;
    if (node->right) node->right->isLeftChild = false;

    if (temp->left != nullptr) {
      temp->left->parent = node;
    }

    temp->parent = node->parent;
    if (node->parent == nullptr) {
      this->root = temp;
    } else if (node->isLeftChild == true) {
      node->parent->left = temp;
      temp->isLeftChild = true;
    } else {
      node->parent->right = temp;
      temp->isLeftChild = false;
    }

    temp->left = node;
    node->isLeftChild = true;
    node->parent = temp;
  }

  void rightRotate(Node<K, V> *node) {
    Node<K, V> *temp = node->left;
    node->left = temp->right;
    if (node->left) node->left->isLeftChild = true;

    if (temp->right != nullptr) {
      temp->right->parent = node;
    }

    temp->parent = node->parent;
    if (node->parent == nullptr) {
      this->root = temp;
    } else if (node->isLeftChild == false) {
      node->parent->right = temp;
      temp->isLeftChild = false;
    } else {
      node->parent->left = temp;
      temp->isLeftChild = true;
    }

    temp->right = node;
    node->isLeftChild = false;
    node->parent = temp;
  }

  void insertFixup(Node<K, V> *node) {
    Node<K, V> *temp;
    while ((root != node) && node->parent->color == RED) {
      if (node->parent->isLeftChild == false) {
        temp = node->parent->parent->left;
        if (temp && temp->color == RED) {
          temp->color = node->parent->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else {
          if (node->isLeftChild == true) {
            node = node->parent;
            rightRotate(node);
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          leftRotate(node->parent->parent);
        }
      } else {
        temp = node->parent->parent->right;
        if (temp && temp->color == RED) {
          temp->color = node->parent->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else {
          if (node->isLeftChild == false) {
            node = node->parent;
            leftRotate(node);
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          rightRotate(node->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

  void transplant(Node<K, V> *n, Node<K, V> *child) {
    if (n->parent == nullptr) {
      root = child;
    } else if (n->isLeftChild == true) {
      n->parent->left = child;
      if (child) child->isLeftChild = true;
    } else {
      n->parent->right = child;
      if (child) child->isLeftChild = false;
    }
    if (child) child->parent = n->parent;
  }

  void delete_one_child(Node<K, V> *node) {
    Node<K, V> *child = node->left ? node->left : node->right;
    transplant(node, child);
    if (node->color == BLACK) {
      if (child && child->color == RED) {
        child->color = BLACK;
      } else {
        delete_case_1(node);
      }
    }
    delete node;
  }

  void delete_case_1(Node<K, V> *node) {
    if (node->parent != nullptr) delete_case_2(node);
  }

  void delete_case_2(Node<K, V> *node) {
    Node<K, V> *brother = sibling(node);
    if (brother && brother->color == RED) {
      node->parent->color = RED;
      brother->color = BLACK;
      if (node->isLeftChild == true) {
        leftRotate(node->parent);
      } else {
        rightRotate(node->parent);
      }
    }
    delete_case_3(node);
  }

  void delete_case_3(Node<K, V> *node) {
    Node<K, V> *brother = sibling(node);
    if ((node->parent->color == BLACK) && (brother->color == BLACK) &&
        (brother->left == nullptr || brother->left->color == BLACK) &&
        (brother->right == nullptr || brother->right->color == BLACK)) {
      brother->color = RED;
      delete_case_1(node->parent);
    } else {
      delete_case_4(node);
    }
  }

  void delete_case_4(Node<K, V> *node) {
    Node<K, V> *brother = sibling(node);
    if ((node->parent->color == RED) && (brother->color == BLACK) &&
        (brother->left == nullptr || brother->left->color == BLACK) &&
        (brother->right == nullptr || brother->right->color == BLACK)) {
      brother->color = RED;
      node->parent->color = BLACK;
    } else {
      delete_case_5(node);
    }
  }

  void delete_case_5(Node<K, V> *node) {
    Node<K, V> *brother = sibling(node);
    if (brother->color == BLACK) {
      if ((node->isLeftChild == true) &&
          (brother->left && brother->left->color == RED) &&
          (brother->right == nullptr || brother->right->color == BLACK)) {
        brother->color = RED;
        brother->left->color = BLACK;
        rightRotate(brother);
      } else if ((node->isLeftChild == false) &&
                 (brother->right && brother->right->color == RED) &&
                 (brother->left == nullptr || brother->left->color == BLACK)) {
        brother->color = RED;
        brother->right->color = BLACK;
        leftRotate(brother);
      }
    }
    delete_case_6(node);
  }

  void delete_case_6(Node<K, V> *node) {
    Node<K, V> *brother = sibling(node);
    brother->color = node->parent->color;
    node->parent->color = BLACK;
    if (node->isLeftChild == true) {
      brother->right->color = BLACK;
      leftRotate(node->parent);
    } else {
      brother->left->color = BLACK;
      rightRotate(node->parent);
    }
  }

 public:
  Node<K, V> *root;
  unsigned size;

  using iterator = RBTreeIterator<K, V>;
  using const_iterator = RBTreeConstIterator<K, V>;

  RBTree() : root{nullptr}, size{} {}

  RBTree(const RBTree &other_tree) {
    root = copyTree(other_tree.root);
    size = other_tree.size;
  }

  RBTree(RBTree &&other_tree) { moveTree(std::move(other_tree)); }

  ~RBTree() { freeTree(this->root); }

  void moveTree(RBTree<K, V> &&other_tree) {
    root = other_tree.root;
    size = other_tree.size;

    other_tree.root = nullptr;
    other_tree.size = 0;
  }

  void freeTree(Node<K, V> *node) {
    if (node) {
      if (node->left) freeTree(node->left);
      if (node->right) freeTree(node->right);
      delete node;
      node = nullptr;
    }
  }

  Node<K, V> *copyTree(Node<K, V> *node) {
    if (node == nullptr) {
      return nullptr;
    }
    Node<K, V> *newNode = new Node<K, V>(node, node->parent);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
  }

  Node<K, V> *getRoot(void) { return this->root; }

  unsigned getSize(void) { return this->size; }

  void printTree(Node<K, V> *node) {
    if (node && node->left) printTree(node->left);
    if (node) {
      std::cout << ((node->color == BLACK) ? "Black " : "Red ");
      std::cout << node->value;
      std::cout << "; (parent) = "
                << ((node->parent) ? std::to_string(node->parent->value)
                                   : "nil")
                << " " << std::to_string(node->isLeftChild);
      std::cout << " | ";
    }
    if (node && node->right) printTree(node->right);
    std::cout << std::endl;
  }

  Node<K, V> *insert(const K &key, const V &value) {
    Node<K, V> *newNode = new Node<K, V>{key, value};
    Node<K, V> *parent = nullptr;
    Node<K, V> *x = root;
    this->size++;
    while (x != nullptr) {
      parent = x;
      if (newNode->key < x->key) {
        x = x->left;
      } else {
        x = x->right;
      }
    }
    newNode->parent = parent;
    if (parent == nullptr) {
      this->root = newNode;
    } else if (newNode->key < parent->key) {
      parent->left = newNode;
      newNode->isLeftChild = true;
    } else {
      parent->right = newNode;
      newNode->isLeftChild = false;
    }
    if (newNode->parent == nullptr) {
      newNode->color = BLACK;
    } else if (newNode->parent->parent != nullptr) {
      insertFixup(newNode);
    }
    return newNode;
  }

  Node<K, V> *sibling(Node<K, V> *node) {
    Node<K, V> *res = nullptr;
    if (node->isLeftChild) {
      res = node->parent->right;
    } else {
      res = node->parent->left;
    }
    return res;
  }

  void remove(const K &key) {
    Node<K, V> *node = search(key);
    if (node) {
      Node<K, V> *delNode = nullptr;
      if (node->left && node->right) {
        delNode = maximum(node->left);
        Node<K, V> *tmp = new Node<K, V>{delNode, node->key, node->value};
        new Node<K, V>{node, delNode->key, delNode->value};
        delete delNode;
        delete node;
        delNode = tmp;
      } else {
        delNode = node;
      }
      delete_one_child(delNode);
      size--;
    }
  }

  void removeByNode(Node<K, V> *node) {
    if (node) {
      Node<K, V> *delNode = nullptr;
      if (node->left && node->right) {
        delNode = maximum(node->left);
        Node<K, V> *tmp = new Node<K, V>{delNode, node->key, node->value};
        new Node<K, V>{node, delNode->key, delNode->value};
        delete delNode;
        delete node;
        delNode = tmp;
      } else {
        delNode = node;
      }
      delete_one_child(delNode);
      size--;
    }
  }

  Node<K, V> *minimum(Node<K, V> *subTree) {
    if (subTree) {
      while (subTree->left != nullptr) {
        subTree = subTree->left;
      }
    }
    return subTree;
  }

  Node<K, V> *maximum(Node<K, V> *subTree) {
    if (subTree) {
      while (subTree->right != nullptr) {
        subTree = subTree->right;
      }
    }
    return subTree;
  }

  Node<K, V> *search(const K &key) {
    Node<K, V> *res = root;
    while (res != nullptr && res->key != key) {
      if (key < res->key) {
        res = res->left;
      } else if (key > res->key) {
        res = res->right;
      }
    }
    return res;
  }

  int count_elements_equal_to_key(Node<K, V> *root, int key) {
    if (root == nullptr) return 0;
    int count = 0;
    if (root->key == key) count++;

    count += count_elements_equal_to_key(root->left, key);
    count += count_elements_equal_to_key(root->right, key);

    return count;
  }
};

template <typename K, typename V>
class RBTreeConstIterator {
 public:
  using value_type = V;
  using const_reference = const value_type &;

  RBTree<K, V> &tree;
  Node<K, V> *current;
  RBTreeConstIterator(Node<K, V> *node, RBTree<K, V> &tree)
      : current{node}, tree{tree} {};

  const_reference operator*() const {
    if (current != nullptr) {
      return current->value;
    } else {
      static V res{};
      return res;
    }
  }

  const RBTreeConstIterator &operator++() const {
    if (current != nullptr) {
      if (current->right == nullptr) {
        Node<K, V> *tmp = nullptr;
        while ((tmp = current->parent) != nullptr && (current == tmp->right)) {
          current = tmp;
        }
        current = tmp;
      } else {
        current = tree.minimum(current->right);
      }
    }
    return *this;
  }

  const RBTreeConstIterator &operator--() const {
    if (current != nullptr) {
      if (current->left == nullptr) {
        Node<K, V> *tmp = nullptr;
        while ((tmp = current->parent) != nullptr && (current == tmp->left)) {
          current = tmp;
        }
        current = tmp;
      } else {
        current = tree.maximum(current->left);
      }
    }
    return *this;
  }

  bool operator==(const RBTreeConstIterator &iter) {
    return current == iter.current;
  }

  bool operator!=(const RBTreeConstIterator &iter) {
    return current != iter.current;
  }
};

template <typename K, typename V>
class RBTreeIterator {
 public:
  using value_type = V;
  using reference = value_type &;

  RBTree<K, V> &tree;
  Node<K, V> *current;
  RBTreeIterator(Node<K, V> *node, RBTree<K, V> tree)
      : tree{tree}, current{node} {};
  RBTreeIterator(const RBTreeIterator &other)
      : tree{other.tree}, current{other.current} {};

  reference operator*() {
    if (current != nullptr) {
      return current->value;
    } else {
      static V res{};
      return res;
    }
  }

  RBTreeIterator &operator++() {
    if (current != nullptr) {
      if (current->right == nullptr) {
        Node<K, V> *tmp = nullptr;
        while ((tmp = current->parent) != nullptr && (current == tmp->right)) {
          current = tmp;
        }
        current = tmp;
      } else {
        current = tree.minimum(current->right);
      }
    }
    return *this;
  }

  RBTreeIterator &operator--() {
    if (current != nullptr) {
      if (current->left == nullptr) {
        Node<K, V> *tmp = nullptr;
        while ((tmp = current->parent) != nullptr && (current == tmp->left)) {
          current = tmp;
        }
        current = tmp;
      } else {
        current = tree.maximum(current->left);
      }
    }
    return *this;
  }

  bool operator==(const RBTreeIterator &iter) {
    return current == iter.current;
  }

  bool operator!=(const RBTreeIterator &iter) {
    return current != iter.current;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_BINARY_TREE
