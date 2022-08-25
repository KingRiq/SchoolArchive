/*
 * Container.h
 * COMP 2160 Programming Practices
 * Assignment 3
 * 
 * Author Eriq Hampton 
 * Header file for a Container
 */
#ifndef __CONTAINER_H
#define __CONTAINER_H
//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

typedef enum BOOL { false, true } Boolean;

typedef struct CONTAINER Container;

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------
void clear( Container *theContainer );
Container *createContainer();
void insertNode(Container *theContainer, char* string);
char *firstItem(Container *inContainer);
char *nextItem(Container *inContainer);
int size(Container *theContainer);
void deleteNode(Container *theContainer, char *target);
Boolean contains(Container * inContainer, char *target);
Boolean delete(Container *fromContainer, char *target);
Container *destroyContainer(Container *theContainer);
Boolean insert( Container *intoContainer, char *new_string );
#endif
