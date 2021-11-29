/*
	main.c
	Project 2
	Colton Mosier

    This file is the driver of the program. It calls on the functions in records.c to load the data from 
    the CSV file and to run queries that the user asks for.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "route-records.h"


/*
	Function: main
	-------------------------
	This function is the driver of the program. It takes the user's command line arguments to decide which file to use in the program. The function handles no 
    input for file name, as well as if the file is not able to be opened. It then calls on the functions in record.c to load the data from the inputted file
    and runs queries that user asks for based on inputted menu options. Cases of wrong inputs for the menu options are handled. 
    The program will end if menu option 5 is inputted.
					
		argc: represents the number of inputted command line arguments
        argv[]: represents the actual command line arguments 

	Returns: Integer, a non-zero represents error, while a zero represents proper execution.
*/

int main( int argc, char *argv[ ] )
{
    /* Declare variables here */

    FILE* fp = NULL;
    char strUserInput[ 2 ];
    RouteRecord* r;
    int actualNumberOfFlights;
    int userOption = 0;
    char key1[ 4 ];
    char key2[ 4 ]; 
    
    /* Check command line arguments here. */

    if(argc != 2 )
    {
        printf( "ERROR: Missing file name\n" );
        return 1;
    }
    
    /* Attempt to open the file. */

    printf( "Opening %s...\n", argv[ 1 ] );
    fp = fopen( argv[ 1 ], "r" );
    
    /* Check to see if the file opens.*/

    if( fp == NULL )
    {
        printf( "ERROR: Could not open file\n" );
        return 1;
    }

    r = createRecords( fp );
    actualNumberOfFlights = fillRecords( r, fp );
    printf( "Unique routes by airlines: %d", actualNumberOfFlights );
    fclose( fp );
    

    while( 1 )
    {
        printMenu( );
        userOption = 0;  
        scanf( "%s", strUserInput );
        sscanf( strUserInput, "%d", &userOption );

        if( userOption > 5 || userOption < 1 )
        {
            printf("Invalid choice.");
            continue;
        }

        switch( userOption )
        {
            case 1:
                printf( "\nEnter origin: " );
                scanf( "%s", key1 );
                printf( "\nEnter destination: " );
                scanf( "%s", key2 );
                searchRecords( r, actualNumberOfFlights, key1, key2, ROUTE );
                break;
            case 2:
                printf( "\nEnter origin: " );
                scanf( "%s", key1 );
                searchRecords( r, actualNumberOfFlights, key1, " ", ORIGIN );
                break;
            case 3:
                printf( "\nEnter destination: " );
                scanf( "%s", key1 );
                searchRecords( r, actualNumberOfFlights, key1, " ", DESTINATION );
                break;
            case 4:
                printf( "\nEnter airline: " );
                scanf( "%s", key1 );
                searchRecords( r, actualNumberOfFlights, key1, " ", AIRLINE );
                break;
            case 5:
                printf( "Good-bye!\n" );
                free( r );
                return 0;
        }
    }
    return 0;
}
