#include "Simulation.h"
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

using std::string;
using std::cout;
using std::endl;
using std::cin;

void Simulation::run() {
  readTables();
  queryUser();
}

void Simulation::readTables() {
  if (fileExists("studentTable")) {
    readStudentTable();
  }

  if (fileExists("facultyTable")) {
    readFacultyTable();
  }
}



bool Simulation::fileExists(string fileName) const {
  bool exists = false;
  std::ifstream inFile (fileName);
  if (inFile.is_open()) {
    exists = true;
    inFile.close();
  }
  return exists;
}

void Simulation::readStudentTable() {
  std::ifstream studentFile ("studentTable");
  std::string line;

  int ID, advisor;
  string name, level, major;
  double gpa;
  while( getline(studentFile, line) ) {
    std::istringstream ssin(line);
    ssin >> ID >> name >> level >> major >> gpa >> advisor;
    masterStudent_.insert( Student(ID, name, level, major, gpa, advisor) );
  }
}

void Simulation::readFacultyTable() {
  std::ifstream facultyFile ("facultyTable");
  std::string line;

  int fID, sID;
  string name, level, dept;
  Faculty newFaculty;
  while( getline(facultyFile, line) ) {
    std::istringstream ssin(line);
    ssin >> fID >> name >> level >> dept;

    newFaculty = Faculty(fID, name, level, dept);
    while (ssin >> sID) { newFaculty.addStudent(sID); }
    masterFaculty_.insert(newFaculty);
  }
}

void Simulation::writeTables() {
  string delim = " ";
  // writeStudentTable(delim);
  // writeFacultyTable(delim);
  std::ofstream fout ("studentTable");
  recWriteStudent(masterStudent_.root(), fout, delim);
  fout.close();

  fout = std::ofstream("facultyTable");
  recWriteFaculty(masterFaculty_.root(), fout, delim);
  fout.close();
}

void Simulation::recWriteStudent(TreeNode<Student>* node, std::ofstream& fout, string delim) {
  if (node == nullptr) {return;}

  fout << (node->key()).infoLine(delim);
  recWriteStudent(node->left(),  fout, delim);
  recWriteStudent(node->right(), fout, delim);
}

void Simulation::recWriteFaculty(TreeNode<Faculty>* node, std::ofstream& fout, string delim) {
  if (node == nullptr) {return;}

  fout << (node->key()).infoLine(delim);
  recWriteFaculty(node->left(),  fout, delim);
  recWriteFaculty(node->right(), fout, delim);
}

void Simulation::queryUser() {
  int queryResult;
  displayMenu();
  cout << "Please choose from the options above: ";
  std::cin >> queryResult;
  executeRequest(queryResult);
  if (queryResult != 14) {
    queryUser();
  }
}

void Simulation::displayMenu() const {
  cout << endl;
  cout << "=========================================================\n";
  cout << "|  1.  Print all students and their information         |\n";
  cout << "|  2.  Print all faculty and their information          |\n";
  cout << "|  3.  Find and display a student's information         |\n";
  cout << "|  4.  Find and display a faculty member's information  |\n";
  cout << "|  5.  Print the info of a student's faculty advisor    |\n";
  cout << "|  6.  Print the info of a faculty member's advisees    |\n";
  cout << "|  7.  Add a new student                                |\n";
  cout << "|  8.  Delete a student                                 |\n";
  cout << "|  9.  Add a new faculty member                         |\n";
  cout << "|  10. Delete a faculty member                          |\n";
  cout << "|  11. Change a student’s advisor                       |\n";
  cout << "|  12. Remove an advisee from a faculty member          |\n";
  cout << "|  13. Rollback                                         |\n";
  cout << "|  14. Exit                                             |\n";
  cout << "=========================================================" << endl;
}

void Simulation::executeRequest(int request) {
  cout << endl;
  switch(request) {
    case 1: executeCase1(); break;
    case 2: executeCase2(); break;
    case 3: executeCase3(); break;
    case 4: executeCase4(); break;
    case 5: executeCase5(); break;
    case 6: executeCase6(); break;
    case 7: executeCase7(); break;
    case 8: executeCase8(); break;
    case 9: executeCase9(); break;
    case 10: executeCase10(); break;
    case 11: executeCase11(); break;
    case 12: executeCase12(); break;
    case 13: executeCase13(); break;
    case 14: writeTables();   break;
    default: cout << "Please provide a valid number (1-14)" << endl;
  }
}

void Simulation::executeCase1() const {
  cout << "You have selected case 1. The student list is as follows: " << endl;
  masterStudent_.printTree();
}

void Simulation::executeCase2() const {
  cout << "You have selected case 2. The faculty list is as follows: " << endl;
  masterFaculty_.printTree();
}

void Simulation::executeCase3() const {
  cout << "You have selected case 3. Please provide a student ID: ";
  int sID; cin >> sID;
  Student sKey (sID);
  try {
    cout << masterStudent_.get(sKey) << endl;
  } catch (const std::runtime_error& e) {
    cout << "The student you are searching for does not exist." << endl;
  }
}

void Simulation::executeCase4() const {
  cout << "You have selected case 4. Please provide a faculty ID: ";
  int fID; cin >> fID;
  Faculty fKey (fID);
  try {
    cout << masterFaculty_.get(fKey) << endl;
  } catch (const std::runtime_error& e) {
    cout << "The faculty member you are searching for does not exist." << endl;
  }
}

