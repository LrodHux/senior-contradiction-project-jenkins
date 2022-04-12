%Holds the functions made for the test.pl document.

takingTaken(Student, Course, X):- ((hasTaken(Student, Course);
				    isTaking(Student, Course)),
				   X is 1);
				  X is 0.

canTakingTaken(Student, Course, X):- (canTake(Student, Course),
				      X is 1);
				     X is 0.



is-empty([]).

convert-list(X, X).

is-required(Course, [Course|_]).

is-required(Course, [_|Tail]):- is-required(Course, Tail).


impossible-requirement(Course1, Course2):- not(check-requirement(Course1, Course2),
					   check-requirement(Course2, Course1)).
%checks if any course in the list requires course 1
deep-check-requirement([], _):- false. %ASSERT: We cannot check a list with no elements.
deep-check-requirement([Head|Tail], Course1):- check-requirement(Head, Course1);
					       deep-check-requirement(Tail, Course1).
					       %ASSERT: If it is a requirement, return true
					       %        else, check the next course in the list.
%checks if Course1 requires Course2
check-requirement(Course1, Course2):- hardReqs(Course1, Reqs1),
				      (is-required(Course2, Reqs1);
				       deep-check-requirement(Reqs1, Course2)).

check-redundancy(_, []):-true. %ASSERT: No matter the course, if
                                %there are no courses left to check,
                                %it is false.
check-redundancy(Course, [Head|Tail]):- (not(check-requirement(Course, Head)),
					 not(check-requirement(Head, Course))),
					check-redundancy(Course, Tail).
%ASSERT: Checks if either course requires the other, if so, it is
%redundant, if not, check this course against the rest.

check-all-redundancy(_, []):-true. %ASSERT: No matter the course, if
                                    %there are no courses left to
                                    %check, it is false.
check-all-redundancy(Course, [Head|Tail]):- check-redundancy(Course, [Head|Tail]),
					    check-all-redundancy(Head, Tail).
%ASSERT: Check if this course is redundant. If not, check the next course in the list.

find-redundancy(Course):-allReqs(Course, Y),
			 %write(Course),
			 %write(,),
			 hardReqs(Course, X),
			 (is-empty(X);
			  convert-list(X, [Head|Tail]),
			  check-all-redundancy(Head, Tail)).


find-existence(Course):-allReqs(Course, X). %ASSERT: Checks if course exists.

check-all-non-existent-reqs(Course, []):- allReqs(Course, X),
					  (is-empty(X);
					   convert-list(X, [Head|Tail]),
					   check-all-non-existent-reqs(Head, Tail)).
					  

check-all-non-existent-reqs(Course, [Head|Tail]):- allReqs(Course, X),
						   (is-empty(X);
						    convert-list(X, [Head2|Tail2]),
						    check-all-non-existent-reqs(Head2, Tail2)),
						   check-all-non-existent-reqs(Head, Tail).
						   
					  
check-non-existent-reqs(Course):-allReqs(Course, X), %ASSERT: Checks if the course exists.
				 %write(Course),
				 %write(, ),
				 (is-empty(X);
				  convert-list(X, [Head|Tail]),
				  check-all-non-existent-reqs(Head, Tail)).

can-take-all(Student, Course, []):- student(Student), %ASSERT: Ensures the student exists
				    allReqs(Course, X), %ASSERT: Ensures the course exists
				    canTake(Student, Course),
				    (is-empty(X);
				     convert-list(X, [Head|Tail]),
				     can-take-all(Student, Head, Tail)).

can-take-all(Student, Course, [Head|Tail]):- allReqs(Course, X),
					     canTake(Student, Course),
					     (is-empty(X);
					      convert-list(X, [Head2|Tail2]),
					      can-take-all(Student, Head2, Tail2)),
					     can-take-all(Student, Head, Tail).

