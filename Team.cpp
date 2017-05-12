/*
 * Team.cpp
 *
 *  Created on: May 9, 2017
 *      Author: Ameer Badran
 */


#include <iostream>
#include "Team.h"
#include <string>


Team::Team(int teamID)
{
	this->teamID=teamID;
	MostPowerfullStudent=-1;
	NumOfStudents=0;
	studentPowerTree=NULL;
}


Team::~Team()
{

}

int Team::getPower()
{
	return 0;
}

bool Team::operator==(const Team& team) const
{
	return (this->teamID==team.teamID);
}

bool Team::operator!=(const Team& team) const
{
	return (!((*this)==team));
}

bool Team::operator>(const Team& team) const
{
	return (this->teamID > team.teamID);
}

bool Team::operator<(const Team& team) const
{
	return (this->teamID < team.teamID);
}
