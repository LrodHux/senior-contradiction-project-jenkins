#include "linkList.h"
#include "exceptions.h"
using namespace std;

//PRE: id is a valid course id.
//POST: adds a node to the front of the list for id.
void linkList::addToFront(string id){
  node* previousFirst = firstNode;
  firstNode = new node(id);
  firstNode->setNext(previousFirst);
  numElements++;
}

//PRE: id is a valid course id.
//POST: adds a node to the back of the list for id.
void linkList::addToBack(string id){
  if(numElements == 0){
    addToFront(id);
  }
  else{
    int counter = 1;
    node* current = firstNode;
    while(counter < numElements){
      current = current->getNext();
      counter++;
    }
    current->setNext(new node(id));
    numElements++;
  }
}

//PRE: x is an integer
//POST: returns the id of the xth node in the list.
string linkList::getXId(int x){
  string toReturn; // The string that is returned at the end.
  if(x >= numElements){
    toReturn = "NULL";
  }
  //ASSERT: This returns an error in the event that the list has less
  //than x elements.
  else{
    node* xNode = firstNode;
    for(int i = 0; i < x; i++){
      xNode = xNode->getNext();
    }
    toReturn = xNode->getId();
  }
  return toReturn;
}

//PRE: cId is a string
//POST: Returns the position of the node with id = cId
int linkList::getPos(string cId){
  bool isIn = true;
  node* currentNode = firstNode;
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

//PRE: x is an integer
//POST: Removes the node at position x.
void linkList::removeNode(int x){
  if(x >= numElements){
    //do nothing
  }
  else{
    node* previous = NULL;
    node* current = firstNode;
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
void linkList::removeNode(string cId){
  int pos;
  try{
    pos = this->getPos(cId);
  }
  catch(Exception e){
    throw e;
  }
  this->removeNode(pos);
}
