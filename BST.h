#ifndef _BST_H_
#define _BST_H_

#include "treeNode.h"
#include <iostream>
#include <string>
#include <stdexcept>

template <class T> class BST {
public:
  BST() { root_ = nullptr; }
  // Rule of three methods
  virtual ~BST() { recDelete(root_); }
  BST(const BST<T>& other) { copy(other); }
  BST<T>& operator = (const BST<T>& other) { copy(other); return *this; }
  // Public methods
  void insert(T);
  bool deleteNode(const T&);
  bool contains(const T&) const;
  T get(const T&) const;
  T& get(const T&);
  bool isEmpty() const { return (root_ == nullptr); }
  // Getters, setters and display methods
  void printTree(std::ostream& out = std::cout, std::string delim = "\n") const {
    recPrint(root_, out, delim); } // in-order traversal
  void sexyDisplay() const { recDisplay(root_, 0); }; // sooo sexy
  TreeNode<T>* root() const { return root_; }

  bool operator == (const BST<T>& other) const { return root_ == other.root_; }
  friend std::ostream& operator << (std::ostream& os, const BST<T>& tree) { return os; }
private:
  TreeNode<T>* root_;
  // deleteNode helpers
  TreeNode<T>* getSuccessor(TreeNode<T>*);
  TreeNode<T>* getRightLeafSuccessor(TreeNode<T>*);
  void insertSuccessor(TreeNode<T>*, TreeNode<T>*, TreeNode<T>*&);
  // Rule of three and recursive helpers
  void recPrint(TreeNode<T>*, std::ostream&, std::string) const;
  void recDisplay(TreeNode<T>*, int) const;
  void recDelete(TreeNode<T>*);
  void copy(const BST<T>&);
  TreeNode<T>* recCopy(TreeNode<T>*);
};

template <class T>
void BST<T>::insert(T value) {
  // check duplicates
  if (contains(value)) {
    throw std::runtime_error("Cannot insert existing value into tree");
  }

  TreeNode<T>* newNode = new TreeNode<T>(value);
  if (isEmpty()) {
    root_ = newNode;
    return;
  }

  TreeNode<T>* current = root_;
  TreeNode<T>* parent;
  while (true) {
    parent = current;
    if (value < current->key()) {
      current = current->left();
      if (current == nullptr) { parent->setLeft(newNode); break; }
    }
    else {
      current = current->right();
      if (current == nullptr) { parent->setRight(newNode); break;}
    }
  }
}

template <class T>
bool BST<T>::contains(const T& value) const {
  if ( isEmpty() ) { return false; }

  TreeNode<T>* current = root_;
  while (current->key() != value) {
    if (value < current->key()) {
      current = current->left(); }
    else {
      current = current->right(); }

    if (current == nullptr) { return false; }
  }
  return true;
}

template <class T>
T BST<T>::get(const T& k) const {
  if (!contains(k)) {
    throw std::runtime_error("Requesting nonexistent key");
  }

  TreeNode<T>* current = root_;
  while (current->key() != k) {
    if (k < current->key()) {
      current = current->left();
    }
    else {
      current = current->right();
    }
  }

  return current->key();
}

template <class T>
T& BST<T>::get(const T& k) {
  if (!contains(k)) {
    throw std::runtime_error("Requesting nonexistent key");
  }

  TreeNode<T>* current = root_;
  while (current->key() != k) {
    if (k < current->key()) {
      current = current->left();
    }
    else {
      current = current->right();
    }
  }

  return current->key();
}

////////////////////////////
// deleteNode and Helpers //
////////////////////////////

