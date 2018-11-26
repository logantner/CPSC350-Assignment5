#ifndef _DOUBLE_NODE_H_
#define _DOUBLE_NODE_H_

#include <iostream>
#include <stdexcept>

template <class T> class DoubleNode {
public:
  DoubleNode() : next_(nullptr), prev_(nullptr) { }
  DoubleNode(T data) : data_(data), next_(nullptr), prev_(nullptr) { }
  // Rule of 3 methods
  DoubleNode(const DoubleNode<T>& other) {
    std::cout << "Nodes should not be copied directly" << std::endl;
    // throw std::runtime_error("Nodes should not be copied directly");
  }
  DoubleNode<T> & operator = (const DoubleNode<T>& other) {
    std::cout << "Nodes should not be assigned directly" << std::endl;
    // throw std::runtime_error("Nodes should not be assigned directly");
    return *this; }
  ~DoubleNode();

  T data() const { return data_; }
  DoubleNode* next() const { return next_; }
  DoubleNode* prev() const { return prev_; }
  void setNext(DoubleNode* n) { next_ = n; }
  void setPrev(DoubleNode* p) { prev_ = p; }
private:
  T data_;
  DoubleNode* next_;
  DoubleNode* prev_;
  void copyMemory(const DoubleNode<T>&);
};

template <class T>
DoubleNode<T>::~DoubleNode() {
  if (next_ == nullptr && prev_ == nullptr) {
    return;
  }
  std::cout << "Only singleton nodes can be safely deleted" << std::endl;
  // throw std::runtime_error("Only singleton nodes can be safely deleted");
}

#endif
