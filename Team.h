/*
 * Team.h
 *
 *  Created on: May 9, 2017
 *      Author: Ameer Badran
 */

#ifndef TEAM_H_
#define TEAM_H_

#include <iostream>
#include "Student.h"
#include "AVL-A.h"

typedef enum {
    TEAM_SUCCESS = 0,
    TEAM_FAILURE = -1,
    TEAM_ALLOCATION_ERROR = -2,
    TEAM_INVALID_INPUT = -3
}	TeamResult;


class Team{
private:
	int teamID; //Team ID.
	int MostPowerfullStudent; //The ID of the the student that holds the highest power.
	int NumOfStudents; //Number of students in the team.
	avlTree<Student,int>* studentPowerTree; //AVL tree sorted by power.

public:
	Team(int teamID);
	~Team();

	int getPower();

	/*Checks if This team ID is equal to team ID.
	  Parameters : this team and team, the operator compares between their IDs.
	  RETURN true if the two IDs are equal , false otherwise.
	 */
	bool operator==(const Team& team) const;

	/*Checks if This team ID is equal to team ID.
	  Parameters : this team and team, the operator compares between their IDs.
	  RETURN true if the two IDs are equal , false otherwise.
	 */
	bool operator!=(const Team& team) const;

	/*Checks if This team ID is bigger from team ID.
	  Parameters : this team and team, the operator compares between their IDs.
	  RETURN true if this team's ID is bigger than the other team ID, false otherwise.
	 */
	bool operator>(const Team& team) const;

	/*Checks if This team ID is bigger from team ID.
	  Parameters : this team and team, the operator compares between their IDs.
	  RETURN true if this team's ID is bigger than the other team ID, false otherwise.
	 */
	bool operator<(const Team& team) const;

	int operator-(const Team& team) const;
};


#endif /* TEAM_H_ */
