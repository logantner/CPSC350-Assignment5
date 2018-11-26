#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <iostream>
#include <string>

class Student {
public:
  // Constructors
  Student() {}
  Student(int ID) : ID_(ID) {}
  Student(int ID, std::string name, std::string level, std::string major, double GPA, int advisor)
    : ID_(ID), name_(name), level_(level), major_(major), GPA_(GPA), advisor_(advisor) {}
  // Rule of three functions
  ~Student() {}
  Student(const Student& other) { copy(other); }
  Student& operator = (const Student& other) { copy(other); return *this; }
  // Operator overloads
  bool operator == (Student other) const { return ID_ == other.ID_; }
  bool operator != (Student other) const { return ID_ != other.ID_; }
  bool operator < (Student other) const  { return ID_ <  other.ID_; }
  bool operator > (Student other) const  { return ID_ >  other.ID_; }
  friend std::ostream& operator << (std::ostream& os, const Student& s) {
    os << "ID: " << s.ID_
       << " | Name: " << s.name_
       << " | Level: " << s.level_
       << " | Major: " << s.major_
       << " | GPA: " << s.GPA_
       << " | Advisor: " << s.advisor_;
    return os;
  }
  // Getters and setters
  std::string name() const { return name_; }
  int advisor() const { return advisor_; }
private:
  // Fields
  int ID_;
  std::string name_;
  std::string level_;
  std::string major_;
  double GPA_;
  int advisor_;

  void copy(const Student& other) {
    ID_ = other.ID_;
    name_ = other.name_;
    level_ = other.level_;
    major_ = other.major_;
    GPA_ = other.GPA_;
    advisor_ = other.advisor_;
  }
};

#endif
