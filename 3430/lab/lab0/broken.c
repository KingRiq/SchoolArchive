#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int number;
    char* name;
} Data;

/*
 * This function should create n Data structs, print out i for each one
 */
int main()
{
    
    Data* data[10];
    char a[] = "Hello";
    char *test;
    int length = sizeof(data)/sizeof(data[0]);

    for (int i = 0; i < length; i++)
    {
        data[i] = (Data *) malloc(sizeof(Data));
        data[i]->number = i;
        data[i]->name = (char*) malloc(sizeof(char*));
        // change this to sprintf, so line 24 can work
        sprintf(data[i]->name, "%d test", data[i]->number);
    }
    
    for(int i = 0; i < length; i++) {
        printf("The name of this data is '%s'\nAt index %d\n", data[i]->name,data[i]->number);
        free(data[i]->name);
        free(data[i]);
    }
    
}
