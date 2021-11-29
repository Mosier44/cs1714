/*
	main.c
	Project 3
	Colton Mosier

    This is the driver file of the program. The purpose of this program is to create a game that has 2 players (computers) 
    fight against eachother with a linked list of different champions at different levels.
*/

#include "champion.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char* argv[] )
{
    srand( ( int ) time( 0 ) );
    if (argc != 2)
    {
        printf( "Error, expecting two arguments.\n" );
        return -1;
    }
    int size;
    sscanf( argv[1], "%d", &size );

    if(size < 1)
    {
        printf( "Error, argument for number of Champions must be larger than 0.\n" );
        return -1;
    }

    int roundCount = 1;
    Champion* player1 = buildChampionList( size );
    Champion* player2 = buildChampionList( size );


    printf( "============= PLAYER 1 V PLAYER 2 SHOWDOWN =============\n\n" );
    while( ( player1 != NULL ) || ( player2 != NULL ) )
    {

        if( player1 == NULL || player2 == NULL)
        {
            break;
        }

        printf( "----- ROUND %d -----\n", roundCount );

        printf( "Player 1: " );
        printChampionList( player1 );
        printf( "Player 2: " );
        printChampionList( player2 );

        if( player1->role == MAGE )
        {
            printf( "Player 1 is a MAGE and " );
            if( player2->role == MAGE )
            {
                printf( "Player 2 is a MAGE\n" );

                // Winner gains 1 champion, loser loses 1 champion.
                if( player1->level > player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );
                    printf( "Player 1 (MAGE) wins and gains a new champion.\n" );
                    printf( "Player 2 (MAGE) loses one champion.\n" );
                    player1 = addChampion( player1, createChampion() );
                    if( player1 == NULL || player2 == NULL )
                    {
                    break;
                    }
                    player2 = removeChampion( player2 );
                }

                else if( player1->level < player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );
                    printf( "Player 1 (MAGE) loses one champion.\n" );
                    printf( "Player 2 (MAGE) wins and gains a new champion.\n" );
                    player2 = addChampion( player2, createChampion() );
                    if( player1 == NULL || player2 == NULL )
                    {
                    break;
                    }
                    player1 = removeChampion( player1 );
                }

                else
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );
                    printf( "Nothing happens - no penalty or reward.\n" );
                }
            }

            else if( player2->role == FIGHTER )
            {
                printf( "Player 2 is a FIGHTER\n" );

                if( player1->level > player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );
                    // MAGE win, Player1 gains 1 champion. Player2 loses nothing.
                    printf( "Player 1 (MAGE) wins and gains a new champion.\n");
                    printf( "Player 2 (FIGHTER) loses with no penalty.\n" );
                    player1 = addChampion( player1, createChampion() );
                }

                else if( player1->level < player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );
                    // FIGHER win, Player1 losses 1 champion. Player2 gains nothing.
                    printf( "Player 1 (MAGE) loses one champion.\n");
                    printf( "Player 2 (FIGHTER) wins but gains no reward.\n");
                    if( player1 == NULL || player2 == NULL )
                    {
                    break;
                    }
                    player1 = removeChampion( player1 );
                }

                else
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );
                    printf( "Nothing happens - no penalty or reward.\n" );
                }
            }

            else if( player2->role == SUPPORT )
            {
                printf( "Player 2 is a SUPPORT\n" );

                if( player1->level > player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );
                    // MAGE win, Player1 gains 1 champion. Player2 loses 2 champs.
                    printf( "Player 1 (MAGE) wins and gains a champion.\n" );
                    printf( "Player 2 (SUPPORT) loses two champions.\n");
                    player1 = addChampion( player1, createChampion() );
                    if( player1 == NULL || player2 == NULL )
                    {
                    break;
                    }
                    player2 = removeChampion( player2 );
                    if( player1 == NULL || player2 == NULL )
                    {
                    break;
                    }
                    player2 = removeChampion( player2 );
                }

                else if( player1->level < player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );
                    // SUPPORT win, Player1 losses 1 champion. Player2 gains 2 champs.
                    printf( "Player 1 (MAGE) loses one champion.\n");
                    printf( "Player 2 (SUPPORT) wins and gains two champions.\n");
                    if( player1 == NULL || player2 == NULL )
                    {
                    break;
                    }
                    player1 = removeChampion( player1 );
                    player2 = addChampion( player2, createChampion() );
                    player2 = addChampion( player2, createChampion() );
                }

                else
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );
                    printf( "Nothing happens - no penalty or reward.\n" );  
                }
            }

            else if( player2->role == TANK )
            {
                printf( "Player 2 is a TANK\n" );

                player1 = removeChampion( player1 );
                player1 = removeChampion( player1 );
                // Player2 loses one champion, Player1 gains one champion.
                printf( "Player 1 (MAGE) wins and gains a new champion.\n" );
                printf( "Player 2 (TANK) loses one champion.\n" );
                player1 = addChampion( player1, createChampion() );
                if( player1 == NULL || player2 == NULL )
                {
                    break;
                }
                player2 = removeChampion( player2 );
            }
        }

        else if( player1->role == FIGHTER )
        {
            printf( "Player 1 is a FIGHTER and " );
            if( player2->role == MAGE )
            {
                printf( "Player 2 is a MAGE\n" );

                if( player1->level > player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );
                    printf( "Player 1 (FIGHTER) wins but gains no reward.\n" );
                    printf( "Player 2 (MAGE) loses one champion.\n");
                    player2 = removeChampion( player2 );
                }

                else if ( player1->level < player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );
                    printf( "Player 1 (FIGHTER) loses with no penalty.\n" );
                    printf( "Player 2 (MAGE) wins and gains a new champion.\n" );
                    player2 = addChampion( player2, createChampion() );
                }

                else
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );
                    printf( "Nothing happens - no penalty or reward.\n" );
                }
                

            }
            else if( player2->role == FIGHTER )
            {
                printf( "Player 2 is a FIGHTER\n");

                player1 = removeChampion( player1 );
                player2 = removeChampion( player2 );
                printf( "Both players gain a new champion.\n" );
                player1 = addChampion( player1, createChampion() );
                player2 = addChampion( player2, createChampion() );

            }
            else if( player2->role == SUPPORT )
            {
                printf( "Player 2 is a SUPPORT\n" );

                if ( player1->level > player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );

                    printf( "Player 1 (FIGHTER) wins but gains no reward.\n" );
                    printf( "Player 2 (SUPPORT) loses one champion.\n" );

                    player2 = removeChampion( player2 );
                }

                else if ( player1->level < player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );

                    printf( "Player 1 (FIGHER) loses with no penalty.\n" );
                    printf( "Player 2 (SUPPORT) wins and gains one champion.\n" );

                    player2 = addChampion( player2, createChampion() );
                }

                else
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );

                    printf( "Nothing happens - not penalty or reward.\n" );
                }
                
                
            }
            else if ( player2->role == TANK )
            {
                printf( "Player 2 is a TANK\n" );
                
                player1 = removeChampion( player1 );
                player2 = removeChampion( player2 );

                printf( "Player 1 (FIGHER) wins and gains a new champion.\n" );
                printf( "Player 2 (TANK) loses with no penalty.\n" );

                player1 = addChampion( player1, createChampion() );
            }
        }
        else if( player1->role == SUPPORT )
        {
            printf( "Player 1 is a SUPPORT and " );
            if( player2->role == MAGE )
            {
                printf( "Player 2 is a MAGE\n" );

                if ( player1->level > player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );

                    printf( "Player 1 (SUPPORT) wins and gains two new champions.\n" );
                    printf( "Player 2 (MAGE) loses one champion.\n" );

                    player2 = removeChampion( player2 );
                    player1 = addChampion( player1, createChampion() );
                    player1 = addChampion( player1, createChampion() );
                }

                else if( player1->level < player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );

                    printf( "Player 1 (SUPPORT) loses two champions.\n" );
                    printf( "Player 2 (MAGE) wins and gains a new champion.\n" );

                    if( player1 == NULL || player2 == NULL )
                    {
                    break;
                    }
                    player1 = removeChampion( player1 );
                    if( player1 == NULL || player2 == NULL )
                    {
                    break;
                    }
                    player1 = removeChampion( player1 );
                    player2 = addChampion( player2, createChampion() );
                }

                else
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );

                    printf( "Nothing happens - no penalty or reward.\n" );
                }
                
                
            }
            else if( player2->role == FIGHTER )
            {
                printf( "Player 2 is a FIGHTER\n" );
                if ( player1->level > player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );

                    printf( "Player 1 (SUPPORT) wins and gains a new champions.\n" );
                    printf( "Player 2 (FIGHTER) loses one champion.\n" );

                    if( player1 == NULL || player2 == NULL )
                    {
                    break;
                    }

                    player2 = removeChampion( player2 );
                    player1 = addChampion( player1, createChampion() );

                }

                else if( player1->level < player2->level )
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );

                    printf( "Player 1 (SUPPORT) loses two champions.\n" );
                    printf( "Player 2 (FIGHER) wins and gains a new champion.\n" );
                    if( player1 == NULL || player2 == NULL )
                    {
                    break;
                    }
                    player1 = removeChampion( player1 );
                    if( player1 == NULL || player2 == NULL )
                    {
                    break;
                    }
                    player1 = removeChampion( player1 );
                    player2 = addChampion( player2, createChampion() );
                }

                else
                {
                    player1 = removeChampion( player1 );
                    player2 = removeChampion( player2 );

                    printf( "Nothing happens - no penalty or reward.\n" );
                }
            }
            else if( player2->role == SUPPORT )
            {
                printf( "Player 2 is a SUPPORT\n" );
                player1 = removeChampion( player1 );
                player2 = removeChampion( player2 );

                printf( "Both players lose one champion.\n" );
                if( player1 == NULL || player2 == NULL )
                {
                    break;
                }
                player1 = removeChampion( player1 );
                player2 = removeChampion( player2 );

            }
            else if( player2->role == TANK)
            {
                printf( "Player 2 is a TANK\n" );

                player1 = removeChampion( player1 );
                player2 = removeChampion( player2 );

                printf( "Player 1 (SUPPORT) loses one champion.\n" );
                printf( "Player 2 (TANK) wins and gains a new champion.\n" );

                if( player1 == NULL || player2 == NULL )
                {
                    break;
                }

                player1 = removeChampion( player1 );
                player2 = addChampion( player2, createChampion() );
            }
        }
        else if( player1->role == TANK )
        {
            printf( "Player 1 is a TANK and " );
            if( player2->role == MAGE )
            {
                printf( "Player 2 is a MAGE\n" );
                player1 = removeChampion( player1 );
                player2 = removeChampion( player2 );

                printf( "Player 1 (TANK) loses one champion.\n" );
                printf( "Player 2 (MAGE) wins and gains a new champion.\n" );

                if( player1 == NULL || player2 == NULL )
                {
                    break;
                }

                player1 = removeChampion( player1 );
                player2 = addChampion( player2, createChampion() );

            }
            else if( player2->role == FIGHTER )
            {
                printf( "Player 2 is FIGHTER\n" );
                player1 = removeChampion( player1 );
                player2 = removeChampion( player2 );
                
                printf( "Player 1 (TANK) loses but with no penalty.\n" );
                printf( "Player 2 (FIGHTER) wins and gains a new champion.\n" );

                player2 = addChampion(player2, createChampion() );

            }
            else if( player2->role == SUPPORT )
            {
                printf( "Player 2 is a SUPPORT\n" );
                player1 = removeChampion( player1 );
                player2 = removeChampion( player2 );

                printf( "Player 1 (TANK) wins and gains a new champion.\n" );
                printf( "Player 2 (SUPPORT) loses with no penalty.\n" );

                player1 = addChampion( player1, createChampion() );
            }
            else if ( player2->role == TANK )
            {
                printf( "Player 2 is a TANK\n" );
                player1 = removeChampion( player1 );
                player2 = removeChampion( player2 );
                printf( "Nothing happens - no penalty or reward.\n" );
            }
        }

        roundCount++;
        printf("\n" );
    }

    printf( "============= GAME OVER =============\n" );

    printf( "Player 1 ending champion list: " );
    printChampionList( player1 );
    printf( "Player 2 ending champion list: " );
    printChampionList( player2 );

    if( player1 != NULL )
    {
        printf( "Player 2 ran out of champions. Player 1 wins.\n" );
    }
    else if( player2 != NULL )
    {
        printf( "Player 1 ran out of champions. Player 2 wins.\n" );
    }
    else
    {
        printf( "TIE -- both players ran out of champions.\n" );
    }

    destroyChampionList( player1 );
    destroyChampionList( player2 );

    return 0;
}