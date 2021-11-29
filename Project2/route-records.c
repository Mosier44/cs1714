/*
	records.c
	Project 2
	Colton Mosier

    This file holds the functions themselves that the main.c driver file will call on to preform an action.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "route-records.h"


/*
	Function: createRecords
	-------------------------
	This function loops through the input file one time to initialize the max size of RouteRecord array based on how many lines are in the file.
    The function then dynamically allocates memory for the array.
					
		fileIn: File pointer to the file being used for data

	Returns: Returns a pointer to RouteRecord at it's memory allocated location
*/

RouteRecord* createRecords( FILE* fileIn )
{
    int count = 0;
    char fileData[ 50 ];
    int i, j;
    RouteRecord* r = NULL;


    // check if fileIn is empty or non-existent 
    if( fileIn == NULL )
    {
      return 0;
    }

    // Ignores first line or header line of file
    fgets( fileData, 50, fileIn );

    // loop through file to get line count not including hearder line
    while( fgets( fileData, 50, fileIn ) != NULL )
    {
        count++;
    }
 
    // dynamically assign memory for RoutRecord struct based on how many lines of information in csv file, excluding first line.
     r = ( RouteRecord* ) malloc ( sizeof( RouteRecord ) * count );
    

    rewind( fileIn );

    // Initialize totalPassenger to 0 for each of the array indexes
    for( i = 0; i < count; i++ )
    {
        for( j = 0; j < 6; j++ )
        {
            r[ i ].totalPassenger[ j ] = 0;
        }
    }

    return r;
}


/*
	Function: fillRecords
	-------------------------
	This functions job is to loop through the input file to then use the information gathered to call findAirlineRoute to search if
    the route information gathered is already in the array. If the information is NOT in the array, the function adds the new route to the array. However, if
    the route information was found in the search through the array, the function updates the passanger record for the found route information.

        r: Pointer to RouteRecord array			
		fileIn: File pointer to the file being used for data

	Returns: Integer representing the number of actual unique RouteRecord's used
*/

int fillRecords( RouteRecord* r, FILE* fileIn )
{
    int length = 0;
    int totalPassengerIndex;
    char tmpStr[ 50 ];
    int foundIndex;
    char tmpOrigin[ 4 ];
    char tmpDestination[ 4 ];
    char tmpAirline[ 3 ];
    int tmpPassCount;

    // Skips the first line in file
    fgets( tmpStr, 50, fileIn );

    /* Loops through the file and places flights into their own array slot, if duplicate udpate flight passanger count */
    while( fscanf( fileIn, "%d,%[^,],%[^,],%[^,],%[^,],%d", &totalPassengerIndex, tmpOrigin, tmpDestination, tmpAirline, tmpStr, &tmpPassCount) == 6 )
    {

        if( length == 0 )
        {
            strcpy( r[ length ].origin, tmpOrigin );
            strcpy( r[ length ].destination, tmpDestination );
            strcpy( r[ length ].airline, tmpAirline );
            r[ length ].totalPassenger[ totalPassengerIndex - 1 ] = tmpPassCount;
            length++;
        }
        else
        {
            foundIndex = findAirlineRoute( r, length, tmpOrigin, tmpDestination, tmpAirline, 0 );
            if( foundIndex == -1 )
            {
                strcpy( r[ length ].origin, tmpOrigin );
                strcpy( r[ length ].destination, tmpDestination );
                strcpy( r[ length ].airline, tmpAirline );
                r[ length ].totalPassenger[ totalPassengerIndex - 1 ] = tmpPassCount;
                length++;
            }
            else
            {
                r[ foundIndex ].totalPassenger[ totalPassengerIndex - 1 ] = tmpPassCount;
            }
        }
    }

    return length;
}


/*
	Function: findAirlineRoute
	-------------------------
	This recursive function searching through the given RouteRecord array for exact given origin, destination, and airline. If the function does not find the corresponding
    route, the function returns -1. However, if the function finds the given route, the function will return the index at which the route is located within the RouteRecord
    array.

		r: RouteRecord array pointer 
        length: The size of actual unique RouteRecord's array
        origin: String of origin name to search for in existing array
        destination: String of destination name to search for in existing array
        airline: String of airline name to search for in existing array
        curIdx: Int value that is used as the index when searching through the RouteRecord array.

	Returns: Integer representing the index found
*/

int findAirlineRoute( RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx )
{

    if( curIdx <= length )
    {
        if( strcmp( r[ curIdx ].origin, origin ) == 0 && strcmp( r[ curIdx ].destination, destination ) == 0 && strcmp( r[ curIdx ].airline, airline ) == 0)
        { 
 
            return curIdx;
        }
        else
            curIdx = findAirlineRoute( r, length, origin, destination, airline, curIdx += 1 );
    }
    else
        return -1;

    return curIdx;

    /* ---------------------------------------- NO RECURSION --------------------------------------------------------
    int index;

    for( index = 0; index < length; index++ )
    {   
        if( strcmp( r[ index ].origin, origin ) == 0 )
        { 
            if( strcmp( r[ index ].destination, destination ) == 0 )
            {
                if ( strcmp( r[ index ].airline, airline ) == 0 )
                {
                    return index;
                }
            }
        }
    }
    return -1; 
    -----------------------------------------------------------------------------------------------------------------
    */
}


