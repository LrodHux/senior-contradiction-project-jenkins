#include <string>
#include <iostream>
#include <fstream>
#include "linkList.h"
#include "courseClass.h"
#include "courseList.h"
#include "exceptions.h"
#include "student.h"
#include "repository.h"
#include "helperFunctions.cc"
using namespace std;
//PRE: s is a string.
//POST: returns true IFF the last two characters of a string is - followed
//any letter.
bool largerPreReq(string s){
  int size = s.length();
  bool isLargePre = false;
  if(s[size-2] == '-'){
    if(s[size-1] >= 'a' and s[size-1] <= 'z'){
      isLargePre = true;
    }
  }
  return isLargePre;
}
//PRE: file is an opened fstream file
//     c is a character
//POST: Returns the name of course in file.
string buildName(fstream &file, char c){
  string name;
  while(c != ','){
    name += c;
    file.get(c);
  }
  //ASSERT: In a formatted file, the first thing to follow a name is a
  //comma, so it needs to end as soon as a comma appears.
  return name;
}

//PRE: file is an opened fstream file
//     name is the name of the course
//     id is the id of the course
//     hReqs is the hard requirements of the course
//     c is a character
//POST: Returns the course with soft requirements.
course buildSoftReqs(fstream &file, string name, string id,
		     linkList hReqs, char c){
  linkList softReqs;
  string softRequire;
  file.get(c); //gets it off previous identifier character (, ;
		//etc...)
  bool done = false;
  while(!done){
    if(c == ' '){
      file.get(c);
    }
    //ASSERT: Ignores spaces
    else if(c == ';'){
      softReqs.addToBack(softRequire);
      softRequire = "";
      done = true;
      file.get(c);
    }
    //ASSERT: This is the end of the soft requirements. And the
    //current string to the list and set done to true.
    else if(c != ','){
      softRequire += c;
      file.get(c);
    }
    //ASSERT: Add the next character to the string.
    else{
      softReqs.addToBack(softRequire);
      softRequire = "";
      file.get(c);
    }
    //ASSERT: Add the current string to the list. Reset the string.
  }
  string softNeeded;
  done = false;
  while(!done){
    if(c == ' '){
      file.get(c);
    }
    //ASSERT: Ignores spaces
    else if(c == '\n' or c == '\0'){
      done = true;
    }
    //ASSERT: If the end of line or end of file character is found,
    //the number is finished.
    else{
      softNeeded += c;
      file.get(c);
    }
    //ASSERT: The next digit is added to the number.
  }
  int needed;
  needed = stoi(softNeeded);
  course t(name, id, hReqs, softReqs, needed);
  return t;
}

//PRE: file is an opened fstream file
//     name is the name of the course
//     id is the id of the course
//     c is a character
//POST: Returns the course with hard requirements
course buildHardReqs(fstream &file, string name, string id, char c){
  linkList hardReqs;
  string hardRequire;
  file.get(c); //gets it off previous identifier character (, ;
		//etc...)
  bool reqsDone = false;
  bool fileDone = false;
  while(reqsDone == false and fileDone == false){
    if(c == ' '){
      file.get(c);
    }
    //ASSERT: Ignores spaces
    else if(c == '\n' or file.eof()){
      hardReqs.addToBack(hardRequire);
      hardRequire = "";
      fileDone = true;
    }
    //ASSERT: If either of these is encoutered, there are no more
    //requirements at all.
    else if(c == ';'){
      hardReqs.addToBack(hardRequire);
      hardRequire = "";
      reqsDone = true;
    }
    //ASSERT: If this is encountered, there are soft requirements to
    //be found.
    else if(c != ','){
      hardRequire += c;
      file.get(c);
    }
    //ASSERT: While there isn't a comma, the string is still being
    //built.
    else{
      hardReqs.addToBack(hardRequire);
      hardRequire = "";
      file.get(c);
    }
    //ASSERT: A comma was encountered, add current string to the list
    //and reset the string. Get the next character in file.
  }
  course t;
  if(fileDone){
    course t1(name, id, hardReqs);
    t = t1;
  }
  //ASSERT: The course only has hard requirements.
  else{
    //cout << "There are soft requirements in addition to the hard." << endl;
    t = buildSoftReqs(file, name, id, hardReqs, c);
  }
  return t;
}

