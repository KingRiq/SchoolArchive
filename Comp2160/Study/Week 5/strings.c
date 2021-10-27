#include <stdio.h>
#include <string.h>
#define STR_LNGTH 500

typedef struct STRING
{
	char contents[STR_LNGTH];
	int length;
}my_string;

my_string make_string(char *);
char char_at(my_string, int);
void split(my_string, char *, my_string[]);

int main(void)
{
	my_string s1;
	int tokens = 2;
	my_string splitted_string[tokens];
	//s1.contents = "Monday";
	s1 = make_string("Monday");
	char c = char_at(s1,0);
	split(s1,"o",splitted_string);
	printf("%s %d %c\n", s1.contents, s1.length,c);
	for(int i=0;i<tokens;i++)
	{
		printf("token %d is %s\n",i,splitted_string[i].contents);
	}
	return 0;
}

my_string make_string (char *string)
{
	my_string s1;
	int i = 0;
	while(string[i] != '\0')
	{
		s1.contents[i] = string[i];
		i++;
	}
	s1.contents[i] = '\0';
	s1.length = i;
	return s1;
}


char char_at(my_string string, int loc)
{
    return string.contents[loc];
}


void split(my_string string, char *delim, my_string split_strings[])
{
    int index = 0;
    char *next;

    next = strtok(string.contents, delim);

    while (next != NULL)
    {
        my_string next_string = make_string(next);
        split_strings[index] = next_string;
        index++;
        next = strtok(NULL, delim);
    }
}
