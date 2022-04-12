#include "courseList.h"
#include "exceptions.h"
#include <iostream>
using namespace std;

//PRE: c is a valid course.
//POST: adds a node to the front of the list for c.
void courseList::addToFront(course c){
  courseNode* previousFirst = firstNode;
  firstNode = new courseNode(c);
  firstNode->setNext(previousFirst);
  numElements++;
}

//PRE: c is a valid course.
//POST: adds a node to the back of the list for c.
void courseList::addToBack(course c){
  if(numElements == 0){
    addToFront(c);
  }
  else{
    int counter = 1;
    courseNode* current = firstNode;
    while(counter < numElements){
      current = current->getNext();
      counter++;
    }
    current->setNext(new courseNode(c));
    numElements++;
  }
}

//PRE: c1 is a valid courseList.
//POST: adds all nodes from c1 to the front of the list.
void courseList::addToFront(courseList c1){
  course c;
  int x = c1.numElements - 1;
  while(x >= 0){
    c = c1.getXCourse(x);
    addToFront(c);
    x--;
  }
  //ASSERT: While x >= 0, get the course at x, add it to the front
  //of this, and decrement x.
}

//PRE: c1 is a valid courseList.
//POST: adds all nodes from c1 to the back of the list.
void courseList::addToBack(courseList c1){
  course c;
  while(c1.numElements > 0){
    c = c1.getFirst()->getCourse();
    addToBack(c);
    c1.removeNode(0);
  }
  //ASSERT: While there are still elements in c1, add the first node
  //to the back of this and remove it from c1.
}

//PRE: x is an integer
//POST: returns the id of the xth node in the list.
string courseList::getXId(int x){
  string toReturn; // The string that is returned at the end.
  if(x >= numElements){
    toReturn = "NULL";
  }
  //ASSERT: This returns an error in the event that the list has less
  //than x elements.
  else{
    courseNode* xNode = firstNode;
    for(int i = 0; i < x; i++){
      xNode = xNode->getNext();
    }
    toReturn = xNode->getId();
  }
  return toReturn;
}

//PRE: x is an integer
//POST: returns the course at position x.
course courseList::getXCourse(int x){
  course toReturn; // The string that is returned at the end.
  if(x >= numElements){
    Exception e("Out of range.");
    throw e;
  }
  //ASSERT: This returns an error in the event that the list has less
  //than x elements.
  else{
    courseNode* xNode = firstNode;
    for(int i = 0; i < x; i++){
      xNode = xNode->getNext();
    }
    toReturn = xNode->getCourse();
  }
  return toReturn;
}

//PRE: cId is a string
//POST: Returns the position of the node with id = cId
int courseList::getPos(string cId){
  bool isIn = true;
  courseNode* currentNode = firstNode;
  string currentId = currentNode->getId();
  int pos = 0;
  while(isIn == true and currentId != cId){
    if(pos+1 == numElements){
      isIn = false;
    }// ASSERT: If pos+1 == numElements then there is no possible node
     // which has cId as its id.
    else{
      currentNode = currentNode->getNext();
      currentId = currentNode->getId();
      pos++;
    } //ASSERT: else, set the id to be checked to the next node's id.
  }
  if(isIn == false){
    Exception e("No such node with the given id exists");
    throw(e);
  }
  return pos;
}

//PRE: cId is a string
//POST: returns the course with id = cId.
course courseList::getICourse(string cId){
  int i;
  try{
    i = this->getPos(cId);
  }
  catch(Exception e){
    throw e;
  }
  return this->getXCourse(i);
}

//PRE: x is an integer
//POST: Removes the node at position x.
void courseList::removeNode(int x){
  if(x >= numElements){
    //do nothing
  }
  else{
    courseNode* previous = NULL;
    courseNode* current = firstNode;
    for(int i = 0; i < x; i++){
      previous = current;
      current = current->getNext();
    }
    if(x == 0){
      firstNode = firstNode->getNext();
      numElements--;
    }
    else{
      previous->setNext(current->getNext());
      current->setNext(NULL);
      numElements--;
    }
  }
}

//PRE: cId is a string
//POST: Removes the node with id cId from the list
void courseList::removeNode(string cId){
  int pos;
  try{
    pos = this->getPos(cId);
  }
  catch(Exception e){
    throw e;
  }
  this->removeNode(pos);
}