//PRE: file is an opened fstream file
//     name is the name of the course
//     c is a character
//POST: Returns the course with the name: name.
course buildId(fstream &file, string name, char c){
  string id;
  while(c != ',' and c != ';' and c != '\n' and file.eof() == false){
    if(c == ' '){
      file.get(c);
    }
    //ASSERT: This ignores spaces.
    else{
      id += c;
      file.get(c);
    }
    //ASSERT: Adds the next character to the id string.
  }
  file.get(c);
  //cout << "The id of the course is " << id << endl;
  string credits;
  while(c != ',' and c != ';' and c != '\n' and file.eof() == false){
    if(c == ' '){
      file.get(c);
    }
    //ASSERT: This ignores spaces.
    else{
      credits += c;
      file.get(c);
    }
    //ASSERT: Adds the next character to the id string.
  }
  //cout << "Size was: " << credits.length() << endl;
  float creds = stof(credits);
  course t;
  //ASSERT: Creates the id string
  if(c == ','){
    //cout << "Hard Requirements found "<< endl;
    t = buildHardReqs(file, name, id, c);
    t.setCredits(creds);
  }
  //ASSERT: There are hard requirements
  else if(c == ';'){
    linkList empty;
    t = buildSoftReqs(file, name, id, empty, c);
    t.setCredits(creds);
  }
  //ASSERT: There are only soft requirements
  else{
    course t1(name, id, creds);
    t = t1;
  }
  //ASSERT: There are no requirements.
  return t;
}

//PRE: file is an opened fstream file which holds the course
//information.
//POST: Builds a course based on the current line.
course makeCourse(fstream &file){
  char c;
  file.get(c);
  if(file.eof()){
    Exception e("final course already added");
    throw e;
  }
  string courseName = buildName(file, c);
  //cout << "The Course Name is: " << courseName << endl;
  file.get(c);
  if(file.eof()){
    Exception e("file is empty");
    throw e;
  }
  course t = buildId(file, courseName, c);
  //ASSERT: This ensures that the next time this is called,
  //file->get(c) will get the first element of the next course.
  return t;
}

//PRE: file is an opened fstream file which holds the course
//information.
//POST: Returns a courseList of every course in file.
courseList buildCourses(fstream &file){
  courseList courses;
  bool done = false;
  if(file.peek() == '\0'){
    done = true;
    //cout << "It Worked" << endl;
  }
  while(!done){
    if(file.eof()){
      done = true;
    }
    //ASSERT: If the end of the file has been reached, end the loop.
    else{
      try{
	//cout << "Trying again." << endl;
	courses.addToBack(makeCourse(file));
	//cout << courses.getXId(courses.getSize()-1) << endl;
      }
      catch(Exception e){
	//cout << "reached final course" << endl;
      }
    }
    //ASSERT: If the end of the file has not been reached, add the
    //next course.
  }
  //ASSERT: Until the end of the file is reached, add courses to the
  //course list based on the contents of the file.
  return courses;
}

//PRE:s is a string
//POST: makes the string lowercase.
string lowercase(string s){
  int x = s.size();
  int y = 'A' - 'a';
  //cout << "Is this negative? " << y << endl;
  char c;
  string toReturn = "";
  for(int i = 0; i < x; i++){
    c = s[i];
    if(c >= 'A' and c <= 'Z'){
      //cout << "Got here" << endl;
      c = c - y;
      //cout << "c should be: " << c << endl;
    }
    //ASSERT: If s[i] is a capital letter, convert it to it's
    //lowercase counterpart.
    toReturn += c;
  }
  return toReturn;
}

