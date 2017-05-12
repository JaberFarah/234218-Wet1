/*
 * DataStruct.h
 *
 *  Created on: May 8, 2017
 *      Author: Ameer Badran
 */

#ifndef SCHOOL_H_
#define SCHOOL_H_

#include <iostream>
#include "AVL-A.H"
#include "Team.h"


typedef enum {
    SCHOOL_SUCCESS = 0,
    SCHOOL_FAILURE = -1,
    SCHOOL_ALLOCATION_ERROR = -2,
    SCHOOL_INVALID_INPUT = -3
}	SchoolResult;


class School{
	avlTree<Student,int>* studentsID;
	avlTree<Student,int>* studentsPower;
	avlTree<Team,int>* teams;
	int numberStudents;

	/*Checks if the new student is more powerful than the current most powerful student.
	*The new student is declared most powerful only if his power is higher than the power of the current
	*most powerful student, or if their powers are equal but the new student has a smaller ID number.
	*If the new student is more powerful then he is made the most powerful student, else nothing done.
	*/
	void setMostPowerfulStudent(Student& newStudent);

public:
	School();

	 //Increases the number of student by 1.
	void operator++();

	//Decreases the number of student by 1.
	void operator--();



	/*Adds a new student to the school.
	 * @PARAMETERS : studentID - The ID of the new student.
	 * 				grade - The grade of the new student.
	 * 				power - the power of the new student.
	 * 				The team of the new student is set to be NULL.
	 * @RETURN :	SCHOOL_INVALID_INPUT - in case of studentID<=0 or power<=0 or grade<0
	 * 				SCHOOL_FAILURE - in case a student with this ID is already in school
	 * 				SCHOOL_ALLOCATION_ERROR - in case of allocation error happened during the process
	 * 				SCHOOL_SUCCESS - otherwise
	 */
	SchoolResult AddStudent(int studentID, int grade,int power);


	/*Adds a new team to the school.
	* @PARAMETERS :  teamID - The ID of the new team.
	* 				The team of the new student is set to be NULL.
	* @RETURN :		SCHOOL_INVALID_INPUT - in case of teamID<=0
	* 				SCHOOL_FAILURE - in case a team with this ID is already in school
	* 				SCHOOL_ALLOCATION_ERROR - in case of allocation error happened during the process
	* 				SCHOOL_SUCCESS - otherwise
	*/
	SchoolResult AddTeam(int teamID);

	/*Gets the most Powerful student in a team.
	* @PARAMETERS : teamID - The ID of the team to search in.
	* 				studentID - parameter that holds the ID of the most powerful student.
	* @RETURN :		SCHOOL_INVALID_INPUT - in case of teamID==0 or studentID==NULL or this==NULL
	* 				SCHOOL_FAILURE - in case teamID>0 and there is no team with such ID.
	* 				SCHOOL_SUCCESS - otherwise
	* @RETURN VALUE IN studentID : -in case teamID<0, the ID of the most powerful student in the school
	* 							   -
	*/
	SchoolResult GetMostPowerful(int teamID,int* studentID);
};

#endif /* SCHOOL_H_ */
