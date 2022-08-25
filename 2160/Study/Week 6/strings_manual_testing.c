#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
//#define STR_LNGTH 500 
typedef struct STRING
{
	char *contents;
	int length;
}my_string;

my_string *make_string(char *);
char char_at(my_string *, int);
void split(my_string *, char *, my_string *[]);
void destroy_string(my_string*);
void checkString(my_string *);
int main(void)
{
	#define MAX_INPUT_SIZE 80
    char input[MAX_INPUT_SIZE];
    char delim[MAX_INPUT_SIZE];
    int expected_tokens = -1;

    printf("Enter the input string: ");
    fgets(input, MAX_INPUT_SIZE, stdin);
    printf("Enter the delimiter: ");
    fgets(delim, MAX_INPUT_SIZE, stdin);
    printf("Enter the expected number of tokens: ");
    scanf("%d", &expected_tokens);

    my_string *tokens[MAX_INPUT_SIZE];
    my_string *to_split = make_string(input);

    split(to_split, delim, tokens);

    printf("Here's the output:\n");
    for (int i = 0; i < expected_tokens; i++)
    {
        printf("%d\t%s\n", i, tokens[i]->contents);
    }
    return 0;


}
void destroy_string(my_string *string)
{
	free(string->contents);
	free(string);
}


char char_at(my_string *string, int loc)
{
	char value;
	//pre-condition
	checkString(string);
	assert(loc >= 0);
	assert(loc < string -> length);
	value =  string->contents[loc];
	//post-condition
	assert(strchr(string->contents, value)!= NULL);
	return value;
}
void split(my_string *string, char *delim, my_string *split_string[])
{
	int index = 0;
	char *next;
	next = strtok(string->contents,delim);
	while(next != NULL)
	{
		my_string *next_string = make_string(next);
		split_string[index++] = next_string;
		next = strtok(NULL,delim);		
	}
}


my_string* make_string(char *string)
{
	my_string *s2;
	int i=0;
	// ---- pre-condition
	assert(string != NULL);
	s2 = malloc(sizeof(my_string));
	while(string[i]!='\0'){
		i++;
	}
	s2->contents = malloc (i * sizeof(char));
	i=0;
	while(string[i]!='\0')
	{
		s2->contents[i] = string[i];
		i++;
	}
	s2->contents[i]='\0';
	s2->length = i;
	// --- post-condition
	checkString(s2);
	return s2;
}
//invariants
void checkString(my_string *string)
{
	assert(string->contents != NULL);
	assert(string->length > 0);
	assert(string->contents[string->length] == '\0');
}
