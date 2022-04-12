#ifndef _LINKLIST
#define _LINKLIST
#include "node.h"
#include <string>
#include <iostream>
class linkList{
  //Class Invarient (CI):
  // firstPoint points to a valid point or
  //                        firstPoint = NULL
  // numElements >= 0
 private:
  node* firstNode; // Points to the first point in the list.

  int numElements;

 public:
  //default constructor
  linkList(){
    firstNode = NULL; //Ensures that firstPoint points to NULL 
    numElements = 0; //Defines numElements as 0
  }

  //copy constructor
  linkList(const linkList &l1){
    firstNode = l1.firstNode;
    numElements = l1.numElements;
  }

  //deconstructor
  ~linkList(){
    firstNode = NULL;
    numElements = 0;
  }
  
  //PRE: The CI is met
  //     numElements = n
  //POST: returns n
  int getSize() const{return(numElements);}

  //PRE: CI is met
  //POST: returns pointer for firstPoint
  node* getFirst(){return(firstNode);}

  //PRE: id is a valid course id.
  //POST: adds a node to the front of the list for id.
  void addToFront(std::string id);

  //PRE: id is a valid course id
  //POST: adds a node to the back of the list for id.
  void addToBack(std::string id);

  //PRE: x is an integer
  //POST: returns the id of the xth node in the list.
  std::string getXId(int x);

  //PRE: cId is a string
  //POST: Returns the position of the node with id = cId.
  int getPos(std::string cId);

  //PRE: x is an integer.
  //POST: removes the xth node from the list
  void removeNode(int x);

  //PRE: cId is a string.
  //POST: removes the node with id cId from the list
  void removeNode(std::string cId);
};
#endif
