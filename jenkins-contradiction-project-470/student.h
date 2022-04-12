#ifndef STUDENTS
#define STUDENTS
#include "courseList.h"
#include <string>
using namespace std;
class student{
  //Class Invarient (CI):
  //name is a string which is the contains the students full name ex)
  //John Hopkins
  //id is a string of 6 numbers which are the student's id ex) 000001
  //coursesTaken is a list of courses the student has taken.
 private:
  string name;

  string id;

  courseList coursesTaken;

  courseList currentCourses;

 public:
  //default constructor
  student(){
    name = "Place Holder";
    id = "000000";
  }

  //parametric constructors

  //name/id constructor
  student(string sName, string sId){
    name = sName;
    id = sId;
  }
  
  //taken constructor
  student(string sName, string sId, courseList cTaken){
    name = sName;
    id = sId;
    coursesTaken = cTaken;
  }

  //full constructor
  student(string sName, string sId, courseList cTaken, courseList cCourses){
    name = sName;
    id = sId;
    coursesTaken = cTaken;
    currentCourses = cCourses;
  }
  
  //PRE:
  //POST: returns the name of the student.
  string getName(){return name;}

  //PRE:
  //POST: returns the id of the student.
  string getId(){return id;}

  //PRE:
  //POST: returns the courses taken by the student.
  courseList getCoursesTaken(){return coursesTaken;}

  //PRE:
  //POST: returns teh courses being taken by the student.
  courseList getCurrentCourses(){return currentCourses;}

  //PRE: sName is a string of someone's name.
  //POST: Changes name to sName.
  void setName(string sName){name = sName;}

  //PRE: sId is a string of 6 digits
  //POST: sets id to sId.
  void setId(string sId){id = sId;}

  //PRE: cTaken is a list of courses.
  //POST: set coursesTaken to cTaken.
  void setCoursesTaken(courseList cTaken){coursesTaken = cTaken;}

  //PRE: cCourses is a list of courses
  //POST sets currentCourses to cCourses
  void setCurrentCourses(courseList cCourses){currentCourses = cCourses;}
  
  //PRE: c is a course
  //POST: adds c to courses taken.
  void addTakenCourse(course c){coursesTaken.addToBack(c);}

  //PRE: c is a course in coursesTaken.
  //POST: Removes c from coursesTaken.
  void removeTakenCourse(course c){coursesTaken.removeNode(c.getId());}

  //PRE: c is a course
  //POST: adds c to current courses.
  void addCurrentCourse(course c){currentCourses.addToBack(c);}

  //PRE: c is a course in currentCourses.
  //POST: Removes c from currentCourses.
  void removeCurrentCourse(course c){currentCourses.removeNode(c.getId());}
};
#endif
