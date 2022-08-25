//-----------------------------------------
// NAME: Eriq Hampton
// STUDENT NUMBER: 7852830
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Mahdi Safiur
// ASSIGNMENT: Assignment 1, QUESTION: Question #2
//
// REMARKS: Caluates the levenshtein distance between
// two strings.
//-----------------------------------------

#include <stdio.h>
#include <string.h>
#include <assert.h>

static int testsFailed = 0;
static int testsExecuted = 0;
static int levenshtein(char s[], char t[]);
static int minimumDistance(int minimum[], int size);
static void testDistance(char s[],char t[], int expected);


int main (void)
{
	printf( "Testing typical cases.\n" );
        testDistance( "kitten", "kitten", 0 );
        testDistance( "kitten", "sitting", 3 );
        testDistance( "kitten", "mittens", 2 );
        testDistance( "balloon", "saloon", 2 );
        testDistance( "hello", "doggo", 4 );
        testDistance( "\t\thi", "\t\t\t\thi", 2 );

        printf( "\nTesting empty/edge cases.\n" );
        testDistance( "", "", 0 );
        testDistance( "hello", "", 5 );
        testDistance( "", "doggo", 5 );
        testDistance( "a", "b", 1 );
        testDistance( "b", "b", 0 );
        testDistance( " ", " ", 0 );

        printf( "\nThis might take a while...\n" );
        testDistance( "12345678901", "123456789012", 1 );  

	//These tests should fail because of the terminating characters contained in them
        printf( "\n******These tests will be opposite in the C version******\n" );
        printf( "\n******These tests **should** FAIL in the C version*******\n" );
        testDistance( "kitten", "mitten\0s", 3 );          
        testDistance( "\0totally", "\0different", 9 );

        printf( "\nTotal number of tests executed: %d\n" , testsExecuted );
        printf( "Number of tests passed: %d\n" ,(testsExecuted - testsFailed) );
        printf( "Number of tests failed: %d\n" , testsFailed );	
	printf( "Processing Complete\n");
}

//------------------------------------------------------
// testDistance
//
// PURPOSE: tests the distance of determined strings 
// by comparing the expected distance with the
// actual distance
//
// INPUT PARAMETERS:
// Accepts both strings respectively and the expected distances respectively
// OUTPUT PARAMETERS:
// This function merely prints whether the distances compare properly
// and counts the number of times it passes and fails
//------------------------------------------------------
static void testDistance( char s[], char t[], int expected)
{
	int distance = levenshtein(s, t);

	if (distance == expected )
	{
		printf("Passed! You can get from '%s' to '%s' in %d moves\n", s,t,expected);
        }
	else
	{
		printf("FAILED: I thought it would take %d moves, but apparently it takes %d moves to get from '%s' to '%s'.\n",expected,
			distance,s,t);
		testsFailed++;
	}
	
	testsExecuted++;
}

//------------------------------------------------------
// levenshtein
//
// PURPOSE: Tells user the distance between a determined word
// versus another (recursively)
// INPUT PARAMETERS:
// Accepts both string from the main function respectively.
// OUTPUT PARAMETERS:
// Returns the number of inputs required to make either
// string identical.
//------------------------------------------------------
static int levenshtein(char s[], char t[])
{
	int cost;
	int distance;
	char deleteS[strlen(s)+31];
	char  deleteT[strlen(t)+1];

	//if one string is empty the distance is equal to the other string's length
	if(strlen(s) != 0)
	{
		distance = strlen(t);
	}

	else if (strlen(t) == 0)
	{
		distance = strlen(s);
	}

	else
	{
		if(s[0] == t[0])
		{
			cost = 0;
		}

		else
		{
			cost = 1;
		}
		
		// copies index 1 of the original strings respectively into a new arrays.
		for(int i = 1; i <= strlen(s); i++)
		{
		deleteS[i-1]= s[i];
		}		
		
		for(int i = 1; i <= strlen(t); i++)
		{
		deleteT[i-1] = t[i];
		}		
		
		// abort if the length of these arrays are not equal
		assert(strlen(deleteS) == strlen(s)-1);
		assert(strlen(deleteT) == strlen(t)-1);
        	
		// abort the strings are not identical
		assert(strcmp(s, deleteS));
 		assert(strcmp(t, deleteT));

		//establishes the minimum distance
		int minimum[] = {levenshtein(deleteS,t)+1, levenshtein(s, deleteT)+1, levenshtein(deleteS, deleteT)+ cost};
		int size= sizeof(minimum) / sizeof(minimum[0]);
		distance = minimumDistance(minimum, size);  
			
	}
	return distance;
}

//------------------------------------------------------
// minimumDistance
//
// PURPOSE: Accepts the distances stored in int array minimum
// and accepts the smallest distance as the minimum distance
// INPUT PARAMETERS:
// Accepts int minimum array values and length.
// OUTPUT PARAMETERS:
// Returns the minimum distance among the 3 indexes
//------------------------------------------------------
static int minimumDistance(int minimum[],int size )
{
	int min = 0;	
	
	if( size > 0 )
	{
	  min = minimum[0];

	  for( int i = 1; i< size; i++)
	  {
	    if(minimum[i] < min)
	    {
		min = minimum[i];
	    }
	  }
	}
	
	return min;
}	
