#ifndef COURSECLASS
#define COURSECLASS
#include <string>
#include "linkList.h"
using namespace std;

class course{
  //Class Invarient
  // name is a string which represents the name of a given course.
  // id is a string which represents the id of a given course.
  // requirements is a linked list which hold the course id's of
  // courses required to take the given course.

 private:
  string name; //Used to hold the course name.

  string id; //Used to hold the course id.

  linkList hardReqs; //Used to hold absolute requirements of a given
		     //course.
  linkList softReqs; //Used to hold requirements which can be
		     //substituted with others in this group.
  int softReqsNeeded; //Used to hold the number of soft requirements
		      //needed before a requirement is satified.
  float credits;

 public:
  //default constructor
  course(){
    name = "None";
    id = "None";
    softReqsNeeded = 0;
    credits = 0;
    //No need to set requirements to default value since it is at a
    //default value upon definition.
  }

  //copy constructor
  course(const course &c1){
    name = c1.name;
    id = c1.id;
    hardReqs = c1.hardReqs;
    softReqs = c1.softReqs;
    softReqsNeeded = c1.softReqsNeeded;
    credits = c1.credits;
    //Will work due to the copy constructor for linkList objects
  }

  //parametric constructors

  //id constructor
  course(string cId){
    name = "None";
    id = cId;
    softReqsNeeded = 0;
    credits = 0;
    //id is a vital part of the course, creates a default course with
    //the given id.
  }

  //name, id constructor
  course(string cName, string cId){
    name = cName;
    id = cId;
    softReqsNeeded = 0;
    credits = 0;
    //Creates a course with a given name and id with no requirements.
  }

  //name, id, credits constructor
  course(string cName, string cId, float creds){
    name = cName;
    id = cId;
    softReqsNeeded = 0;
    credits = creds;
    //Creates a course with a given name and id with no requirements.
  }

  //hardReqs constructor
  course(string cName, string cId, linkList cReqs){
    name = cName;
    id = cId;
    hardReqs = cReqs;
    softReqsNeeded = 0;
    credits = 1;
    //Creates a course with name, id and a list of hard requirements.
  }

  //hardReqs constructor
  course(string cName, string cId, linkList cReqs, float creds){
    name = cName;
    id = cId;
    hardReqs = cReqs;
    softReqsNeeded = 0;
    credits = creds;
    //Creates a course with name, id and a list of hard requirements.
  }

  //full constructor
  course(string cName, string cId, linkList hReqs, linkList sReqs, int numNeeded){
    name = cName;
    id = cId;
    hardReqs = hReqs;
    softReqs = sReqs;
    softReqsNeeded = numNeeded;
    credits = 1;
    //Creates a course with name, id and a list requirements.
  }

  //full constructor
  course(string cName, string cId, linkList hReqs, linkList sReqs, int numNeeded, float creds){
    name = cName;
    id = cId;
    hardReqs = hReqs;
    softReqs = sReqs;
    softReqsNeeded = numNeeded;
    credits = creds;
    //Creates a course with name, id and a list requirements.
  }

  //PRE:
  //POST: Returns the name of the course.
  string getName(){return name;}

  //PRE:
  //POST: Returns the course id.
  string getId(){return id;}

  //PRE:
  //POST: Returns the list of hard requirements.
  linkList getHardReqs(){return hardReqs;}

  //PRE:
  //POST: Returns the list of soft requirements.
  linkList getSoftReqs(){return softReqs;}

  //PRE:
  //POST: Returns the number of soft requirements that must be
  //completed to take the course.
  int getSoftNeeded(){return softReqsNeeded;}

  //PRE:
  //POST: Returns the credits the course is worth
  float getCredits(){return credits;}

  //PRE: cName is a string which represents a course name.
  //POST: The course name is set to cName.
  void setName(string cName){name = cName;}

  //PRE: cId is a string which represents a course id.
  //POST: The course name is set to cId.
  void setId(string cId){id = cId;}

  //PRE: cReqs is a list of requirements for the course.
  //POST: The hard requirements of the course are changed to cReqs.
  void setHardReqs(linkList cReqs){hardReqs = cReqs;}

  //PRE: cReqs is a list of requirements for the course.
  //POST: The soft requirements of the course are changed to cReqs.
  void setSoftReqs(linkList cReqs){softReqs = cReqs;}

  //PRE: i is an integer.
  //POST: Sets the number of soft requirements nessecary to take this
  //course to i.
  void setSoftNeeded(int i){softReqsNeeded = i;}

  //PRE: k is a float
  //POST: Sets the credits to k
  void setCredits(float k){credits = k;}

  //PRE: id is an id of a course that is required for this course.
  //POST: The course with ID = id is added as a hard requirement for this
  //course.
  void addHardReq(string id){hardReqs.addToBack(id);}

  //PRE: id is a hard course required for this course
  //POST: removes the hard requirement with the ID of id.
  void removeHardReq(string id){hardReqs.removeNode(id);}

  //PRE: id is an id of a course that is required for this course.
  //POST: The course with ID = id is added as a soft requirement for this
  //course.
  void addSoftReq(string id){softReqs.addToBack(id);}

  //PRE: id is a soft course required for this course
  //POST: removes the soft requirement with the ID of id.
  void removeSoftReq(string id){softReqs.removeNode(id);}
};

#endif
