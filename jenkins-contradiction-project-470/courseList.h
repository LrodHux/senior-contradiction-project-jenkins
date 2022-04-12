#ifndef _COURSELIST
#define _COURSELIST
#include "courseNode.h"
#include "courseClass.h"
#include <string>
#include <iostream>
class courseList{
  //Class Invarient (CI):
  // firstPoint points to a valid point or
  //                        firstPoint = NULL
  // numElements >= 0
 private:
  courseNode* firstNode; // Points to the first point in the list.

  int numElements;

 public:
  //default constructor
  courseList(){
    firstNode = NULL; //Ensures that firstPoint points to NULL 
    numElements = 0; //Defines numElements as 0
  }

  //copy constructor
  courseList(const courseList &l1){
    firstNode = l1.firstNode;
    numElements = l1.numElements;
  }

  //deconstructor
  ~courseList(){
    firstNode = NULL;
    numElements = 0;
  }
  
  //PRE: The CI is met
  //     numElements = n
  //POST: returns n
  int getSize() const{return(numElements);}

  //PRE: CI is met
  //POST: returns pointer for firstPoint
  courseNode* getFirst(){return(firstNode);}

  //PRE: c is a valid course.
  //POST: adds a node to the front of the list for c.
  void addToFront(course c);

  //PRE: c is a valid course
  //POST: adds a node to the back of the list for c.
  void addToBack(course c);

  //PRE: c1 is a valid courseList.
  //POST: adds all nodes from c1 to the front of the list.
  void addToFront(courseList c1);

  //PRE: c1 is a valid courseList
  //POST: adds all nodes from c1 to the back of the list.
  void addToBack(courseList c1);

  //PRE: x is an integer
  //POST: returns the id of the xth node in the list.
  std::string getXId(int x);

  //PRE: x is an integer
  //POST returns the course at the xth position.
  course getXCourse(int x);

  //PRE: cId is a string
  //POST: Returns the position of the node with id = cId.
  int getPos(std::string cId);

  //PRE: cId is a string
  //POST returns the course with id = cId.
  course getICourse(std::string cId);
  
  //PRE: x is an integer.
  //POST: removes the xth node from the list
  void removeNode(int x);

  //PRE: cId is a string.
  //POST: removes the node with id cId from the list
  void removeNode(std::string cId);

  //PRE: cId is a valid course id in the list.
  //POST: Returns a string containing all requirements for the course.
  std::string getBasicReqs(std::string cId);

  //PRE: cId is a valid course id in the list.
  //POST: Returns a string containing all requirements for the course
  //and every requirement of each required course.
  std::string getDeepReqs(std::string cId);
};
#endif
