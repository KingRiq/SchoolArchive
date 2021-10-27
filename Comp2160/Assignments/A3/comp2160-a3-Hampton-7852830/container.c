/*
 * Container.h
 * COMP 2160 Programming Practices
 * Assignment 3
 *
 * Author Eriq Hampton
 * Implementation file for a Container
 * Implemented as an unsorted linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include "container.h"
#include <string.h>
#include <assert.h>
//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

typedef struct NODE{
  char *item;
  struct NODE *next;
} Node;

// Container definition
struct CONTAINER{
  Node *head;

  // used to track where we are for the list traversal methods
  Node *traverseNode;
  
  // used to track testing values
  int numNodes;
  int numTraversals;  
};


//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

//Invariant Checker
static void validateContainer( Container *theContainer )
{

	if(theContainer !=NULL)
	{
		if(theContainer->head == NULL)
		{
			assert(theContainer->traverseNode == NULL);
			assert(theContainer->numTraversals == 0);
			assert(theContainer->numNodes == 0);
		}
        else
        {
            Node *previous = theContainer->traverseNode;
            if(theContainer->head != NULL && theContainer->traverseNode->item == theContainer->head->item)
            {
                assert(strcmp(theContainer->head->item, theContainer->traverseNode->item) == 0);
                assert(theContainer->numTraversals == 1);
                assert(theContainer->numTraversals <= theContainer->numNodes);
            }
            
    		previous= theContainer->head;
    		while(theContainer->head != NULL && previous != NULL)
    		{
                int i =0;
                while(previous->item[i] != '\0')
                    i++;
                assert(previous->item[i]== '\0');
                previous = previous->next;
    		}
    		assert(previous == NULL);
            assert(theContainer->numTraversals <= theContainer->numNodes);
            
        }
	}
}// validateContainer

// make an empty container that we can start working with
Container * createContainer()
{

	Container *newContainer = NULL;
	newContainer = malloc(sizeof(Container));
	newContainer->head = NULL;
	newContainer->traverseNode= NULL;
	newContainer->numNodes = 0;
	newContainer->numTraversals = 0;
    
    //post condition and invariance
	validateContainer(newContainer);
	
    return newContainer;

}// createContainer

// deallocate and destroy the Container so that we clear all memory
Container *destroyContainer( Container *theContainer )
{
    //pre-condition
    validateContainer(theContainer);
	clear(theContainer);
	free(theContainer);
    theContainer = NULL;
    
    //post condition
    validateContainer(theContainer);
	
    return theContainer;
}// destroyContainer

// clear all entries from the container, but don't destroy it
void clear( Container *theContainer )
{

    //to clear entries just free them
    
    //pre-condition
    validateContainer(theContainer);
	if(theContainer->head !=NULL)
	{
		while(theContainer->head != NULL)
		{
            validateContainer(theContainer);
			theContainer->traverseNode= theContainer->head;
			theContainer->head= theContainer->head->next;
			free(theContainer->traverseNode->item);
			free(theContainer->traverseNode);
            theContainer->traverseNode->item = NULL;
            theContainer->traverseNode = NULL;
			theContainer->numNodes--;
            validateContainer(theContainer);
		}
        
        theContainer->traverseNode = theContainer->head;
        theContainer->numTraversals = 0;
        
	}
    
    //post condition
    assert(theContainer->head == NULL);
    validateContainer(theContainer);
}// clear

void insertNode(Container *theContainer, char *new_string)
{
    //pre-condition
    validateContainer(theContainer);
    assert(theContainer !=NULL);
    assert(strlen(new_string) != 0);
    
	//allocate the node
    Node *newNode = malloc(sizeof(Node));
    int i = 0;
    while(new_string[i] != '\0')
        i++;

    //now allocate space for characters
    newNode->item = malloc ( i * sizeof(char));
    i=0;
    while(new_string[i] != '\0')
    {
            newNode->item[i] = new_string[i];
            i++;
    }
    newNode->item[i] = new_string[i];
    //now insert
    if(theContainer->head == NULL)
    {
        validateContainer(theContainer);
        assert(theContainer->numNodes == 0);
        newNode->next = NULL;
        theContainer->head = newNode;
        theContainer->traverseNode = theContainer->head;
        theContainer->numNodes = 1;
        theContainer->numTraversals = 1; //we have traversed to the first node
            
        //post condition
        assert(insert(theContainer, new_string));
        validateContainer(theContainer);
		
    }
    else
    {
            validateContainer(theContainer);
            newNode->next = theContainer->head;
            theContainer->head = newNode;
            theContainer->traverseNode = theContainer->head;
            theContainer->numTraversals=1;
            theContainer->numNodes++;
        
            //post condition
            assert(insert(theContainer, new_string));
            validateContainer(theContainer);
        }
}

// add an element to the beginning of the linked list
Boolean insert( Container *intoContainer, char *new_string )
{
	Boolean check = false;
	
    if(contains(intoContainer, new_string))
		check = true;
	
    return check;
}// insert

void deleteNode(Container *theContainer, char *target)
{
    
    //pre-condition
   // validateContainer(theContainer);
    assert(theContainer->numNodes > 0);
    
    //when we delete we are getting ride of the node
	//access the nodes
	//go to the top of the linkedlist
	theContainer->traverseNode = theContainer->head;
	theContainer->numTraversals = 1;	
	Node *previous = theContainer->traverseNode;

	while(theContainer->traverseNode !=NULL && strcmp(theContainer->traverseNode->item, target) !=0)
	{
        
		theContainer->traverseNode = theContainer->traverseNode->next;
		theContainer->numTraversals++;
	}
	if(strcmp(theContainer->traverseNode->item, target) == 0)
    {
		//we have found a node with that target
		//now delete it
		for(int i = 1; i<theContainer->numTraversals-1; i++)
            previous= previous->next;
        
        
        
        if(theContainer->numTraversals == 1) //the first item
        {
            
            theContainer->head = theContainer->head->next;
            free(theContainer->traverseNode->item);
            free(theContainer->traverseNode);
            theContainer->traverseNode=theContainer->head;
            theContainer->numNodes--;
            if(theContainer->numNodes == 0)
            {
                theContainer->head = NULL;
                theContainer->traverseNode = theContainer->head;
                theContainer->numTraversals = 0;
                
            }
            //post condition
            assert(delete(theContainer, target));
            validateContainer(theContainer);
        }
        else if(theContainer->traverseNode->next == NULL) //if we are at the last node
        {
            
            previous->next = NULL;
            free(theContainer->traverseNode->item);
            free(theContainer->traverseNode);
            theContainer->traverseNode= previous;
            theContainer->numNodes--;
            theContainer->numTraversals--;
            assert(delete(theContainer, target));
            validateContainer(theContainer);
        }
		else
		{
            
			//now link prev with traverse next
			previous->next= theContainer->traverseNode->next;
            
			//free contents of traverse
			free(theContainer->traverseNode->item);
			free(theContainer->traverseNode);
		
			//set curr to prev
			theContainer->traverseNode = previous;
			theContainer->numTraversals--;
			theContainer->numNodes--;
            
            //post condition
            validateContainer(theContainer);
            assert(delete(theContainer, target));
		}
	
    }
}
// remove an element with the given string
Boolean delete( Container *fromContainer, char *target )
{
    Boolean check = false;
    
    if(!contains(fromContainer, target))
        check = true;
    
    return check;
}// delete

// starts a list traversal by getting the data at head
char * firstItem( Container *inContainer ){
    
    //pre-condition
	validateContainer(inContainer);
    if(inContainer->head != NULL)
	{
        
		inContainer->traverseNode = inContainer->head;
		inContainer->numTraversals=1;
        validateContainer(inContainer);
	}
    //post condition
    validateContainer(inContainer);
	
    return inContainer->traverseNode->item;
}// firstItem


// increments the traversal and gets the data at the current traversal node 
char * nextItem( Container *inContainer ){
    
    
        //pre-condition
        assert(inContainer->traverseNode != NULL);
        validateContainer(inContainer);
    
    
        validateContainer(inContainer);
        if(inContainer->traverseNode !=NULL && inContainer->numNodes > 1)
        {
            validateContainer(inContainer);
            assert(inContainer->numTraversals >= 1);
            assert(inContainer-> numNodes > 1);
            
                if(inContainer->traverseNode->next != NULL)
                {
                inContainer->traverseNode = inContainer->traverseNode->next;
                inContainer->numTraversals++;
                validateContainer(inContainer);
                }
                else
                {
                    validateContainer(inContainer);
                    printf("There is no next item this function will return null");
                    return NULL;
                }
            
            validateContainer(inContainer);
            return inContainer->traverseNode->item;
                
        
            
        }
       else
       {
            //post condition
            assert(inContainer->numNodes <= 1);
            validateContainer(inContainer);
            printf("Warning there is only one node, This function will return null");
            return NULL;
       }
   // return inContainer->traverseNode->item;
    
}// nextItem

// tells us whether or not the given string is in the list
Boolean contains( Container *inContainer, char *target ){
    
    //pre-condition and invariance
    validateContainer(inContainer);
    Boolean check = false;
    
    if(inContainer->head != NULL)
    {
        inContainer->traverseNode = inContainer->head;
        inContainer->numTraversals =1;
    
    
        while (inContainer->traverseNode !=NULL)
        {
        
            if(strcmp(inContainer->traverseNode->item, target) == 0)
            {
                check = true;
            }
        
            inContainer->traverseNode = inContainer->traverseNode->next;
            inContainer->numTraversals++;
        
        }
        inContainer->traverseNode = inContainer->head;
        inContainer->numTraversals =1;
    }
    else
    {
        assert(inContainer->head == NULL);
    }
    
    //post condition
    validateContainer(inContainer);
    
    return check;
}// search

int size( Container *theContainer ){
    //pre-condition
    validateContainer(theContainer);
    
	int size;
	size = theContainer->numNodes;

    //post-condition
    validateContainer(theContainer);

	return size;
}
