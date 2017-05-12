/*
 * Student.h
 *
 *  Created on: May 9, 2017
 *      Author: Ameer Badran
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include "iostream"

typedef enum {
    STUDENT_SUCCESS = 0,
    STUDENT_FAILURE = -1,
    STUDENT_ALLOCATION_ERROR = -2,
    STUDENT_INVALID_INPUT = -3
}	StudentResult;

class Student{
	int id; //Student id
	int grade; //Student's grade
	int power; //Student's power
	int TeamID;

	public:
		Student(int StudentID,int Grade, int Power);

		//two add stuff to remove from team and other places
		~Student();

		int getStudentID();
		int getPower();

		//a function that returns true if the two IDs are equal, false otherwise
		bool operator==(const Student& student2) const;

		//returns true if the IDs are different
		bool operator!=(const Student& student1) const;

		//returns true if the ID of student1 is great, false otherwise.
		bool operator>=(const Student& student2) const;

		//returns true if the ID of student2 is greater, false otherwise.
		bool operator<=(const Student& student2) const;

		//returns true if the power of student1 is greater or is equal but his id is smaller
		bool operator>(const Student& student2) const;

		//returns true if the power of student2 is greater or is equal but his id is smaller
		bool operator<(const Student& student2) const;
};



#endif /* STUDENT_H_ */
