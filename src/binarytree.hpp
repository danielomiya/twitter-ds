//
// Created by Daniel Omiya on 09/05/21.
//

#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "node.hpp"
#include <sstream>

template <class T> class BinaryTree {
private:
  Node<T> *root;
  std::stringstream &nodeToString(std::stringstream &ss, Node<T> *node, int *id,
                                  int parent = -1) const {
    int self = *id;

    // self identify node
    if (node == nullptr)
      ss << "node" << self << "[style=invis,shape=plaintext,label=\"<NULL>\"];";
    else
      ss << "node" << self << "[shape=plaintext,label=\"" << node->data << "\\n("
         << node->count << ")\"];";

    if (parent >= 0) {
      ss << "node" << parent << " -- node" << *id
         << (node == nullptr ? "[style=invis]" : "") << ';';
    }

    if (node != nullptr) {
      ++*id;
      nodeToString(ss, node->left, id, self);

      ++*id;
      nodeToString(ss, node->right, id, self);
    }

    return ss;
  }

  void destroyNode(Node<T> *node) {
    if (node == nullptr)
      return;
    destroyNode(node->left);
    destroyNode(node->right);
    delete node;
  }

protected:
  void setRoot(Node<T> *node) { root = node; };
  int count(const Node<T> *node) const {
    if (node == nullptr)
      return 0;
    return 1 + count(node->left) + count(node->right);
  }

public:
  BinaryTree() { root = nullptr; }
  ~BinaryTree() { destroyNode(root); }
  bool isEmpty() const { return root == nullptr; }
  int count() const { return count(root); }
  Node<T> *getRoot() const { return root; }
  int height() const { return height(root); }
  int height(const Node<T> *node) const { return node == nullptr ? -1 : node->height; }
  virtual void insert(const T &x) = 0;
  virtual void insert(const T &x, int count) = 0;
  std::string toString() const {
    int id = 0;
    std::stringstream ss;
    ss << "graph G{";
    ss << "nodesep=0.4;";
    ss << "ranksep=0.5;";
    ss << "margin=0.1;";
    ss << "graph [ordering=\"out\"];";
    ss << "edge[arrowsize=0.8];";

    if (getRoot() != nullptr)
      nodeToString(ss, root, &id);

    ss << "}\n";

    return ss.str();
  }
};

#endif // BINARY_TREE_HPP
