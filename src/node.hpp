//
// Created by Daniel Omiya on 09/05/21.
//

#ifndef NODE_HPP
#define NODE_HPP

#include <string>

template <class T> struct Node {
  const T &data;
  int count;
  int height;
  Node<T> *left, *right;
};

#endif // NODE_HPP
