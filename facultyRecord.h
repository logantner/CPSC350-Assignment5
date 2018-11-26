#ifndef _FACULTY_RECORD_H_
#define _FACULTY_RECORD_H_

#include <string>
// #include "doubleLinkedList.h"
#include "BST.h"

class Faculty {
public:
  // Constructors
  Faculty() {}
  Faculty(int ID) : ID_(ID) {}
  Faculty(int ID, std::string name, std::string level, std::string dept)
    : ID_(ID), name_(name), level_(level), department_(dept) {}
  // Rule of three methods
  ~Faculty() {}
  Faculty(const Faculty& other) { copy(other); }
  Faculty& operator = (const Faculty& other) { copy(other); return *this; }
  // Operator overloads
  bool operator == (Faculty other) const { return ID_ == other.ID_; }
  bool operator != (Faculty other) const { return ID_ != other.ID_; }
  bool operator < (Faculty other) const  { return ID_ <  other.ID_; }
  bool operator > (Faculty other) const  { return ID_ >  other.ID_; }
  friend std::ostream& operator << (std::ostream& os, const Faculty& f) {
    os << "ID: " << f.ID_ << " | Name: " << f.name_ << " | Level: " << f.level_ << " | Department: " << f.department_ << std::endl;
    os << "\t Students: ";
    f.students_.printTree(os, " ");
    return os;
  }
  // Getters and setters
  void addStudent(int sID) { students_.insert(sID); }
  std::string name() const { return name_; }
  BST<int> students() const { return students_; }
private:
  // Fields
  int ID_;
  std::string name_;
  std::string level_;
  std::string department_;
  BST<int> students_;

  void copy(const Faculty& other) {
    ID_ = other.ID_;
    name_ = other.name_;
    level_ = other.level_;
    department_ = other.department_;
    students_ = other.students_;
  }
};

#endif
