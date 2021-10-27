// NAME: Eriq Hampton
// STUDENT NUMBER: 7852830
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Mahdi Safiur
// ASSIGNMENT: Assignment 1, QUESTION: Question 1
//
// REMARKS: Accepts the a file, reads every line 
// and returns the Nthword corresponding to the 
//integer present afterward until NULL.
//-----------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_LENGTH 1000


void extractWord(char lineRead[], int wordNumber);
static char* nthWord;
int main(void)
{
	
	char line[LINE_LENGTH];
	char wordNum[5];

	// read the entire text file line by line until empty 
	while ( fgets( line, LINE_LENGTH, stdin) != NULL )
	{
		//overwrites newline character
		line[strlen(line)-1] = '\0';
		
		fgets(wordNum, LINE_LENGTH, stdin);
		wordNum[strlen(wordNum)-1] = '\0';
        	
		// print each line and retrieve the integer contained in the next line
		printf("Read line: \"%s\", extracting word [%s]\n", line, wordNum);
		extractWord(line,atoi(wordNum));
		printf("Word # %s is: %s\n", wordNum, nthWord);
	}
	// Program successfully completed
	printf("\nEnd Processing\n");
} 

//------------------------------------------------------
// extractWord
//
// PURPOSE: Extracts the nth word from the line that was previously printed
// INPUT PARAMETERS:
// Accepts a char array that stores the string from a text file
// OUTPUT PARAMETERS:
// Stores address of "result" (nthword) for access outside of the method
// 
//------------------------------------------------------
void extractWord(char lineRead[], int wordNumber)
{
	int start;
	int end;
	int spaces = 1;
       	static char result[] = "";
	int i = 0;	
	
	// search for the nth non-blank character
	for(start = 0; start < strlen(lineRead) && spaces < wordNumber; start++)
	{

		if(isblank(lineRead[start]))
		{
		 spaces++;
		}
	}

	// only need to continue if we haven't gone past the end of the string
	if(start < strlen(lineRead))
	{
		for(end = start; end < strlen(lineRead) && !(isblank(lineRead[end])); end++);
	
		for(i = 0; start <= end; i++)
		{
			result[i] = lineRead[start];
			start++;
		}
	}
	result[i] = '\0';
	nthWord = result;
}

