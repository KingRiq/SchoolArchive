/*
 * main.c
 * COMP 2160 Programming Practices
 * Assignment 3
 *
 * Author Eriq Hampton
 * Automated testing for container.h and container.c
 *
 */
#include "container.h"
#include <stdio.h>
#include <string.h>
int main(void)
{
    printf("Testing Typical cases.\n");
    
    //creation
    Container *hello = NULL;
    hello = createContainer(hello);
    
    //insertion
    printf("\nTesting Insertion function\n");
    printf("\nEntering \'linked list\'\n");
    insertNode(hello, "linked list");
    if(size(hello) == 1 && insert(hello, "linked list") == 1)
        printf("\nThe test passed");
    else
        printf("\nThe test failed");
    
    
    printf("\n Testing Deletion function\n");
    printf("\nDeleting \'linked list\'\n");
    deleteNode(hello, "linked list");
    
    printf("\nTesting Size of 0 entries and deletion\n");
    if(size(hello) == 0 && delete(hello, "linked list") ==1)
        printf("\nThe test passed");
    else
        printf("\nThe test failed");
    
    //insertion of multiple items
    printf("\nTesting Multiple insertions\n");
    printf("\nEntering \'random\'\n");
    insertNode(hello, "random");
    
    printf("\nEntering \'words\'\n");
    insertNode(hello, "words");
    
    printf("\nEntering \'entered\'\n");
    insertNode(hello, "entered");
    
    printf("\nEntering \'into the list\'\n");
    insertNode(hello, "into the list");
    
    printf("\nTesting Size with multiple insertions\n");
    printf("\nSize should be 4\n");
    
    if(size(hello) == 4)
    {
        printf("\nThe test passed the size is = %d", size(hello));
        printf("\nEntering \'random\'\n");
    }
    else
    {
        printf("\nThe test failed the size is = %d" , size(hello));
        
    }
    //first and second item tests
    printf("\nChecking the first entry in the container \'into the list\n");
    printf("\nThe first item in this container = %s", firstItem(hello));
    if(strcmp("into the list", firstItem(hello)) == 0)
       printf("\nThe test passed");
    else
       printf("\nThe test failed");
    
    printf("\nChecking the second entry in the container \'entered\n");
    printf("\nThe second item in this container = %s", nextItem(hello));
    
    if(strcmp("entered ", nextItem(hello)) == 0)
        printf("\nThe test passed");
    else
        printf("\nThe test failed");
    
    printf("\n Clearing container");
   
    printf("testing complete");
	return 0;
}


void testContainer();


