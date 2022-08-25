/*
 * main0.c
 * COMP 2160 Programming Practices
 * Assignment 4
 *
 * Author Eriq Hampton
 *
 * Tests the ObjectManager.c implementation using the ObjectManager.h interface
 */
#include "ObjectManager.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  
    char *ptr;
    int i;
    int id1,id2,id3,id4,id5,id6,id7;
    initPool();
  
    id1= insertObject(100);
    ptr = (char*)retrieveObject(id1);
    for (i = 0; i < 100; i++)
        ptr[i] = (char)(i%26 + 'A');
  
    id2 = insertObject(4000);
    id3 = insertObject(20200);
    dropReference(id3);
    id3 = insertObject(10);
    
    addReference(id3);
    addReference(id3);
    addReference(id3);
    
    id4 = insertObject(499000);
    id5 = insertObject(978);
    
    //check addresses and references
    dumpPool();
    
    //checking compact function here
    id6 = insertObject(11);
    
    //tests that insertion will fail
    id7 = insertObject(20190);
    
    //test insertion of memblock bigger than MEMORY_SIZE
    id7 = insertObject(MEMORY_SIZE+1);
  
    ptr = (char*)retrieveObject(id1);
    for (i = 0; i < 100; i++)
        fprintf(stderr,"%c",ptr[i]);
    fprintf(stderr,"\n");
  
    dumpPool();
    destroyPool();
    fprintf(stderr,"Process Complete!\n");
    return 0;
}

