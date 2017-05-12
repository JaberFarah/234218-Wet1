/*
 * library1.cpp
 *
 *  Created on: May 9, 2017
 *      Author: Ameer Badran
 */

#include "library1.h"
#include "School.h"

template<class DS_Type>

DS_Type* Init(){
	School* DS = new School();
	return DS;
}


template<class DS_Type>
StatusType AddStudent(DS_Type* DS,int StudentID,int Grade,int Power){
	return((School*)DS)->AddStudent(StudentID,Grade,Power);
}

template<class DS_Type>
StatusType AddTeam(DS_Type* DS,int TeamID){
	return((School*)DS)->AddTeam(TeamID);
}

template<class DS_Type>
StatusType GetMostPowerful(void *DS, int TeamID, int *StudentID){
	return ((School*)DS)->GetMostPowerful(TeamID,StudentID);
}
