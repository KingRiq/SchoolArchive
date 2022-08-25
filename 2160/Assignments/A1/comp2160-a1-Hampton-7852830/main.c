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
int main(void)
{
    printf("Testing Typical cases.\n");
    
    //creation
    Container *hello;
    hello = createContainer(hello);
    
    //insertion
    insertNode(hello, "linked list");
    if(size(hello) == 1 && insert(hello, "linked list") == 1)
        printf("the test passed");
    else
        printf("the test failed");
    
    
    //deletion
    //deleteNode
    
	
	return 0;
}


void testContainer();