//PRE: l1 is a linkList object of soft requirements.
//POST: returns the prolog translation of soft requirements.
string buildSoftFacts(linkList l1){
  string toReturn = "";
  string name;
  int x = 0;
  while(l1.getSize() > 0){
    name = l1.getXId(0);
    name = lowercase(name);
    if(largerPreReq(name)){
      toReturn += "canTakingTaken(Student, ";
      toReturn += name;
      toReturn += ", X";
    }
    //ASSERT: Creates a complex requirement if the course has -A,
    //-B... -Z at the end.
    else{
      toReturn += "takingTaken(Student, ";
      toReturn += name;
      toReturn += ", X";
    }
    //ASSERT: Creates a normal soft requirement for the course.
    toReturn += to_string(x);
    x++;
    toReturn += "),";
    toReturn += '\n';
    l1.removeNode(0);
  }
  //ASSERT: Builds a prolog statement for each soft requirement listed
  //for the course.
  toReturn += "Y is ";
  for(int i = 0; i < x; i++){
    toReturn += "X";
    toReturn += to_string(i);
    if(i+1 != x){
      toReturn += "+";
    }
    //ASSERT: If this is not the last X, and + to the string.
  }
  //ASSERT: Creates the mechanism to check if a student has taken the
  //required number of soft requirements.
  toReturn += ",";
  toReturn += '\n';
  return toReturn;
}

//PRE: l1 is a linkList object of hard requirements.
//     l2 is a linkList object which may have soft requirements.
//POST: Returns the prolog translation of hard requirements.
string buildHardFacts(linkList l1, linkList l2){
  string toReturn = "";
  string name;
  while(l1.getSize() > 0){
    name = l1.getXId(0);
    name = lowercase(name);
    if(largerPreReq(name)){
      toReturn += "canTake(Student, ";
      toReturn += name;
      toReturn += ")";
    }
    //ASSERT: Creates a complex requirement if the course has -A,
    //-B... -Z at the end.
    else{
      toReturn += "(hasTaken(Student, ";
      toReturn += name;
      toReturn += "); isTaking(Student, ";
      toReturn += name;
      toReturn += "))";
    }
    //ASSERT: Creates a normal hard requirment for regular courses.
    if(l1.getSize() != 1){
      toReturn += ",";
      toReturn += '\n';
    }
    //ASSERT: If this is not the last element of l1, add a comma and
    //end of line character.
    l1.removeNode(0);
  }
  //ASSERT: Builds a prolog statement for each hard requirement listed
  //for the course.
  if(l2.getSize() > 0){
    toReturn += ",";
    toReturn += '\n';
    toReturn += buildSoftFacts(l2);
  }
  //ASSERT: Builds a definition with soft requirments if they exist.
  else{
    toReturn += ".";
  }
  //ASSERT: Finishes the statement since there are no soft
  //requirements to consider.
  return toReturn;
}

//PRE: l1 is a link list.
//     l2 is a link list.
//POST: Returns a string of every id in both l1 and l2.
string getAllReqs(linkList l1, linkList l2){
  string toReturn = "";
  string name;
  while(l1.getSize() > 0){
    name = l1.getXId(0);
    name = lowercase(name);
    toReturn += name;
    l1.removeNode(0);
    if(l1.getSize() != 0 or l2.getSize() != 0){
      toReturn += ", ";
    }
    //ASSERT: If there are further requirements, add a comma.
  }
  //ASSERT: For each node in l1, add their id's to toReturn.
  while(l2.getSize() > 0){
    name = l2.getXId(0); 
    name = lowercase(name);
    toReturn += name;
    l2.removeNode(0);
    if(l2.getSize() != 0){
      toReturn += ", ";
    }
    //ASSERT: If there are further requirements, add a comma.
  }
  //ASSERT: for each node in l2, add their id's to toReturn.
  toReturn += "]).";
  toReturn += '\n';
  return toReturn;
}