//PRE: cId is a string.
//POST: Returns a string containing all requirements for the course.
string courseList::getBasicReqs(string cId){
  course c;
  try{
    c = this->getICourse(cId);
  }
  catch(Exception e){
    throw e;
  }
  linkList hardReqs = c.getHardReqs();
  linkList softReqs = c.getSoftReqs();
  int softNeeded = c.getSoftNeeded();
  bool done = false;
  bool hardMentioned = false;
  string toReturn = "";
  while(!done){
    if(hardReqs.getSize() > 0 and hardMentioned == false){
      toReturn += "Hard Requirements: ";
      hardMentioned = true;
    }
    //ASSERT: There are hard requirements to add. Make sure the string
    //reflects this is the case.
    else if(hardReqs.getSize() > 0){
      toReturn += hardReqs.getXId(0);
      hardReqs.removeNode(0);
      if(hardReqs.getSize() > 0){
	toReturn += ", ";
      }
      //ASSERT: There are still more hard requirements to add. Add a
      //comma to the end.
    }
    //ASSERT: If there are still hard requirements in hardReqs, add
    //their id to the list and remove the 0th hard requirement from
    //hardReqs.
    else{
      done = true;
    }
    //ASSERT: There are no hard requirements left.
  }
  //cout << "Got past hardReqs" << endl;
  //ASSERT: While not done, add all hard requirements to the string.
  bool softMentioned = false;
  done = false;
  while(!done){
    if(softReqs.getSize() > 0 and hardMentioned == true and softMentioned == false){
      toReturn += "; ";
      toReturn += "Soft Requirements (";
      toReturn += to_string(softNeeded);
      toReturn += " of): ";
      softMentioned = true;
    }
    //ASSERT: If there are hard requirements, separate them with a
    //semi-colon and add text acknowledging where the soft
    //requirements begin.
    else if(softReqs.getSize() > 0 and hardMentioned == false and softMentioned == false){
      toReturn += "Soft Requirements (";
      toReturn += to_string(softNeeded);
      toReturn += " of): ";
      softMentioned = true;
    }
    //ASSERT: If there are no hard requirements, begin the string by
    //announcing the soft requirements.
    else if(softReqs.getSize() > 0){
      toReturn += softReqs.getXId(0);
      softReqs.removeNode(0);
      if(softReqs.getSize() > 0){
	toReturn += ", ";
      }
      //ASSERT: There are still more soft requirements to add. Add a
      //comma to the end.
    }
    //ASSERT: If there are still soft requirements in hardReqs, add
    //their id to the list and remove the 0th soft requirement from
    //hardReqs.
    else{
      done = true;
    }
    //ASSERT: There are no hard requirements left.
  }
  if(hardMentioned == false and softMentioned == false){
    toReturn = "No requirements.";
  }
  //ASSERT: While not done, add all soft requirements to the string.
  return toReturn;
}

//PRE: cId is a string.
//POST: Returns a string containing all requirements for the course.
string courseList::getDeepReqs(string cId){
  course c;
  try{
    c = this->getICourse(cId);
  }
  catch(Exception e){
    throw e;
  }
  linkList hardReqs = c.getHardReqs();
  linkList softReqs = c.getSoftReqs();
  int softNeeded = c.getSoftNeeded();
  bool done = false;
  bool hardMentioned = false;
  string toReturn = "";
  string hold;
  while(!done){
    if(hardReqs.getSize() > 0 and hardMentioned == false){
      toReturn += "Hard Requirements: ";
      hardMentioned = true;
    }
    //ASSERT: There are hard requirements to add. Make sure the string
    //reflects this is the case.
    else if(hardReqs.getSize() > 0){
      hold = hardReqs.getXId(0);
      toReturn += hold;
      toReturn += "(requires: [";
      toReturn += this->getDeepReqs(hold);
      toReturn += "])";
      hardReqs.removeNode(0);
      if(hardReqs.getSize() > 0){
	toReturn += ", ";
      }
      //ASSERT: There are still more hard requirements to add. Add a
      //comma to the end.
    }
    //ASSERT: If there are still hard requirements in hardReqs, add
    //their id to the list and remove the 0th hard requirement from
    //hardReqs.
    else{
      done = true;
    }
    //ASSERT: There are no hard requirements left.
  }
  //ASSERT: While not done, add all hard requirements to the string.
  //cout << "hold" << endl;
  bool softMentioned = false;
  done = false;
  while(!done){
    if(softReqs.getSize() > 0 and hardMentioned == true and softMentioned == false){
      toReturn += "; ";
      toReturn += "Soft Requirements (";
      toReturn += to_string(softNeeded);
      toReturn += " of): ";
      softMentioned = true;
    }
    //ASSERT: If there are hard requirements, separate them with a
    //semi-colon and add text acknowledging where the soft
    //requirements begin.
    else if(softReqs.getSize() > 0 and hardMentioned == false and softMentioned == false){
      toReturn += "Soft Requirements (";
      toReturn += to_string(softNeeded);
      toReturn += " of): ";
      softMentioned = true;
    }
    //ASSERT: If there are no hard requirements, begin the string by
    //announcing the soft requirements.
    else if(softReqs.getSize() > 0){
      hold = softReqs.getXId(0);
      toReturn += hold;
      toReturn += "(requires: [";
      toReturn += this->getDeepReqs(hold);
      toReturn += "])";
      softReqs.removeNode(0);
      if(softReqs.getSize() > 0){
	toReturn += ", ";
      }
      //ASSERT: There are still more soft requirements to add. Add a
      //comma to the end.
    }
    //ASSERT: If there are still soft requirements in hardReqs, add
    //their id to the list and remove the 0th soft requirement from
    //hardReqs.
    else{
      done = true;
    }
    //ASSERT: There are no hard requirements left.
  }
  if(hardMentioned == false and softMentioned == false){
    toReturn = "No requirements.";
  }
  //ASSERT: While not done, add all soft requirements to the string.
  return toReturn;
}
