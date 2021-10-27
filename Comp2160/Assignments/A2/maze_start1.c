#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

#define MAX_DIMENSION 20

// constant definitions for the different cell states
const char WALL    = '1';
const char SPACE   = '0';
const char VISITED = '.';
const char MOUSE   = 'm';
const char EXIT    = 'e';

typedef enum BOOL { false, true } Boolean;

struct CELL
{
  int row;
  int column;
};
typedef struct CELL Cell;

typedef struct CELL_NODE CellNode;
struct CELL_NODE
{
  Cell     cell;
  CellNode *next;
};

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

CellNode *top = NULL;

// a 2D array used to store the maze
char maze[MAX_DIMENSION][MAX_DIMENSION];
int mazeRows;
int mazeCols;

// holds the location of the mouse and escape hatch
Cell mouse;
Cell escape;
//stores curr and goal values
Cell currCell;
Cell goalCell;
Cell startCell;
//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

// basic cell manipulation

// returns true if the cells are at the same position in our maze
Boolean equalCells(const Cell cell1, const Cell cell2);
// returns a new cell object
Cell makeCell(const int row, const int col);
// returns true if the cell is within our maze
Boolean validCell(const Cell theCell);

// routines for managing our backtracking

// returns true if there are no more cells to try
Boolean noMoreCells();
// returns the next cell to try for a path out of the maze
Cell nextCell();
// introduces a new cell to try
void addCell(const Cell cell);

void printMaze();
void loadMaze();

// returns true if there's a solution to the maze
Boolean solveMaze();

// our invariant checker
void checkState();

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    loadMaze();
    if ( solveMaze() )
      printf( "The mouse is free!!!!\n" );
    else
      printf( "The mouse is trapped!!!!\n" );
    
    printf( "\nEnd of processing\n" );
    
  return EXIT_SUCCESS;
}


//////////////////////////////////////////////
// Cell routines
//////////////////////////////////////////////
Cell makeCell(int row, int col)
{
	Cell newCell;
	newCell.row = row;
	newCell.column = col;
	
	return newCell;
}
Boolean equalCells(const Cell cell1, const Cell cell2)
{
	Boolean check = false;
	if(cell1.row== cell2.row && cell1.column == cell2.column)
	{
		check = true;
	}
	else
	{
		check = false;
	}
	return check; 
}
void addCell(const Cell cell)
{
	//if we have entered here we need to add to the list
	//create cell node
	CellNode *newCellNode;
	newCellNode= malloc(sizeof(struct CELL_NODE));
	newCellNode->cell = cell;
	// add to list
	if(top == NULL)
	{
		printf("I work\n");
		top= newCellNode;
		newCellNode->next = NULL;
		printf("new node cell row = %d new node cell column = %d\n", top->cell.row, top->cell.column);		
		if(top->next == NULL)
		{
			printf("yeah its null\n");
		}	
	}
	else //top contains a node
	{	
		newCellNode->next= top;
		top = newCellNode;
		printf("new node cell row = %d new node cell column = %d\n", top->cell.row, top->cell.column);
		printf("new node cell row = %d new node cell column %d\n", top->next->cell.row, top->next->cell.column);
	}
		
}

Boolean validCell(const Cell theCell)
{
	Boolean check = false;
	
	//check if any of the cells go out of bounds
	//if a cell's rows or columns are  greater than our array length constant it is out of bounds
	 
	if(theCell.row < MAX_DIMENSION && theCell.column < MAX_DIMENSION)
	check = true;

	return check;
}

Cell nextCell()
{
	Cell tryNext= top->cell;
	if(top->next != NULL)
        {
                       //      currCell= tempCell; //previous position
                free(top);
                top = top->next; //delete try
        }
        else    //there is onlt one item in the stack
        {
        	top = NULL;
                printf("top is now null");
        }
	return tryNext;
}

//////////////////////////////////////////////
// List routines
//////////////////////////////////////////////
Boolean noMoreCells()
{
	Boolean check = false;
	if(top == NULL)
	{
		check = true;
	}	
	return check;
}