//PRE: c is a course.
//POST: Returns a prolog fact regarding what one would need to take in
//order to take the course c.
string getFact(course c){
  string name = c.getId();
  name = lowercase(name);
  linkList hardReqs = c.getHardReqs();
  linkList softReqs = c.getSoftReqs();
  int softNeeded = c.getSoftNeeded();
  string courseName = "courseName(";
  courseName += name;
  courseName += ").";
  courseName += '\n';
  string toReturn = "canTake(Student, ";
  string addReturn = "allReqs(";
  string addHard = "hardReqs(";
  string addSoft = "softReqs(";
  string addCreds = "credits(";
  addCreds += name;
  addCreds += ", ";
  addCreds += to_string(c.getCredits());
  addCreds += ").";
  addCreds += "\n";
  linkList empty;
  toReturn += name;
  addReturn += name;
  addSoft += name;
  addHard += name;
  toReturn += "):- student(Student)";
  addReturn += ", [";
  addSoft += ", [";
  addHard += ", [";
  if(hardReqs.getSize() == 0 and softReqs.getSize() == 0){
    toReturn += ".";
    addReturn += "]).";
    addReturn += '\n';
    addSoft += "]).";
    addSoft += '\n';
    addHard += "]).";
    addHard += '\n';
  }
  //ASSERT: Closes all statements since there are no requirements for
  //the course to be added.
  else if(hardReqs.getSize() > 0){
    toReturn += ",";
    toReturn += '\n';
    toReturn += buildHardFacts(hardReqs, softReqs);
    addReturn += getAllReqs(hardReqs, softReqs);
    addHard += getAllReqs(empty, hardReqs);
    if(softReqs.getSize() > 0){
      addSoft += to_string(softNeeded);
      addSoft += ", ";
      addSoft += getAllReqs(empty, softReqs);
      toReturn += "Y >= ";
      toReturn += to_string(softNeeded);
      toReturn += ".";
    }
    //ASSERT: Builds facts for softReqs if there are any soft requirements.
    else{
      addSoft += "]).";
      addSoft += '\n';
    }
    //ASSERT: Closes the softReqs fact since there are not any soft
    //requirements.
  }
  //ASSERT: Builds hardReqs, allReqs, and softReqs if any soft
  //requirements exist.
  else{
    addHard += "]).";
    addHard += '\n';
    toReturn += ",";
    toReturn += '\n';
    toReturn += buildSoftFacts(softReqs);
    toReturn += "Y >= ";
    toReturn += to_string(softNeeded);
    toReturn += ".";
    addReturn += getAllReqs(hardReqs, softReqs);
    addSoft += to_string(softNeeded);
    addSoft += ", ";
    addSoft += getAllReqs(empty, softReqs);
  }
  //ASSERT: Closes hardReqs fact since there are no hard
  //requirements. Builds softReqs & allReqs based on existing soft
  //requirements.
  //cout << addReturn << endl;
  addReturn += courseName;
  addReturn += addSoft;
  addReturn += addHard;
  addReturn += addCreds;
  addReturn += toReturn;
  toReturn = addReturn;
  return toReturn;
}

//PRE: list is a courseList object.
//POST: Outputs a .pl file with the facts created from each course in
//the courseList object.
void makePrologFile(courseList list){
  fstream prologFile;  
  prologFile.open("test.pl");
  fstream functionFile;
  functionFile.open("test2.pl");
  string s = "";
  s += "student(s).";
  s += '\n';
  s += "hasTaken(s, c).";
  s += '\n';
  s += "isTaking(s, c).";
  s += '\n';
  //ASSERT: This initializes the facts.
  prologFile << s;
  while(list.getSize() > 0){
    s = getFact(list.getXCourse(0));
    list.removeNode(0);
    prologFile << s;
    prologFile << '\n';
  }
  //ASSERT: For every course in list, create statements for it and add
  //it to the file.
  char c;
  string functions;
  while(!functionFile.eof()){
    functionFile.get(c);
    functions += c;
  }
  //ASSERT: Creates a string containing the contents of the function file.
  prologFile << functions; //ASSERT: Appends the function file to the
			   //end of the statement file.
  prologFile.close();
}

int main(){
  remove("test.pl"); //Deletes previous iteration of test.pl.
  ofstream {"test.pl"};
  fstream courseFile;
  courseFile.open("finalCourseDoc.txt");
  courseList courses = buildCourses(courseFile);
  makePrologFile(courses);
}
