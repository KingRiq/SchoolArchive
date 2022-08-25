/*
 * ObjectManager.c
 * COMP 2160 Programming Practices
 * Assignment 4
 *
 * Author Eriq Hampton
 * Implementation file of a object manager
 * Uses garbage collection for dereferenced memory
 */
#include "ObjectManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// tracks the next reference (ID) to use, we start at 1 so we can use 0 as the NULL reference
static Ref nextRef = 1;

// A Memblock holds the relevent information associated with an allocated block of memory by our memory manager
typedef struct MEMBLOCK MemBlock;


// information needed to track our objects in memory
struct MEMBLOCK
{
  int numBytes;    // how big is this object?
  int startAddr;   // where the object starts
  Ref ref;         // the reference used to identify the object
  int count;       // the number of references to this object
  MemBlock *next;  // pointer to next block.  Blocks stored in a linked list.
};


// The blocks are stored in a linked list where the start of the list is pointed to by memBlockStart.
static MemBlock *memBlockStart; // start of linked list of blocks allocated
static MemBlock *memBlockEnd;   // end of linked list of blocks allocated
static int numBlocks;            // number of blocks allocated

// our buffers.  This is where we allocate memory from.  One of these is always the current buffer.  The other is used for swapping
//during compaction stage.

static unsigned char buffer1[MEMORY_SIZE];
static unsigned char buffer2[MEMORY_SIZE];

// points to the current buffer containing our data
static unsigned char *currBuffer = buffer1;

// points to the location of the next available memory location
static int freeIndex = 0;

// checks if the buffer has enough space
int checkBuffer(int spaceLeft, int spaceReq);

// Garbage Collection implementation
void compact();

// invariant checker
void checkState();

// performs required setup
void initPool()
{
    // Ref already set to 1
    // buffers already set and free index already set
    memBlockStart = NULL;
    memBlockEnd = NULL;
    checkState();
    
    
}

// performs required clean up
void destroyPool()
{
    checkState();
    MemBlock *curr = memBlockStart;
    
    while(memBlockStart != NULL)
    {
        memBlockStart = memBlockStart->next;
        free(curr);
        curr = memBlockStart;
        numBlocks--;
    }
    memBlockEnd = memBlockStart;
    assert(memBlockStart == NULL);
    checkState();
}

