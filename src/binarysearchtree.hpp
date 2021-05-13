//
// Created by Daniel Omiya on 09/05/21.
//

#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "binarytree.hpp"

template <class T> class BinarySearchTree : public BinaryTree<T> {
private:
  void insertNode(Node<T> *node, Node<T> *x) {
    if (x->data < node->data) {
      if (node->left == nullptr) {
        node->left = x;
      } else {
        insertNode(node->left, x);
      }
      return;
    }

    if (x->data > node->data) {
      if (node->right == nullptr) {
        node->right = x;
      } else {
        insertNode(node->right, x);
      }
      return;
    }

    node->count += x->count;
    delete x;
  }

public:
  BinarySearchTree() : BinaryTree<T>() {}
  void insert(const T &x) override { insert(x, 1); };
  void insert(const T &x, int count) override {
    auto node = new Node<T>{x, count, 0, nullptr, nullptr};

    if (this->isEmpty())
      this->setRoot(node);
    else
      insertNode(this->getRoot(), node);
  };
};

#endif // BINARY_SEARCH_TREE_HPP
