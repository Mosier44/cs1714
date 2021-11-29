/*
	records.h
	Project 2
	Colton Mosier

    This file holds the function prototypes as well as the definition of struct RouteRecord and enum SearchType.
*/
#ifndef RECORDS_H_
#define RECORDS_H_

// Define struct RouteRecord
typedef struct RouteRecord_struct
{
    char origin[ 4 ];
    char destination[ 4 ];
    char airline[ 3 ];
    int totalPassenger[ 7 ];
} RouteRecord;

 // Define enum SearchType
typedef enum SearchType{
    ROUTE,
    ORIGIN,
    DESTINATION, 
    AIRLINE
} SearchType;


/*
	Function: createRecords
	-------------------------
	This function loops through the input file one time to initialize the max size of RouteRecord array based on how many lines are in the file.
    The function then dynamically allocates memory for the array.
					
		fileIn: File pointer to the file being used for data

	Returns: Returns a pointer to RouteRecord at it's memory allocated location
*/
RouteRecord* createRecords( FILE* fileIn );


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

int fillRecords( RouteRecord* r, FILE* fileIn );


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

int findAirlineRoute( RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx );


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

void searchRecords( RouteRecord* r, int length, const char* key1, const char* key2, SearchType st );

/*
	Function: fillRecords
	-------------------------
	This function prints out the menu for the user to use as a guideline on how to use the program.

	Returns: Void
*/
void printMenu( );

#endif 