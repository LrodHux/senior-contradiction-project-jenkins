#ifndef COURSENODE
#define COURSENODE
#include <string>
#include "courseClass.h"
using namespace std;

class courseNode{
  //Class Invariant (CI):
  // c is a valid course
  // next points to the next course. If there are no further
  // courses, next = NULL.
 private:

  course c; //Used to hold the course ID.

  courseNode* next; // Used to hold the position of the next set of
	       // coordinates.
 public:

  //defualt constructor

  courseNode(){
    next = NULL;
  }

  //constructor with course
  courseNode(course c1){
    c = c1;
    next = NULL;
  }

  //destructor
   ~courseNode(){
     next = NULL;
   }

  //PRE: c1 is a valid course
  //POST: sets c to c1
  void setCourse(course c1){c = c1;}

  //PRE: CI is met
  //POST: returns the course
  course getCourse() const{return(c);}

  //PRE:
  //POST: returns the id of the course
  string getId(){return c.getId();}
  
  //PRE: CI is met
  //     nextNode is defined and meets the CI
  //POST: sets next to nextNode
  void setNext(courseNode* nextNode){next = nextNode;}

  //PRE: CI is met
  //POST: IF next != NULL, then returns next
  //      ELSE returns NULL.

  courseNode* getNext() const{return(next);}
  
};
#endif