void Simulation::executeCase5() const {
  cout << "You have selected case 5. Please provide a student ID: ";
  int sID; cin >> sID;
  Student sKey (sID);
  Student s;
  try {
    s = masterStudent_.get(sKey);
  } catch (const std::runtime_error& e) {
    cout << "The student you are searching for does not exist." << endl;
    return;
  }

  cout << s.name() << "'s advisor is:" << endl;
  cout << masterFaculty_.get(Faculty(s.advisor())) << endl;
}

void Simulation::executeCase6() const {
  cout << "You have selected case 6. Please provide a faculty ID: ";
  int fID; cin >> fID;
  Faculty fKey (fID);
  Faculty f;
  try {
    f = masterFaculty_.get(fKey);
  } catch (const std::runtime_error& e) {
    cout << "The faculty member you are searching for does not exist." << endl;
    return;
  }

  cout << f.name() << "'s students are as follows:" << endl;
  printFacultyStudents(f.students().root());

}

void Simulation::printFacultyStudents(TreeNode<int>* node) const {
  if (node == nullptr) {return;}

  printFacultyStudents(node->left());
  Student sKey (node->key());
  cout << masterStudent_.get(sKey) << endl;
  printFacultyStudents(node->right());
}

void Simulation::executeCase7() {
  int id, advisorID;
  double gpa;
  std::string name, level, major;
  cout << "You have selected case 7. Please provide the student ID: ";
  cin >> id;
  cout << "What is the student's name? ";
  cin >> name;
  cout << "What is the student's grade level? ";
  cin >> level;
  cout << "What is the student's major? ";
  cin >> major;
  cout << "What is the student's GPA? ";
  cin >> gpa;
  cout << "What is the student's advisor ID? ";
  cin >> advisorID;

  if (!masterFaculty_.contains(Faculty(advisorID))) {
    cout << "The specified advisor could not be found. The student was not added." << endl;
  }
  else {
    saveState();
    Student newStudent(id, name, level, major, gpa, advisorID);
    masterStudent_.insert(newStudent);
    masterFaculty_.get(Faculty(advisorID)).addStudent(id);
    cout << "The student has been successfully added to the database." << endl;
  }
}

void Simulation::executeCase8() {
  cout << "You have selected case 8. Please provide the student ID: ";
  int sID; cin >> sID;

  if (!masterStudent_.contains(Student(sID))) {
    cout << "The student you are trying to delete does not exist." << endl;
    return;
  }

  saveState();

  Student studentToDelete = masterStudent_.get(Student(sID));
  int fID = studentToDelete.advisor();
  masterFaculty_.get(Faculty(fID)).deleteStudent(sID);
  masterStudent_.deleteNode(studentToDelete);
  cout << "The student has been successfully removed from the database." << endl;
}

void Simulation::executeCase9() {
  int fID;
  string name, level, dept;
  cout << "You have selected case 9. Please provide the faculty ID: ";
  cin >> fID;
  cout << "What is the advisor's name? ";
  cin >> name;
  cout << "What is the advisor's level? ";
  cin >> level;
  cout << "What is the advisor's department? ";
  cin >> dept;

  saveState();

  masterFaculty_.insert( Faculty(fID, name, level, dept) );
  cout << "The faculty member has been successfully added to the database." << endl;
}

void Simulation::executeCase10() {
  cout << "You have selected case 10. Please provide a faculty ID to delete: ";
  int fID; cin >> fID;
  if ( !masterFaculty_.contains(Faculty(fID)) ) {
    cout << "The faculty member you are attempting to delete does not exist." << endl;
    return;
  }

  Faculty f = masterFaculty_.get(Faculty(fID));
  if ( !f.students().isEmpty() ) {
    cout << "Sorry, you can only delete an advisor after their students have been reassigned." << endl;
  }
  else {
    saveState();
    masterFaculty_.deleteNode(f);
    cout << "The faculty member has been successfully deleted." << endl;
  }

}

void Simulation::executeCase11() {
  cout << "You have selected case 11. Please provide a student ID: ";
  int sID; cin >> sID;
  if ( !masterStudent_.contains(Student(sID)) ) {
    cout << "The student you entered could not be found." << endl;
    return;
  }

  cout << "And please provide the ID of their new faculty advisor: ";
  int newfID; cin >> newfID;
  if ( !masterFaculty_.contains(Faculty(newfID)) ) {
    cout << "The advisor you entered could not be found." << endl;
    return;
  }

  saveState();

  int oldfID = masterStudent_.get(Student(sID)).advisor();
  masterStudent_.get(Student(sID)).advisor() = newfID;
  masterFaculty_.get(Faculty(oldfID)).deleteStudent(sID);
  masterFaculty_.get(Faculty(newfID)).addStudent(sID);
  cout << "The student's advisor has been modified successfully." << endl;
}

void Simulation::executeCase12() const {
  cout << "I chose not to implement this query/request. I consider this case to\n"
       << "be either ill-posed, or at best redundant with cases 8 and 11." << endl;
}

void Simulation::executeCase13() {
  if (masterStudentHistory_.getSize() == 0) {
    cout << "Sorry, there are no remaining states to roll back." << endl;
  }
  else {
    masterStudent_ = masterStudentHistory_.removeFront();
    masterFaculty_ = masterFacultyHistory_.removeFront();
    cout << "Previous save state has been loaded." << endl;
  }
}

void Simulation::saveState() {
  masterStudentHistory_.insertFront(masterStudent_);
  masterFacultyHistory_.insertFront(masterFaculty_);
  if (masterStudentHistory_.getSize() == 6) {
    masterStudentHistory_.removeBack();
    masterFacultyHistory_.removeBack();
  }
}
