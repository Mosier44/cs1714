/*
	champion.h
	Project 3
	Colton Mosier

    This file holds the function prototypes as well as the definition of struct Champion and enum ChampionRole.
*/

#ifndef CHAMPION_H_
#define CHAMPION_H_

typedef enum
{
    MAGE,
    FIGHTER,
    SUPPORT,
    TANK
} ChampionRole;

typedef struct Champion
{
    ChampionRole role;
    int level;
    struct Champion* next;
} Champion;

/*
	Function: createChampion
	-------------------------
	This function is used to create new champion nodes by assigning values to the variables in the Champion struct.
		
	Returns: The newly created champion node.
*/
Champion* createChampion( );

/*
	Function: addChampion
	-------------------------
	This function is used to add new champion nodes in descending order in a linked list

        head: the head of the linked list to be edited
        c: the new node that is to be added to the head linked list
		
	Returns: The recently altered linked list.
*/
Champion* addChampion( Champion* head, Champion* c );

/*
	Function: buildChampionList
	-------------------------
	This function is used to add new champion nodes in descending order in a linked list

        n: the number of champions per player that is given by the user as a command line argument.
		
	Returns: The built linked list in correct order.
*/
Champion* buildChampionList( int n );

/*
	Function: printChampionList
	-------------------------
	This function is used to print out each players linked list in order

        head: the head of the linked list to be printed
		
	Returns: Void
*/
void printChampionList( Champion* head );

/*
	Function: removeChampion
	-------------------------
	This function is used to remove champion nodes from the beginning of the players linked list

        head: the head of the linked list to be edited
		
	Returns: The recently altered linked list.
*/
Champion* removeChampion( Champion* head );

/*
	Function: destroyChampionList
	-------------------------
	This function is used to remove each champion from the link list that is passed in.

        head: the head of the linked list to be DESTROYED.
		
	Returns: NULL
*/
Champion* destroyChampionList( Champion* head );

/*
	Function: getRandomNumber
	-------------------------
	This function generates a number between and including the integers that are passed in ****THIS IS JUST A HELPER FUNCTION****
		
		min: the smallest number for rand to select from
		max: the largest number for rand to select from

	Returns: Returns an integer value between and including min and max values
*/
int getRandomNumber(int min, int max);

#endif