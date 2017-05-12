/*
 * School.cpp
 *
 *  Created on: May 9, 2017
 *      Author: Ameer Badran
 */

#include <iostream>
#include <string>
#include "School.h"


School::School()
{
	this->studentsID=NULL;
	this->studentsPower=NULL;
	this->teams=NULL;
	this->numberStudents=0;
}

/*School::~School(){

}*/

void School::operator++(){
	this->numberStudents++;
}

void School::operator--(){
	this->numberStudents--;
}

/*void School::setMostPowerfulStudent(Student& newStudent)
{
	if(this->mostPowerfulStudent==NULL)
		this->mostPowerfulStudent=&newStudent;

	else {
		if((*(this->mostPowerfulStudent))<newStudent)
			this->mostPowerfulStudent=&newStudent;
	}
}*/


SchoolResult School::AddStudent(int studentID, int grade,int power)
{
	if(studentID<=0 || power<=0 || grade<0 || this==NULL)
		return SCHOOL_INVALID_INPUT;
	if(this->studentsID->find(studentID)!=NULL)
		return SCHOOL_FAILURE;

	try{
		Student* newStudent=new Student(studentID,grade,power);
		this->studentsID->insert(*newStudent,studentID);
		this->studentsPower->insert(*newStudent,power);
	}
	catch(std::exception& exception)
	{
		return SCHOOL_ALLOCATION_ERROR;
	}
	return SCHOOL_SUCCESS;
}


SchoolResult School::AddTeam(int teamID)
{
	if(teamID<=0 || this==NULL)
		return SCHOOL_INVALID_INPUT;
	if(this->teams->find(teamID)!=NULL)
		return SCHOOL_FAILURE;

	try{
		Team* newTeam=new Team(teamID);
		this->teams->insert(*newTeam,teamID);
	}
	catch(std::exception& exception)
	{
		return SCHOOL_ALLOCATION_ERROR;
	}
	return SCHOOL_SUCCESS;
}

SchoolResult School::GetMostPowerful(int teamID,int* studentID)
{
	if(teamID==0 || studentID==NULL || this==NULL)
		return SCHOOL_INVALID_INPUT;

	if(teamID>0 && this->teams->find(teamID)==NULL)
		return SCHOOL_FAILURE;

	if(teamID<0)
	{
		if(this->numberStudents==0)
			*studentID=-1;
		else
			*studentID=this->studentsID->getMostPowerful()->getStudentID();
		return SCHOOL_SUCCESS;
	}

	return SCHOOL_SUCCESS;
}