/*
	Function: searchRecords
	-------------------------
	This function loops through the RouteRecord array looking for the inputted search values from the user with the specific SearchType enum inputted to function. 
    If the function finds the key(s) the user was searching for it will print out the airline and the route for each matching value. Next, the function will 
    print out the total number of passengers on all matching records, total number of passengers by month for all matching records, as well as average numbers of 
    passengers per month. However, if no matching values were found, the function will print all 0's for the above values.

        r: Pointer to RouteRecord array			
		length: File pointer to the file being used for data
        key1: Search value 1
        key2: Search value 2
        st: SearchType enum value

	Returns: Void
*/

void searchRecords( RouteRecord* r, int length, const char* key1, const char* key2, SearchType st )
{
    int i, j, count = 0;
    int months[ 7 ] = { 0, 0, 0, 0, 0, 0, 0 };
    int totalFliers = 0;
    if( st == ROUTE )
    {
        count = 0;
        printf( "\n\nSearch by route...\n" );
        for( i = 0; i < length; i++ )
        {
            if( strcmp( r[ i ].origin, key1 ) == 0 && strcmp( r[ i ].destination, key2 ) == 0)
            {
                printf( "%s (%s-%s) ", r[ i ].airline, key1, key2 );
                count++;
                for( j = 0; j < 6; j++ )
                {
                    totalFliers += r[ i ].totalPassenger[ j ];
                    months[ j ] = months[ j ] + r[ i ].totalPassenger[ j ];
                }
            }
        }
        printf( "\n%d matches were found.\n", count );
        printf( "\nStatistics\n" );
        printf( "Total Passangers:%23d\n\n", totalFliers );

        for( i = 0; i < 6; i++ )
        {
            printf( "Total Passangers in Month %d:%12d\n", i + 1, months[ i ] );
        }
        printf( "\nAverage Passengers per Month:%11d\n", totalFliers / 6 );
    }

    else if( st == ORIGIN )
    {
        count = 0;
        printf( "\n\nSearch by origin...\n" );
        for( i = 0; i < length; i++ )
        {
            if( strcmp( r[ i ].origin, key1 ) == 0 )
            {
                printf( "%s (%s-%s) ", r[ i ].airline, key1, r[ i ].destination );
                count++;
                for( j = 0; j < 6; j++ )
                {
                    totalFliers += r[ i ].totalPassenger[ j ];
                    months[ j ] = months[ j ] + r[ i ].totalPassenger[ j ];
                }
                
            }
        }
        printf( "\n%d matches were found.\n", count );
        printf( "\nStatistics\n" );
        printf( "Total Passangers:%23d\n\n", totalFliers );
        for( i = 0; i < 6; i++ )
        {
            printf( "Total Passangers in Month %d:%12d\n", i + 1, months[ i ] );
        }
        printf( "\nAverage Passengers per Month:%11d", totalFliers / 6 );   
    }

    else if( st == DESTINATION )
    {
        count = 0;
        printf( "\n\nSearch by destination...\n" );
        for( i = 0; i < length; i++ )
        {
            if( strcmp( r[ i ].destination, key1 ) == 0 )
            {
                printf( "%s (%s-%s) ", r[ i ].airline, r[ i ].origin, key1 );
                count++;
                for( j = 0; j < 6; j++ )
                {
                    totalFliers += r[ i ].totalPassenger[ j ];
                    months[ j ] = months[ j ] + r[ i ].totalPassenger[ j ];
                }
                
            }
        }
        printf( "\n%d matches were found.\n", count );
        printf( "\nStatistics\n" );
        printf( "Total Passangers:%23d\n\n", totalFliers );
        for( i = 0; i < 6; i++ )
        {
            printf( "Total Passangers in Month %d:%12d\n", i + 1, months[ i ] );
        }
        printf( "\nAverage Passengers per Month:%11d", totalFliers / 6 );
    }

    else if( st == AIRLINE )
    {
         count = 0;
         printf( "\n\nSearch by airline...\n" );
        for( i = 0; i < length; i++ )
        {
            if( strcmp( r[ i ].airline, key1 ) == 0 )
            {
                printf( "%s (%s-%s) ", key1, r[ i ].origin, r[ i ].destination );
                count++;
                for( j = 0; j < 6; j++ )
                {
                    totalFliers += r[ i ].totalPassenger[ j ];
                    months[ j ] = months[ j ] + r[ i ].totalPassenger[ j ];
                }
                
            }
        }
        printf( "\n%d matches were found.\n", count );
        printf( "\nStatistics\n" );
        printf( "Total Passangers:%23d\n", totalFliers );
        printf( "\n" );
        for( i = 0; i < 6; i++ )
        {
            printf( "Total Passangers in Month %d:%12d\n", i + 1, months[ i ] );
        }
        printf( "\nAverage Passengers per Month:%11d", totalFliers / 6 );
    }
}


/*
	Function: fillRecords
	-------------------------
	This function prints out the menu for the user to use as a guideline on how to use the program.

	Returns: Void
*/

void printMenu(){
    printf( "\n" );
    printf( "\n\n######### Airline Route Records Database MENU #########\n" );
    printf( "1. Search by Route\n" );
    printf( "2. Search by Origin Airport\n" );
    printf( "3. Search by Destination Airport\n" );
    printf( "4. Search by Airline\n" );
    printf( "5. Quit\n" );
    printf( "Enter your selection: " );
}