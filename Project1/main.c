/*
	main.c
	Project 1
	Colton Mosier
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dicegame.h"

// Add all the includes for the required header files

/*
	Function: main
	--------------
	This is the driver program that bootstraps all the files for execution.

		argc: represents how many arguments are present on the command line
		argv: represents the arguments themselves

	Returns: int
*/
int main( int argc, char* argv[] ){

	// Initialize the srand() to start the random generator
	srand( (int) time( 0 ) );

	// Initialize the player-1 and player-2 points to 0
	int p1 = 0;
	int p2 = 0;

	// Initialize all other required variables
	int numOfRounds = 0;
	int roundCount = 1; // game will always begin at round 1
	int diceRoll = 0;
	int currentPlayer = 0;
	int points = 0;
	int roundType = 0;

	// Ask the user for the number of rounds to run the game
	printf( "Enter the number of rounds: " );
	scanf( "%d", &numOfRounds );


	// Call printPlayerPoints() function to print the initial player points which will be 0
	printPlayerPoints( points, points );
	printf( "\n" );


	// Set up the loop to go through all the rounds one at a time
	// while loops runs until the number of rounds has been met.
	while( roundCount != numOfRounds + 1 )
	{

		// Randomly chooses first player 
		if( roundCount == 1 )
		{
			currentPlayer = getRandomNumber( 1, 2 );
		}
		
		// Call the corresponding functions to get the information for this round - type, dice, points
		diceRoll = getRandomNumber( 1, 6 );
		roundType = getRoundType( );
		points = getRoundPoints( roundType );
			
		
		// Print round number
		printf( "ROUND %d\n", roundCount );
		printf( "--------\n" );

		// Print player of the round
		printf( "Player  : %d\n", currentPlayer );
			
	    // Call printRoundInfo() to print the round information
		printRoundInfo( roundType, diceRoll, points );


		// MAIN GAME LOGIC
		
		// 'if' and 'if else' statements used to add or subtract currennt round points to the current player 
		// saved in the variable "startingPlayer" based on Success or Failure of the round.
		if( currentPlayer == 1 && ( diceRoll % 2 != 0 ) ){			// If player 1 rolls an odd number Success, p1 gains predetermined points and
			p1 = p1 + points;									// Continues to play next round
			currentPlayer = 1;
		}else if( currentPlayer == 2 && (diceRoll % 2 == 0 ) ){ 	// If player 2 rolls an even number Success, p2 gains predetermined points and
			p2 = p2 + points;									// Continues to play next round
			currentPlayer = 2;
		}else if( currentPlayer == 1 && ( diceRoll % 2 == 0 ) ){ 	// If player 1 rolls and even number Failure, p1 loses predetermined points and
			p1 = p1 - points;									// Switch players for next round
			currentPlayer = 2;
		}else if( currentPlayer == 2 && ( diceRoll % 2 != 0 ) ){ 	// If player 2 rolls an odd number Failure, p2 loses predetermined points and
			p2 = p2 - points;									// Switch players for next round
			currentPlayer = 1;
		}

		// Call printPlayerPoints() to print the player information at the end of the round
		printPlayerPoints( p1, p2 );
		
		printf( "\n" );
		roundCount++;
	}
	printf( "\nGAME OVER!!\n" );

	// Compare the final points for player-1 and player-2
	// Print the winner as the one with higher points
	if( p1 > p2 ){
		printf( "P1 Won\n" );
	}else{
		printf( "P2 Won\n" );
	}

	return 0;
}
