#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include <string>
#include "student.h"
#include "facultyRecord.h"
#include "BST.h"
#include "TreeNode.h"

class Simulation {
public:
  Simulation() {}
  ~Simulation() {}

  void run();
private:
  BST<Student> masterStudent_;
  BST<Faculty> masterFaculty_;
  // File reading methods
  void readTables();
  bool fileExists(std::string) const;
  void readStudentTable();
  void readFacultyTable();
  // Query methods
  void queryUser();
  void displayMenu() const;
  // Execution methods
  void executeRequest(int);
  void executeCase1() const;
  void executeCase2() const;
  void executeCase3() const;
  void executeCase4() const;
  void executeCase5() const;
  void executeCase6() const;
  void printFacultyStudents(TreeNode<int>*) const;
  void executeCase7();
  // void executeCase8();
  // void executeCase9();
  // void executeCase11();
  // void executeCase12();
  // void executeCase13();
};

#endif
