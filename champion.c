/*
	champion.c
	Project 3
	Colton Mosier

    This file holds the functions themselves that the main.c driver file will call on to preform an action.
*/

#include "champion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


/*
	Function: createChampion
	-------------------------
	This function is used to create new champion nodes by assigning values to the variables in the Champion struct.
		
	Returns: The newly created champion node.
*/
Champion* createChampion( ){
    int randomNum;
    Champion* newChamp = ( Champion* ) malloc( sizeof( Champion ) );

    randomNum = getRandomNumber( 1, 4 );

    switch ( randomNum )
    {
        case 1:
            newChamp->role = MAGE;
            newChamp->level = getRandomNumber( 5, 8 );
            break;

        case 2:
            newChamp->role = FIGHTER;
            newChamp->level = getRandomNumber( 1, 4 );
            break;

        case 3:
            newChamp->role = SUPPORT;
            newChamp->level = getRandomNumber( 3, 6 );
            break;

        case 4:
            newChamp->role = TANK;
            newChamp->level = getRandomNumber( 1, 8 );
            break;
    }

    newChamp->next = NULL;

    return newChamp;
}

/*
	Function: addChampion
	-------------------------
	This function is used to add new champion nodes in descending order in a linked list

        head: the head of the linked list to be edited
        c: the new node that is to be added to the head linked list
		
	Returns: The recently altered linked list.
*/
Champion* addChampion( Champion* head, Champion* c ){

    Champion* cur = head;

    Champion* prev = NULL;

    if(head == NULL)
    {
        return c;
    }

    if(c->level > head->level)
    {
        c->next = cur;
        head = c;
        return head;
    }

    while (cur != NULL && cur->level >= c->level)
    {
        prev = cur;

        cur = cur->next;
    }

    if(prev == NULL)
    {
        c->next = NULL;

        return c;
    }

    prev->next = c;

    c->next = cur;

    return head;
}

/*
	Function: buildChampionList
	-------------------------
	This function is used to add new champion nodes in descending order in a linked list

        n: the number of champions per player that is given by the user as a command line argument.
		
	Returns: The built linked list in correct order.
*/
Champion* buildChampionList( int n ){
    
    int i;

    Champion* head = NULL;

    for ( i = 0; i < n; i++ )
    {
        if( i == 0 )
        {
            head = createChampion();
        }
        else
        {
        Champion* c = createChampion();

        head = addChampion(head, c);
        }
    }

    return head;
}

/*
	Function: printChampionList
	-------------------------
	This function is used to print out each players linked list in order

        head: the head of the linked list to be printed
		
	Returns: Void
*/
void printChampionList( Champion* head ){

    Champion* curr = head;

    while( curr != NULL )
    {        
        switch ( curr->role )
        {
            case MAGE:
                printf( "M%d ", curr->level );
                break;

            case FIGHTER:
                printf( "F%d ", curr->level );
                break;

            case SUPPORT:
                printf( "S%d ", curr->level );
                break;

            case TANK:
                printf( "T%d ", curr->level );
                break;
        }

        curr = curr->next;
    }
    
    printf( "\n" );
}

/*
	Function: removeChampion
	-------------------------
	This function is used to remove champion nodes from the beginning of the players linked list

        head: the head of the linked list to be edited
		
	Returns: The recently altered linked list.
*/
Champion* removeChampion( Champion *head ){


    Champion* tmp = head;

    head = head->next;

    free( tmp );

    return head;
}

/*
	Function: destroyChampionList
	-------------------------
	This function is used to remove each champion from the link list that is passed in.

        head: the head of the linked list to be DESTROYED.
		
	Returns: NULL
*/
Champion* destroyChampionList( Champion* head ){
    while( head != NULL )
    {
        Champion* tmp = head;
        
        head = head->next;

        removeChampion( tmp );
    }

    return NULL;
}

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