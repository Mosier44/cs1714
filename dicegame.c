/*
	dicegame.c
	Project 1
	Colton Mosier
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dicegame.h"


// character array used stricly for printing round type in the printRoundInfo function
					// ONLY GLOBAL VARIABLE 
const char TYPE[ 3 ] [ 8 ] = { "BONUS", "DOUBLE", "REGULAR" };
					

/*
	Function: getRandomNumber
	-------------------------
	This function generates a number between and including the integers that are passed in
		
		min: the smallest number for rand to select from
		max: the largest number for rand to select from
	Returns: Returns an integer value between and including min and max values
*/
int getRandomNumber(int min, int max)
{
	int randNumber;
	int values;
	values = max - min + 1;
	randNumber = rand()%values + min;
	return randNumber;
}
/*
	Function: getRoundType
	----------------------
	Decides what round type is being placed based on probability calculated with getRandomNumber(0,9) which chooses a 1 out of 10 numbers
	making the probability percentage easier to calculate. BONUS round type has a 20% chance, DOUBLE round type has a 30% chance, and 
	REGULAR round type has a 50% chance of being selected.
	
	Returns: Returns round type based on the enum ROUNDTYPE
*/
 
ROUNDTYPE getRoundType( )
{
	int probabilityNum;
	probabilityNum = getRandomNumber( 0, 9 );
	switch( probabilityNum ){
		case 0:
		case 1:
			return BONUS;
		case 2:
		case 3:
		case 4:
			return DOUBLE;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			return REGULAR;
	}
}
/*
	Function: getRoundPoints
	------------------------
	This function randomly generates points from 10-100 and changes them according to game rules.
	DOUBLE rounds doubles the points generated. REGULAR rounds do nothing to the points generated.
	BONUS rounds sets rounds strictly to 200.

		roundType: passes in the round type for the round so points can be change appropriately 
	
	Returns: Returns integer value of points 
*/
int getRoundPoints( ROUNDTYPE roundType )
{
	int points;
	points = 10 * getRandomNumber(1,10); 

	switch( roundType ){
		case DOUBLE:
			points = points * 2;
			return points;
		case REGULAR: 
			points = points;
			return points;
		case BONUS: 
			points = 200;
			return points;
	}
}

/*
	Function: printPlayerPoints
	---------------------------
	This function prints the players points based on the results of getRoundPoints function.

		p1: Is player 1's points
		p2: Is player 2's points

	Returns: Nothing
*/
void printPlayerPoints( int p1, int p2 )
{
	printf( "P1      : %d\n", p1 );
	printf( "P2      : %d\n", p2 );
}

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
void printRoundInfo( ROUNDTYPE t, int dice, int points ){
	char roundType[8];
	if( t == 0){
		strcpy( roundType, TYPE[ 0 ] );
	}else if ( t == 1 ){
		strcpy( roundType, TYPE[ 1 ] );
	}else if( t == 2){
		strcpy( roundType, TYPE[ 2 ] );
	}

	printf( "Type    : %s\n" , roundType );
	printf( "Dice    : %d\n" , dice );
	printf( "Points  : %d\n" , points );
}
