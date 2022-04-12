#ifndef NODECLASS
#define NODECLASS
#include <string>
using namespace std;

class node{
  //Class Invariant (CI):
  // cId is the id of the course
  // next points to the next requirement. If there are no further
  //requirements, next = NULL.
 private:

  string cId; //Used to hold the course ID.

  node* next; // Used to hold the position of the next set of
	       // coordinates.
 public:

  //defualt constructor

  node(){
    cId = "None";
    next = NULL;
  }

  //constructor with id
  node(string id){
    cId = id;
    next = NULL;
  }

  //destructor
   ~node(){
     cId = "";
     next = NULL;
   }

  //PRE: id is a string which is a valid course id
  //POST: set cId to id
  void setId(string id){cId = id;}

  //PRE: CI is met
  //POST: returns value of cId
  string getId() const{return(cId);}
  
  //PRE: CI is met
  //     nextNode is defined and meets the CI
  //POST: sets next to nextNode
  void setNext(node* nextNode){next = nextNode;}

  //PRE: CI is met
  //POST: IF next != NULL, then returns next
  //      ELSE returns NULL.

  node* getNext() const{return(next);}
  
};
#endif