template <class T>
bool BST<T>::deleteNode(const T& k) {
  // Deletes the specified node from the tree, replacing it with the node's
  // smallest successor. Returns true if the node was found in the tree, and
  // false otherwise
  if (!contains(k)) { return false; }

  // Find the node to delete, and its parent
  TreeNode<T>* parent = nullptr;
  TreeNode<T>* nodeToDelete = root_;
  while (nodeToDelete->key() != k) {
    parent = nodeToDelete;
    if (k < nodeToDelete->key()) { nodeToDelete = nodeToDelete->left(); }
    else                         { nodeToDelete = nodeToDelete->right(); }
  }

  // Obtain the successor and replace the nodeToDelete with this in the tree
  TreeNode<T>* successor = getSuccessor(nodeToDelete);
  insertSuccessor(nodeToDelete, successor, parent);

  // Delete the nodeToDelete
  nodeToDelete->setLeft(nullptr);
  nodeToDelete->setRight(nullptr);
  delete nodeToDelete;
}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* nodeToDelete) {
  // Returns the successor to nodeToDelete.
  // The successor returned will be appropriately removed from its own parent
  // and will have its children correctly assigned in preparation for replacement
  if (nodeToDelete->left() == nullptr && nodeToDelete->right() == nullptr) {
    return nullptr;
  }
  else if (nodeToDelete->left() == nullptr) {
    return nodeToDelete->right();
  }
  else if (nodeToDelete->right() == nullptr) {
    return nodeToDelete->left();
  }
  else {
    return getRightLeafSuccessor(nodeToDelete);
  }
}

template <class T>
TreeNode<T>* BST<T>::getRightLeafSuccessor(TreeNode<T>* nodeToDelete) {
  // Returns the node with the smallest key greater than that of nodeToDelete.
  // Processes the successor's parent and children for the deletion

  TreeNode<T>* sucParent = nodeToDelete;
  TreeNode<T>* successor = nodeToDelete;
  TreeNode<T>* sucChild  = nodeToDelete->right();
  // Traverse down the left wing of the right fork until you hit null
  while (sucChild != nullptr) {
    sucParent = successor;
    successor = sucChild;
    sucChild = sucChild->left();
  }

  // Set the successor's parent and children
  if (successor != nodeToDelete->right()) {
    sucParent->setLeft(successor->right());
    successor->setRight(nodeToDelete->right());
  }
  successor->setLeft(nodeToDelete->left());

  return successor;
}

template <class T>
void BST<T>::insertSuccessor(TreeNode<T>* current, TreeNode<T>* successor, TreeNode<T>*& parent) {
  // Inserts the successor as the new child of the original node's parent,
  // if applicable
  if      (current == root_)               { root_ = successor; }
  else if (current->key() < parent->key()) { parent->setLeft(successor); }
  else                                     { parent->setRight(successor); }
}

/////////////////////////////////////////
// Rule of Three and Recursive Helpers //
/////////////////////////////////////////

template <class T>
void BST<T>::recPrint(TreeNode<T>* node, std::ostream& out, std::string delim) const {
  // Recursive print
  if (node == nullptr) { return; }

  recPrint(node->left(), out, delim);
  out << node->key() << delim;
  recPrint(node->right(), out, delim);
}

template <class T>
void BST<T>::recDisplay(TreeNode<T>* node, int depth) const {
  if (node == nullptr) {
    std::cout << "Empty tree" << std::endl;
    return;
  }

  if (node->right() != nullptr) {
    recDisplay(node->right(), depth+1);
  }

  for (int i=0; i<depth; ++i) { std::cout << "    "; }
  std::cout << node->key() << std::endl;

  if (node->left() != nullptr) {
    recDisplay(node->left(), depth+1);
  }

}

template <class T>
void BST<T>::recDelete(TreeNode<T>* node) {
  // Deletes the entire subtree of provided root node
  if (node == nullptr) { return; }

  TreeNode<T>* leftNode  = node->left();
  TreeNode<T>* rightNode = node->right();
  if (leftNode != nullptr) {
    recDelete(leftNode);
    node->setLeft(nullptr);
  }

  if (rightNode != nullptr) {
    recDelete(rightNode);
    node->setRight(nullptr);
  }

  delete node;
}

template <class T>
void BST<T>::copy(const BST<T>& other) {
  // Writes the tree structure as a deep copy of provided other BST
  if ( other.isEmpty() ) {
    root_ = nullptr;
  }
  else {
    root_ = recCopy(other.root_);
  }
}

template <class T>
TreeNode<T>* BST<T>::recCopy(TreeNode<T>* otherNode) {
  TreeNode<T>* newNode = new TreeNode<T>(otherNode->key());

  TreeNode<T>*  otherLeft = otherNode->left();
  TreeNode<T>* otherRight = otherNode->right();
  if (otherLeft  != nullptr) { newNode->setLeft(  recCopy(otherLeft)  ); }
  if (otherRight != nullptr) { newNode->setRight( recCopy(otherRight) ); }

  return newNode;
}

#endif
