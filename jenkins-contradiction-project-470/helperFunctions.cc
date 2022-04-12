#include "student.h"
#include "repository.h"
#include "courseList.h"
#include "linkList.h"
#include "courseClass.h"
#include "exceptions.h"
#include <iostream>
#include <string>
using namespace std;

//PRE: cList is a courseList object.
//POST: prints all courses by their name.
void printCourseName(courseList cList){
  int x = cList.getSize();
  for(int i = 0; i < x; i++){
    cout << cList.getXCourse(i).getName() << endl;
  }
}

//PRE: cList is a courseList object.
//POST: prints all courses by their id.
void printCourseId(courseList cList){
  int x = cList.getSize();
  for(int i = 0; i < x; i++){
    cout << cList.getXCourse(i).getId() << endl;
  }
}

//PRE: id is a string of a course id
//     cList is a courseList object
//POST: returns true iff the course with id = id is in cList.
bool isCourseIn(string id, courseList cList){
  bool toReturn = true;
  course c;
  try{
    c = cList.getICourse(id);
  }
  catch(Exception e){
    cout << "Caught the Exception: " << id << endl;
    toReturn = false;
  }
  return toReturn;
}

//PRE: c is a course object.
//     s is a student object.
//POST: Returns true iff the student has taken all required courses
//     for this course, or is taking required courses for the course.
bool canTakeCourse(course c, student s){
  bool toReturn = true;
  linkList hardReqs = c.getHardReqs();
  linkList softReqs = c.getSoftReqs();
  int softNeeded = c.getSoftNeeded();
  courseList takenTaking = s.getCoursesTaken();
  takenTaking.addToBack(s.getCurrentCourses());
  //ASSERT: This combines the two list of courses a student has taken
  //and is taking for ease of checking.
  while(hardReqs.getSize() > 0 and toReturn){
    if(isCourseIn(hardReqs.getXId(0), takenTaking)){
      hardReqs.removeNode(0);
    }
    //ASSERT: If the course exists in takenTaking, remove it from
    //hardReqs and run through again.
    else{
      toReturn = false;
    }
    //ASSERT: If the courses isn't in takenTaking, toReturn = false.
  }
  //ASSERT: Ensures all hard requirements are met before continuing.
  
  while(softReqs.getSize() > 0 and softNeeded > 0 and toReturn){
    if(isCourseIn(softReqs.getXId(0), takenTaking)){
      softNeeded--;
      softReqs.removeNode(0);
    }
    //ASSERT: If the course exists in takenTaking, remove it from
    //hardReqs and run through again.
    else{
      softReqs.removeNode(0);
    }
    //ASSERT: If the courses isn't in takenTaking, toReturn = false.
  }
  //ASSERT: Ensures all soft requirements are checked before continuing.
  if(softNeeded > 0){
    toReturn = false;
  }
  //ASSERT: Not all soft requirements were met.
  return toReturn;
}

//PRE: mList is a courseList with major requirements.
//     s is a student
//POST: returns true IFF the student has taken all courses and is
//      taking required courses.
bool hasCompletedMajorRequirements(courseList mList, student s){
  bool toReturn = true;
  int x = mList.getSize();
  int i = 0;
  while(i < x and toReturn){
    if(canTakeCourse(mList.getXCourse(x), s)){
      i++;
    }
    //ASSERT: If the sections requirements are met, increment i.
    else{
      toReturn = false;
    }
    //ASSERT: If the sections requirements are not met, set toReturn
    //to false.
  }
  //ASSERT: While i < x and toReturn = true, check if the student has
  //completed the requirements for the section i of the major.
  return toReturn;
}
