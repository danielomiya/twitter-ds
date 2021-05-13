//
// Created by Daniel Omiya on 09/05/21.
//

#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "binarytree.hpp"
#include "utils.hpp"

template <class T> class AVLTree : public BinaryTree<T> {
private:
  Node<T> *insertNode(Node<T> *node, Node<T> *x) {
    if (node == nullptr)
      return x;

    if (x->data < node->data) {
      node->left = insertNode(node->left, x);
      if (this->height(node->right) - this->height(node->left) == -2) {
        node = (x->data < node->left->data) ? leftToLeft(node) : leftToRight(node);
      }
    } else if (x->data > node->data) {
      node->right = insertNode(node->right, x);
      if (this->height(node->right) - this->height(node->left) == 2) {
        node = (x->data > node->right->data) ? rightToRight(node) : rightToLeft(node);
      }
    } else {
      node->count += x->count;
      delete x;
    }
    node->height = max(this->height(node->left), this->height(node->right)) + 1;

    return node;
  }

  Node<T> *leftToLeft(Node<T> *node) {
    auto leftSub = node->left;
    node->left = leftSub->right;
    leftSub->right = node;
    node->height = max(this->height(node->left), this->height(node->right)) + 1;
    leftSub->height = max(this->height(leftSub->left), this->height(node) + 1);
    return leftSub;
  }

  Node<T> *leftToRight(Node<T> *node) {
    node->left = rightToRight(node->left);
    return leftToLeft(node);
  }

  Node<T> *rightToLeft(Node<T> *node) {
    node->right = leftToLeft(node->right);
    return rightToRight(node);
  }

  Node<T> *rightToRight(Node<T> *node) {
    auto rightSub = node->right;
    node->right = rightSub->left;
    rightSub->left = node;
    node->height = max(this->height(node->left), this->height(node->right)) + 1;
    rightSub->height = max(this->height(rightSub->right), this->height(node) + 1);
    return rightSub;
  }

public:
  AVLTree() : BinaryTree<T>() {}
  void insert(const T &x) override { insert(x, 1); }
  void insert(const T &x, int count) override {
    auto node = new Node<T>{x, count, 0, nullptr, nullptr};
    this->setRoot(insertNode(this->getRoot(), node));
  }
};

#endif // AVL_TREE_HPP