// Adds the given object into our buffer. It will fire the garbage collector as required.
// We always assume that an insert always creates a new object...
// On success it returns the reference number for the block allocated.
// On failure it returns NULL_REF (0)
Ref insertObject( const int size )
{
    // pre condition
    assert(size > 0);
    checkState();
    
    Ref result = NULL_REF;
    MemBlock *newMemBlock = NULL;
    MemBlock *curr = memBlockStart;
    int spaceLeft = MEMORY_SIZE;
    
    // allocation of new memBlock
    newMemBlock = (MemBlock *) malloc (sizeof(MemBlock));
    newMemBlock->next = NULL;
    assert(newMemBlock != NULL && newMemBlock->next == NULL);
    
    if(size > MEMORY_SIZE)
    {
        // if size is too big
        assert(size > MEMORY_SIZE);
        checkState();
        
        printf("\nThe size entered is too big for our buffer");
        printf("\nInsertion Failed");
        
        // insertion failed free the allocated memblock
        free(newMemBlock);
        
    }
    else if(curr == NULL && memBlockStart == NULL)
    {
        
        if(checkBuffer(spaceLeft, size) == 1)
        {
            assert(size <= MEMORY_SIZE);
            checkState();
            
            // starting conditions
            newMemBlock->ref = nextRef++;
            newMemBlock->count = 1;
            newMemBlock->numBytes = size;
            newMemBlock->startAddr = 0;
            freeIndex = newMemBlock->startAddr+newMemBlock->numBytes;

            // insert at the top
            memBlockStart = newMemBlock;
            memBlockEnd = memBlockStart;
            newMemBlock->next = NULL;
            
            
            result = newMemBlock->ref;
            memset(&currBuffer[newMemBlock->startAddr],'E',newMemBlock->numBytes);
            numBlocks++;
            spaceLeft = MEMORY_SIZE -(newMemBlock->numBytes);
            printf("You have %d bytes left of space", spaceLeft);
            
            assert(memBlockStart->next == NULL);
            checkState();
        }
    }
    else// not the first memblock
    {
        assert(curr != NULL);
        checkState();
        
        spaceLeft = MEMORY_SIZE - freeIndex;
        
        if(checkBuffer(spaceLeft,size) == 1)
        {
            newMemBlock->ref = nextRef++;
            result = newMemBlock->ref;
            newMemBlock->numBytes = size;
            newMemBlock->count = 1;
            newMemBlock->startAddr = freeIndex;
            
            // insert at the end!
            memBlockEnd->next = newMemBlock;
            memBlockEnd= newMemBlock;
            numBlocks++;
            freeIndex = newMemBlock->startAddr+newMemBlock->numBytes;
            memset(&currBuffer[newMemBlock->startAddr],'H',newMemBlock->numBytes);
            spaceLeft = MEMORY_SIZE - freeIndex;
            printf("\nYou have %d bytes left of space", spaceLeft);
            
            assert(memBlockEnd->next == NULL);
            checkState();
        }
        else // we need to try to compact
        {
            assert(checkBuffer(spaceLeft,size) == 0);
            checkState();
            
            compact();
            
            curr = memBlockStart;
            while(curr->next != NULL)
            {
                curr = curr->next;
            }
            
            memBlockEnd = curr;
            spaceLeft = MEMORY_SIZE - (memBlockEnd->startAddr + memBlockEnd->numBytes);
            
            
            // recursively call self to see if insertion is possible
            if(checkBuffer(spaceLeft, size) == 1)
            {
                insertObject(size);
            }
            else
            {
                checkState();
                printf("\nWe were not able to allocate the space needed");
                printf("\nInsertion Failed");
                free(newMemBlock);
            }
        }
    }
    
    
    // post condition
    assert(result >= 1 || result == 0);
    checkState();
    return result;
}

// returns a pointer to the object being requested
void *retrieveObject( const Ref ref )
{
    
    unsigned char *object = NULL;
    // pre-condition
    checkState();
    assert(ref > 0);
    
    if( ref > 0)
    {
        MemBlock *curr = memBlockStart;
        
        while(curr != NULL)
        {
            checkState();
            if(curr->ref == ref)
            {
                object = &currBuffer[curr->startAddr];
            }
            curr = curr->next;
        }
        // post condition
        assert(curr == NULL);
        checkState();
    }
    return object;
  
}

// update our index to indicate that we have another reference to the given object
void addReference( const Ref ref )
{
    // pre condition
    assert(ref > 0);
    checkState();
    
    if(ref > 0)
    {
        MemBlock *curr = memBlockStart;
    
        while(curr != NULL)
        {
            if(curr->ref == ref)
                curr->count++;
            
                curr = curr->next;
            
        }
        // post condition
        checkState();
        assert(curr == NULL);
    }
}

// update our index to indicate that a reference is gone
void dropReference( const Ref ref )
{
    // a ref # cannot be 0 or it is null by definition
    // pre condition
    checkState();
    assert(ref > 0);
    
    if(ref > 0)
    {
        MemBlock *curr = memBlockStart;
        MemBlock *prev = NULL;
        while(curr != NULL)
        {
            if(curr->ref == ref)
            {
                if(curr->count <= 1)
                {
                    
                    if(curr == memBlockStart)
                    {
                        // the first node needs to be deallocated
                        memBlockStart = memBlockStart->next;
                        free(curr);
                        curr = memBlockStart;
                    }
                    else
                    {
                        assert(prev != NULL);
                        // unlink and free
                        prev->next = curr->next;
                        free(curr);
                        curr = prev;
                    }
                    numBlocks--;
                }
                else
                {
                    curr->count--;
                }
                
            }
            prev = curr;
            curr = curr->next;
            
        }
        // update last memblock for safety
        memBlockEnd = prev;
        
        // post condition
        assert(curr == NULL);
        checkState();
    }
}

