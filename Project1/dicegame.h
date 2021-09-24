/*
	dicegame.h
	Project 1
	Colton Mosier
*/
#ifndef DICEGAME_H_
#define DICEGAME_H_


// defining enum ROUNDTYPE
typedef enum
{	BONUS, 
	DOUBLE, 
	REGULAR
}ROUNDTYPE;

/*
	Function: getRandomNumber
	-------------------------
	This function generates a number between and including the integers that are passed in
					
		min: the smallest number for rand to select from
		max: the largest number for rand to select from
	Returns: Returns an integer value between and including min and max values
*/
int getRandomNumber( int min, int max );

/*
	Function: getRoundType
	----------------------
	Decides what round type is being placed based on probability calculated with getRandomNumber(0,9) which chooses a 1 out of 10 numbers
	making the probability percentage easier to calculate. BONUS round type has a 20% chance, DOUBLE round type has a 30% chance, and 
	REGULAR round type has a 50% chance of being selected.
						
	Returns: Returns round type based on the enum ROUNDTYPE
*/
ROUNDTYPE getRoundType( );

/*
	Function: getRoundPoints
	------------------------
	This function randomly generates points from 10-100 and changes them according to game rules.
	DOUBLE rounds doubles the points generated. REGULAR rounds do nothing to the points generated.
	BONUS rounds sets rounds strictly to 200.

		roundType: passes in the round type for the round so points can be change appropriately 
								
	Returns: Returns integer value of points 
*/
int getRoundPoints( ROUNDTYPE roundType );

/*
	Function: printPlayerPoints
	---------------------------
	This function prints the players points based on the results of getRoundPoints function.

		p1: Is player 1's points
		p2: Is player 2's points

	Returns: Nothing
*/
void printPlayerPoints( int p1, int p2 );

/*
	Function: printRoundInfo
	------------------------
	This functions job is to print the information of the round type, dice value rolled, and points.
	The function also changes the value of ROUNDTYPE t to a character array for easier printing.

		t: Signifies what type of round is being played
		dice: Passes in the value of the rolled dice for the round
		points: Passes in the value of points that will be either gained or lost based on round type

	Returns: Nothing
*/
void printRoundInfo( ROUNDTYPE t, int dice, int points );

#endif
