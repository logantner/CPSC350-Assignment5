#ifndef _ASS5_DOUBLE_LINKED_LIST_H_
#define _ASS5_DOUBLE_LINKED_LIST_H_

#include <iostream>
#include <stdexcept>
#include "Collection.h"
#include "DoubleNode.h"

template <class T>
class DoubleLinkedList : public Collection<T> {
public:
  DoubleLinkedList() : size(0), front(nullptr), back(nullptr) { }
  // Rule of three methods
  DoubleLinkedList(const DoubleLinkedList<T>& other) { copy(other); }
  DoubleLinkedList& operator = (const DoubleLinkedList<T>& other) {
    copy(other); return *this; }
  ~DoubleLinkedList();
  // Insertions and removals
  void insertFront(T);
  void insertBack(T);
  T removeFront();
  T removeBack();
  T deletePos(unsigned int);
  // Getters
  int find(const T&) const;
  T get(unsigned int) const;
  unsigned int getSize() const { return size; }
  // Aesthetics
  void printList() const;
private:
  DoubleNode<T>* front;
  DoubleNode<T>* back;
  unsigned int size;
  void copy(const DoubleLinkedList<T>&);
};

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList() {
  while (size > 0) {
    removeFront();
  }
}

template <class T>
void DoubleLinkedList<T>::copy(const DoubleLinkedList<T>& other) {
  size = other.size;
  if (size == 0) {
    front = nullptr;
    back  = nullptr;
    return;
  }

  DoubleNode<T>* current = other.front;
  front = new DoubleNode<T>( current->data() );
  back = front;
  for (int i=1; i<size; ++i) {
    current = current->next();
    insertBack( current->data() );
  }
}

template <class T>
void DoubleLinkedList<T>::insertFront(T val) {
  DoubleNode<T>* newFront = new DoubleNode<T>(val);

  if (size == 0) {
    back = newFront;
  }
  else {
    newFront->setNext(front);
    front->setPrev(newFront);
  }

  front = newFront;
  size++;
}

template <class T>
void DoubleLinkedList<T>::insertBack(T val) {
  DoubleNode<T>* newBack = new DoubleNode<T>(val);

  if (size == 0) {
    front = newBack;
  }
  else {
    back->setNext(newBack);
    newBack->setPrev(back);
  }

  back = newBack;
  size++;
}

template <class T>
T DoubleLinkedList<T>::removeFront() {
  if (size == 0) {
    throw std::runtime_error("Cannot remove from empty list");
  }

  DoubleNode<T>* temp = front;
  front = temp->next();

  if (size == 1) {
    back = nullptr;
  }
  else {
    front->setPrev(nullptr);
  }

  T d = temp->data();

  temp->setNext(nullptr);
  delete temp;
  size--;
  return d;
}

template <class T>
T DoubleLinkedList<T>::removeBack() {
  if (size == 0) {
    throw std::runtime_error("Cannot remove from empty list");
  }

  DoubleNode<T>* temp = back;
  back = temp->prev();

  if (size == 1) {
    front = nullptr;
  }
  else {
    back->setNext(nullptr);
  }

  temp->setPrev(nullptr);

  T d = temp->data();
  delete temp;
  size--;
  return d;
}

template <class T>
void DoubleLinkedList<T>::printList() const {
  if (size == 0) {
    std::cout << "Empty list" << std::endl;
    return;
  }

  DoubleNode<T>* node = front;
  while (node != nullptr) {
    std::cout << node->data() << " ";
    node = node->next();
  }
  std::cout << std::endl;
}

template <class T>
T DoubleLinkedList<T>::get(unsigned int idx) const {
  if (idx > size - 1) {
    throw std::runtime_error("Retrieval index out of bounds");
  }

  DoubleNode<T>* node = front;
  for (int i=0; i<idx; ++i) {
    node = node->next();
  }
  return node->data();
}

template <class T>
T DoubleLinkedList<T>::deletePos(unsigned int idx) {
  if (size-1 < idx) {
    throw std::runtime_error("Deletion index out of bounds");
  }

  DoubleNode<T>* node = front;

  if (size == 1) {
    T d = front->data();
    front = nullptr;
    back = nullptr;
    delete node;
    size--;
    return d;
  }

  for (int i=0; i<idx; ++i) {
    node = node->next();
  }

  if (node == front) {
    front = node->next();
    front->setPrev(nullptr);
  }
  if (node == back) {
    back = node->prev();
    back->setNext(nullptr);
  }
  if ((idx != 0) && (idx != size-1)) {
  // if (node != front && node != back) {
    node->prev()->setNext(node->next());
    node->next()->setPrev(node->prev());
  }
  size--;

  node->setPrev(nullptr);
  node->setNext(nullptr);
  T d = node->data();
  delete node;
  return d;
}

template <class T>
int DoubleLinkedList<T>::find(const T& value) const {
  int idx = 0;
  DoubleNode<T>* node = front;
  while (node != nullptr) {
    if (node->data() == value) {
      break;
    }
    node = node->next();
    idx++;
  }
  return idx;
}


#endif
