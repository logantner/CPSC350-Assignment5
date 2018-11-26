#ifndef _COLLECTION_H_
#define _COLLECTION_H_

template <class T> class Collection {
public:
  virtual ~Collection() = default;

  virtual void insertFront(T) = 0;
  virtual void insertBack(T) = 0;
  virtual T removeFront() = 0;
  virtual T removeBack() = 0;
  virtual T get(unsigned int) const = 0;
  virtual T deletePos(unsigned int) = 0;
  virtual int find(const T&) const = 0;

  virtual unsigned int getSize() const = 0;
  virtual void printList() const = 0;
};

#endif
