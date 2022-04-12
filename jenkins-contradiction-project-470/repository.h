#ifndef REPOSITORY
#define REPOSITORY
#include "courseList.h"
#include "courseClass.h"
#include "exceptions.h"
#include <string>

class repository{
  // Class Invarient (CI)
  // courses is a courseList object which holds all potential courses.
  // major is a courseList object which holds the requirements for a
  // given major.
 private:
  
  courseList courses;

  courseList major;

  std::string majorName;

 public:
  //default constructor
  repository(){
    majorName = "Unknown";
  }
  //partial parametric constructor
  repository(courseList c1, courseList c2){
    courses = c1;
    major = c2;
    majorName = "Unknown";
  }

  //full parametric constructor
  repository(courseList c1, courseList c2, std::string mName){
    courses = c1;
    major = c2;
    majorName = mName;
  }
  
  //copy constructor
  repository(const repository &r1){
    courses = r1.courses;
    major = r1.major;
    majorName = r1.majorName;
  }

  //Member functions

  //PRE:
  //POST: Returns the list of courses
  courseList getCourses(){return courses;}

  //PRE:
  //POST: Returns the list of major sections.
  courseList getMajorSections(){return major;}

  //PRE:
  //POST: Returns the name of the major.
  std::string getMajorName(){return majorName;}
  
  //PRE: c1 is a list of courses
  //POST: replaces the current courseList with c1.
  void setCourses(courseList c1){courses = c1;}

  //PRE: m1 is a list of major sections.
  //POST: replaces the current major sections with m1.
  void setMajorSections(courseList m1){major = m1;}

  //PRE: co is a course.
  //POST: Adds co to courses.
  void addCourse(course co){courses.addToBack(co);}

  //PRE: section is a section for a major.
  //POST: Adds section to major.
  void addMajorSection(course section){major.addToBack(section);}
  
  //PRE: x is an integer
  //POST: returns the xth course
  course getXCourse(int x){
    course c;
    try{c =  courses.getXCourse(x);}
    catch(Exception e){throw e;}
    return c;
  }
  
  //PRE: cId is a string
  //POST: Returns the course with id = cId.
  course getICourse(std::string cId){
    course c;
    try{c = courses.getICourse(cId);}
    catch(Exception e){throw e;}
    return c;
  }

  //PRE: x is an integer.
  //POST: returns the xth section of the major.
  course getXSection(int x){
    course c;
    try{c =  major.getXCourse(x);}
    catch(Exception e){throw e;}
    return c;
  }
  
  //PRE: cId is a string
  //POST: Returns the section with id = cId.
  course getISection(std::string cId){
    course c;
    try{c = courses.getICourse(cId);}
    catch(Exception e){throw e;}
    return c;
  }

  //PRE:
  //POST: returns the basic requirements for the major.
  std::string getBasicRequirements(){
    int x = major.getSize();
    std::string toReturn = "";
    for(int i = 0; i < x; i++){
      toReturn = major.getBasicReqs(major.getXId(i));
      toReturn += '\n';
    }
    return toReturn;
  }

  //PRE:
  //POST: returns the deep requirements for the major.
  std::string getDeepRequirements(){
    int x = major.getSize();
    courseList merged = courses;
    merged.addToFront(major);
    std::string toReturn = "";
    for(int i = 0; i < x; i++){
      toReturn = merged.getDeepReqs(merged.getXId(i));
      toReturn += '\n';
    }
    return toReturn;
  }
};
#endif