//////////////////////////////////////////////
// Maze routines
//////////////////////////////////////////////
void loadMaze()
{	
	
	assert(stdin != NULL);
	char mazeText[20];
	fgets(mazeText,20,stdin);
	char *token;

	//store number of rows
	token = strtok(mazeText, " ");
	mazeRows= atoi(token);
	assert(atoi(token) == mazeRows);
//	printf("%d", mazeRows);
	
	//store number of columns
	token = strtok(NULL, " ");
	mazeCols = atoi(token);
	assert(atoi(token) == mazeCols);
//	printf("%d", mazeCols);
	//print maze
//	char mazeText[MAX_DIMENSION];
	int i = 0;
	int j = 0;
	while(fgets(mazeText,21,stdin) !=NULL)
	{	
	
		mazeText[strlen(mazeText)-1] = '\0';
		token= strtok(mazeText, " ");
		while(token !=NULL)
		{
			j = 0;	
			while(j < mazeCols)
			{	
				strcpy(&maze[i][j], token);
				token = strtok(NULL, " ");
				j++;
			}
			token = strtok(NULL, " ");
		}
		i++;

	}
	//the maze is loaded in
	//find the mouse and escape
	i=0;
	j=0;
//	printf("%c", MOUSE);
	while(i<mazeRows)
	{
		j=0;
		while(j<mazeCols)
		{
			if(maze[i][j] == 'r')
			{
				printf("found the mouse at row %d column %d\n",i,j);
				startCell= makeCell(i, j);
				mouse = startCell;
				currCell = startCell;
				//printf("row %d", mouse.row);
				//printf("column %d", mouse.column);
				assert(equalCells(startCell, mouse));		
			}
			if(maze[i][j] == EXIT)
			{
				printf("found the exit at row %d column %d\n",i,j);
				goalCell= makeCell(i, j);
				escape = goalCell;
			}
			j++;
		}	
		i++;	
	}
	printMaze();
int p=0;
//	Cell tempCell = currCell;
	while(!equalCells(currCell, goalCell))
	{
		int neighbors = 0;
		maze[currCell.row][currCell.column] = VISITED;
		printMaze();

		
       		//check top, right, bottom, left
		neighbors = 0;
       		//top
		if(maze[currCell.row - 1][currCell.column] != WALL && maze[currCell.row - 1][currCell.column] != VISITED)
       		{
			
                	printf("top is available to try\n");
			Cell topCell= makeCell(currCell.row-1, currCell.column);
			assert(validCell(topCell));
			addCell(topCell);
                	neighbors++;
        	}
		
		//right 
		if(maze[currCell.row][currCell.column+1] != WALL && maze[currCell.row][currCell.column+1] != VISITED)
        	{
                	printf("right is available to try\n");
			Cell rightCell= makeCell(currCell.row, currCell.column+1);
			printf("row = %d column =%d\n", rightCell.row, rightCell.column);
			assert(validCell(rightCell));
			addCell(rightCell);
                	neighbors++;
       	        }
        
		//bottom
        	if(maze[currCell.row + 1][currCell.column] != WALL && maze[currCell.row + 1][currCell.column] != VISITED)
        	{
                	printf("bottom is available to try\n");
			Cell bottomCell= makeCell(currCell.row+1, currCell.column);
			 printf("row = %d column =%d\n", bottomCell.row, bottomCell.column);
			assert(validCell(bottomCell));
        		addCell(bottomCell);        

			neighbors++;
        	}

        	//left
        	if(maze[currCell.row][currCell.column - 1] != WALL && maze[currCell.row][currCell.column - 1] != VISITED)
        	{
                	printf("left is available to try\n");
                	Cell leftCell= makeCell(currCell.row, currCell.column-1);
			assert(validCell(leftCell));
			addCell(leftCell);
				
			neighbors++;
        	}
        	if(neighbors == 0)//no neighbors so go back
        	{	
			if(noMoreCells())
			{
				break;
			}	
		}

		// take a step
		currCell = nextCell();
			
			
	}
	printMaze();
	free(top);
}

void printMaze()
{	
	for(int i = 0; i< mazeRows; i++)
	{
		printf("%s\n", maze[i]);
	}
	printf("\n");
}

Boolean solveMaze()
{
	Boolean check = false;
	if(equalCells(currCell, goalCell))
	{
		check = true;
	}
	return check;

}