taken-pre-reqs(Student, Course):- student(Student), %ASSERT: Ensure the student exists.
				  allReqs(Course, X), %ASSERT: Ensure the course exists.
				  canTake(Student, Course), %ASSERT: Ensure the student can take the listed course.
				  (is-empty(X); %ASSERT: If the course has no requirements, the student can take it.
				   convert-list(X, [Head|Tail]),
				   can-take-all(Student, Head, Tail)).

list-size([], 0).

list-size([Head|Tail], X):- list-size(Tail, Y),
			    X is 1+Y.

check-soft-valid(X, List):- list-size(List, Y),
			    Y > X,
			    X > 0.

valid-soft-reqs(Course):-softReqs(Course, X),
			 (is-empty(X);
			  convert-list(X, [Head|Tail]),
			  check-soft-valid(Head, Tail)).

self-requirement(Course):- allReqs(Course, X),
			   not(check-requirement(Course, Course)).

%student(steven).



%canTake testcases:

%Test 1) Student qualifies for no requirements:
%Code to run: canTake(steven, any-course).
%No code needed.
%Should return false for any course input.

%Test 2) Student meets hard requirement, but not soft.
%Code to run: canTake(steven, cpsc-600).
%hasTaken(steven, cpsc-120). %To see if hasTaken works as expected in the hard check.
%isTaking(steven, math-121). %To see if isTaking works as expected in the hard check.
%Should return false since no soft requirements are met.

%Test 3) Student meets soft requirements, but not hard.
%Code to run: canTake(steven, cpsc-600).
%hasTaken(steven, stat-210). %To see if hasTaken works as expected in the soft check.
%isTaking(steven, stat-220). %To see if isTaking works as expected in the soft check.
%Should return false since no hard requirements are met.

%Test 4) Student meets both hard and soft requirements for a course.
%Code to run: canTake(steven, cpsc-600).
%hasTaken(steven, stat-210). %To see if hasTaken works as expected in the soft check.
%isTaking(steven, stat-220). %To see if isTaking works as expected in the soft check.
%hasTaken(steven, cpsc-120). %To see if hasTaken works as expected in the hard check.
%isTaking(steven, math-121). %To see if isTaking works as expected in the hard check.
%Should return true since all requirements are met. When traceing, expect Y=2.

%Test 5) Student meets only one hard requirement for a course with only hard requirements.
%Code to run: canTake(steven, cpsc-462).
%hasTaken(steven, cpsc-250).
%Should return false since only one requirement is met.

%Test 6) Student meets all hard requirements for a course with only hard requirements.
%Code to run: canTake(steven, cpsc-462).
%hasTaken(steven, cpsc-250).
%isTaking(steven, math-131).

%Test 7) Student meets some soft requirements for a course with only soft requirements.
%Code to run: canTake(steven, cpsc-610).
%hasTaken(steven, math-121).
%Should return false since at least 2 requirements are nessecary. When traceing, expect Y=1.

%Test 8) Student meets min soft requirements for a course with only soft requirements.
%Code to run: canTake(steven, cpsc-610).
%hasTaken(steven, math-121).
%isTaking(steven, stat-210).
%Should return true. When tracing, expect Y=2.

%is-required / check-requirement / deep-check-requirement test cases

%Test 1) Course 1 requires Course 2
%Code to run: check-requirement(cpsc-170, cpsc-120).
%Expect to return true.
%THIS WORKS

%Test 2) Course 1 doesn't require Course 2
%Code to run: check-requirement(cpsc-120, cpsc-120).
%Expect to return false.
%THIS WORKS

%Test 3) Course 1 requires a course which requires Course 2.
%Code to run: check-requirement(cpsc-250, cpsc-120).
%Expect to return true.
%THIS WORKS

%Test 4) Course 1 requires no courses which require Course 2.
%Code to run: check-requirement(cpsc-250, cpsc-450).
%Expect to return false.
%THIS WORKS

%ALL TESTCASES VALIDATED

%impossible-requirement test cases

