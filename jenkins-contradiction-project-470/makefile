test: node.o
	g++ node.o linkList.o courseList.o -o test
driver: driver.o
	g++ driver.o linkList.o courseList.o -o driver
linkList.o: linkList.cc linkList.h
	g++ -c linkList.cc
courseList.o: courseList.cc courseList.h courseClass.h courseNode.h
	g++ -c courseList.cc
node.o: node.cc linkList.o node.h courseClass.h courseList.o
	g++ -c node.cc
driver.o: driver.cc linkList.o courseClass.h courseList.o student.h repository.h helperFunctions.cc
	g++ -c driver.cc
