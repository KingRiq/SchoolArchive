#include <stdio.h>
#include <string.h>
int main()
{
	char string1[] =  "Hello World\n";
	char* token = strtok(string1, " ");
	printf("%s",token);
	token = strtok(NULL, "-");
	printf("%s",token);
	return 0;
}


