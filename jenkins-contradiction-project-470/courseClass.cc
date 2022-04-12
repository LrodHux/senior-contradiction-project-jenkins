#include <string>
#include "node.cc"
using namespace std;

class course{
  //CI:
  // name is a string which holds the name of the course ex)
  // Principles of Programming
  // id is a string which holds the id of the course ex) CPSC463
  // requirements is a list of strings which are required to take
  // before takeing this course.

private:

  string name; // The name of the given course

  string id; // The id of the given course

  node requirements; // A list of requirements for the given course

public:

  //Default Constructor

  course(){
    name = "None";
    id = "None";
    requirements.setId("None");
    //ASSERT: This constructor sets all values to there default state.
  }

  //Parametric constructor

  //PRE: cName is a string
  //     cId is a string
  //POST: Sets name and id to cName and cId respectively.
  course(string cName, string cId){
    name = cName;
    id = cId;
    requirements.setId("None");
    //ASSERT: This constructor creates a new course which doesn't have
    //any requirements.
  }

  //Copy Constructor

  course(const course &Course1){
    name = Course1.name;
    id = Course1.name;
    requirements.setNext(NULL);
    requirements = Course1.requirements;
  }

  //destructor

  ~course(){
    delete[] name;
    delete[] id;
    delete[] requirements;
  }

  //Member Functions

  //PRE: newName is a string
  //POST: Changes the course name to newName
  void setName(string newName){
    name = newName;
  }

  //PRE: newId is a string
  //POST: Changes the course id to newId
  void setId(string newId){
    id = newId;
  }

  //PRE: newRequirements is a list of strings
  //POST: Changes the requirements to newRequirements
  void setRequirements(string* newRequirements){
    requirements = newRequirements;
  }

  //PRE:
  //POST: Resets requirements to default value
  void resetRequirements(){
    requirements = new string [1];
    requirements[0] = "None";
  }

  //PRE: i is a valid index for requirements
  //POST: Removes the requirement at requirements[i]
  void removeRequirement(int i){
    
  }
}
