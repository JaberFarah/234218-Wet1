/*
 * Student.cpp
 *
 *  Created on: May 9, 2017
 *      Author: Ameer Badran
 */

#include <iostream>
#include "Student.h"

Student::Student(int StudentID,int Grade,int Power)
{
	this->id=StudentID;
	this->grade=Grade;
	this->power=power;
	this->TeamID=0;
}

Student::~Student()
{
	delete(this);
}

int Student::getStudentID()
{
	return this->id;
}

int Student::getPower()
{
	return this->power;
}

bool Student::operator==(const Student& student2) const{
	return this->id == student2.id;
}
bool Student::operator!=(const Student& student2) const{
	return !((*this)==student2);
}

bool Student::operator>=(const Student& student2) const{
	return (this->id > student2.id);
}
bool Student::operator<=(const Student& student2) const{
	return (this->id < student2.id);
}

bool Student::operator>(const Student& student2) const{
	if (this->power>student2.power)
		return true;
	else if(this->power==student2.power)
	{
		return ((this->id<student2.id));
	}
	return false;
}

bool Student::operator<(const Student& student2) const{
	if (this->power<student2.power)
		return true;
	else if(this->power==student2.power)
	{
		return ((this->id>student2.id));
	}
	return false;
}