// performs our garbage collection
void compact()
{
    // pre condition
    checkState();
    
    MemBlock *curr = memBlockStart;
    MemBlock *prev = NULL;
    freeIndex = 0;
    int spaceLeft = 0;
    int garbage = memBlockEnd->startAddr + memBlockEnd->numBytes;
    
    while(curr != NULL)
    {
        checkState();
        if (currBuffer == buffer1)
        {
            checkState();
            memcpy(&buffer2[freeIndex], &currBuffer[curr->startAddr], curr->numBytes);
        }
        else
        {
            checkState();
            memcpy(&buffer2[freeIndex], &currBuffer[curr->startAddr], curr->numBytes);
        }
        
        // if the curr memory block is referenced we do not need to throw it away
        assert(curr->count > 0);
        
        // currbuffer start add is now the new start point
        currBuffer[freeIndex] = currBuffer[curr->startAddr];
        curr->startAddr = freeIndex;
        garbage = garbage-curr->numBytes;
        spaceLeft += curr->numBytes;
        freeIndex = curr->startAddr+curr->numBytes;
        prev = curr;
        curr = curr->next;
    }
    
    if(currBuffer == buffer1)
        currBuffer = buffer2;
    
    else
        currBuffer = buffer1;
    
    checkState();
    
    // print log
    printf("\n----------------------------------------------");
    printf("\nYou are out of memory");
    printf("\nAttempting to compact memory for insertion!");
    printf("\nTotal number of objects = %d", numBlocks);
    printf("\nTotal number of current bytes in use = %d\n", spaceLeft);
    printf("%d bytes Collected!\n", garbage);
    printf("----------------------------------------------\n");
}

void dumpPool()
{
    checkState();
    MemBlock *curr = memBlockStart;
    int i = 1;
    
    // print log
    printf("\n----------------------------------------------");
    
    if(curr == NULL)
    {
        printf("\nThe object manager has no memory blocks");
    }
    
    
    while(curr != NULL)
    {
        checkState();
        printf("\nPrinting MemBlock %d", i);
        printf("\nREF #: %lu", curr->ref);
        printf("\nSIZE IN BYTES: %d", curr->numBytes);
        printf("\nCOUNT: %d",curr->count);
        printf("\nStarting ADDRESS: %d\n", curr->startAddr);
        
        
        curr = curr->next;
        i++;
    }
    printf("\n----------------------------------------------\n");
    
    assert(curr == NULL);
    checkState();
}

// boolean function that returns true if there is space in our buffer. False if it does not.
int checkBuffer(int spaceLeft, int spaceReq)
{
    
    int check = 0;
    
    if(spaceReq <= spaceLeft)
    {
        check = (spaceReq <= spaceLeft);
    }
    assert(check == 1 || check == 0);
    return check;
}


// invariant checker
void checkState()
{
    MemBlock *curr = memBlockStart;
    MemBlock *prev = NULL;
    int blockCount = 0;
    
    // check pointers
    if (numBlocks == 0)
        assert(memBlockStart == NULL && memBlockEnd == NULL);
    
    else if (numBlocks == 1)
        assert ( memBlockStart ->next == NULL && memBlockEnd->next == NULL);
    
    else
    {
        assert (memBlockStart != NULL && memBlockStart->next != NULL);
        assert(numBlocks != 0);
    }
    
    // check numBlocks is correct
    while (curr)
    {
        blockCount++;
        prev = curr;
        
        assert(curr->count != 0);
        curr = curr->next;
        
        // check ref IDs
        if (curr != NULL)
        {
            // by definition IDs are in order
            assert (prev->ref < curr->ref);
            prev = curr;
        }
        
    }
    assert (blockCount == numBlocks);
}
