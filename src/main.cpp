//
// Created by Daniel Omiya on 09/05/21.
//

#include "avltree.hpp"
#include "binarysearchtree.hpp"
#include "binarytree.hpp"
#include "reader.hpp"
#include "trendname.hpp"
#include "trendvolume.hpp"
#include "writer.hpp"
#include <chrono>
#include <ostream>

template <typename T, typename = std::enable_if<std::is_base_of<Trend, T>::value>>
inline void insertData(BinaryTree<T> *tree, const std::vector<T> &trends,
                       std::chrono::duration<double, std::milli> *elapsedTime) {
  auto t0 = std::chrono::high_resolution_clock::now();

  for (auto const &t : trends) {
    tree->insert(t, t.tweetVolume);
  }

  auto t1 = std::chrono::high_resolution_clock::now();
  *elapsedTime = t1 - t0;
}

template <typename T, typename = std::enable_if<std::is_base_of<Trend, T>::value>>
void inOrder(Node<T> *node, std::ostream &out) {
  if (node == nullptr)
    return;

  inOrder(node->left, out);
  out << '\t' << node->data.name << ": " << node->count << std::endl;
  inOrder(node->right, out);
}

template <typename T, typename = std::enable_if<std::is_base_of<Trend, T>::value>>
void inDisorder(Node<T> *node, std::ostream &out) {
  if (node == nullptr)
    return;

  inDisorder(node->right, out);
  out << '\t' << node->data.name << ": " << node->count << std::endl;
  inDisorder(node->left, out);
}

void nodeToVec(Node<TrendName> *node, std::vector<TrendVolume> *vec) {
  if (node == nullptr)
    return;

  vec->emplace_back(node->data);
  vec->back().tweetVolume = node->count;

  nodeToVec(node->left, vec);
  nodeToVec(node->right, vec);
}

inline void report(BinaryTree<TrendName> *nameTree, BinaryTree<TrendVolume> *volumeTree,
                   const std::string &type, const std::vector<Trend> &trends,
                   std::ostream &out) {
  std::vector<TrendName> names(trends.begin(), trends.end());
  std::vector<TrendVolume> volumes;
  std::chrono::duration<double, std::milli> nameMsElapsed{}, volumeMsElapsed{};
  int nameComparisonCount, volumeComparisonCount;

  volumes.reserve(trends.size());

  insertData(nameTree, names, &nameMsElapsed);
  nameComparisonCount = TrendName::getComparisonCounter();

  out << type << ':' << std::endl;
  out << '\t' << nameComparisonCount << " COMPARACOES" << std::endl;
  out << "\tTEMPO DE EXECUCAO: " << nameMsElapsed.count() << "ms" << std::endl
      << std::endl;

  out << "FREQUENCIA DAS PALAVRAS EM ORDEM ALFABETICA:" << std::endl;
  inOrder(nameTree->getRoot(), out);
  out << std::endl;

  nodeToVec(nameTree->getRoot(), &volumes);
  insertData(volumeTree, volumes, &volumeMsElapsed);
  volumeComparisonCount = TrendVolume::getComparisonCounter();

  out << "TRENDING TOPICS:" << std::endl;
  inDisorder(volumeTree->getRoot(), out);

  write("reports/" + type + "_by-name.dot", nameTree->toString());
  write("reports/" + type + "_by-volume.dot", volumeTree->toString());

  TrendName::resetComparisonCounter();
  TrendVolume::resetComparisonCounter();
}

int main(int argc, char *argv[]) {
  const auto path = argc > 1 ? argv[1] : "data/out.csv";

  /* reading trends from csv */
  const auto trends = getTrends(path);

  /* AVL trees */
  AVLTree<TrendName> nameAVL;
  AVLTree<TrendVolume> volumeAVL;

  /* binary search trees */
  BinarySearchTree<TrendName> nameBST;
  BinarySearchTree<TrendVolume> volumeBST;

  /* string output */
  std::stringstream avlOutput, bstOutput;

  /* run benchmark for AVL tree */
  report(&nameAVL, &volumeAVL, "ARVORE AVL", trends, avlOutput);
  write("reports/avl-report.txt", avlOutput.str());

  /* run benchmark for BST tree */
  report(&nameBST, &volumeBST, "ARVORE BINARIA DE BUSCA", trends, bstOutput);
  write("reports/bst-report.txt", bstOutput.str());

  return 0;
}