%Case 1) There is an impossible requirement
%Code to run: impossible-requirement(cpsc-100, math-100).
%Expect to return true.
%THIS WORKS

%Case 2) There is no impossible requirement
%Code to run: impossible-requirement(cpsc-170, cpsc-120).
%Expect to return true.
%THIS WORKS

%Case 3) There is a nested impossible requirement.
%Code to run: impossible requirement(cpsc-100, cpsc-000).
%Expect to return true.
%THIS WORKS

%Case 4) There are no nested impossible requirements.
%Code to run: (cpsc-250, cpsc-170).
%Expect to return false.
%THIS WORKS

%ALL TESTCASES VALIDATED

%find-existence testcases.
%Case 1) Try to find the requirements of a course which doesn't exist.
%Code to run: allReqs(cs-1, X).
%Expect to return false.
%THIS WORKS

%Case 2) Try to see if an existant course exists.
%Code to run: find-existence(cpsc-250).
%Expect to return true.
%THIS WORKS

%Case 3) Try to see if a non-existant course exists.
%Code to run: find-existence(cpsc-900).
%Expect to return false.
%THIS WORKS

%ALL TESTCASES VALIDATED

%check-non-existent-reqs testcases.
%Case 1) A course has only existing requirements.
%Code to run: check-non-existent-reqs(cpsc-170).
%Expect to return true since there are only existing requirements.
%THIS WORKS

%Case 2) A course has a non-existant requirement.
%Code to run: check-non-existent-reqs(cpsc-700).
%Expect to return false.
%THIS WORKS

%Case 3) A course has no requirements.
%Code to run: check-non-existent-reqs(cpsc-120).
%Expect to return true since it is vacuously true.
%THIS WORKS

%Case 4) A course has a nested non-existent requirement.
%Code to run: check-non-existent-reqs(cpsc-710).
%Expect to return false.
%THIS WORKS

%Case 5) A course doesn't exist.
%Code to run: check-non-existent-reqs(cpsc-900).
%Expect to return false.
%THIS WORKS

%ALL TESTCASES VALIDATED

%taken-pre-reqs testcases.
%Case 1) Student has taken no required courses for a course.
%Test vars:
%NONE
%Code to run: taken-pre-reqs(steven, cpsc-170).
%Expect to return false.
%THIS WORKS

%Case 2) Student has taken required courses for a course, but not the course required.
%Test vars:
%hasTaken(steven, cpsc-170).
%Code to run: taken-pre-reqs(steven, cpsc-250).
%Expect to return false.
%THIS WORKS

%Case 3) Student has taken required courses for a course, and required courses for those courses.
%hasTaken(steven, cpsc-120).
%hasTaken(steven, cpsc-170).
%Code to run: taken-pre-reqs(steven, cpsc-250).
%Expect to return true.
%THIS WORKS

%Case 4) The student exists and is trying to take a course which has no pre-reqs
%Test vars:
%NONE
%Code to run: taken-pre-reqs(steven, cpsc-120).
%Expect to return true.
%THIS WORKS

%ALL TESTCASES VALIDATED

%valid-soft-reqs testvases.
%Case 1) A course has 3 courses listed and requires 3 courses.
%Code to run: valid-soft-reqs(cpsc-610).
%Expect to return false since the number of courses matches the number required.

%Case 2) A course has 3 courses listed and requires 4 courses.
%Code to run: valid-soft-reqs(math-610)
%Expect to return false since the number of courses is lower than the number required.

%Case 3) A course has 2 courses listed and requires 0 courses.
%Code to run: valid-soft-reqs(bio-100).
%Expect to return false since there are technically no requirements.

%Case 4) A course has 2 courses listed and requires 1 course.
%Code to run: valid-soft-reqs(cpsc-170).
%Expect to return true.

%Case 5) A course has no soft requirements.
%Code to run: valid-soft-reqs(cpsc-250).
%Expect to return true.
