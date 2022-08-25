#include <stdio.h>

int my_strlen(char[]);
void my_strcpy(char[], char[]);

int main(void)
{
	char string[] = "peanut butter bread";
	char copy[my_strlen(string) + 1];
	my_strcpy(string, copy);
	int length = my_strlen(string);

	printf("%d\n", length);
	printf("%s %s\n", string, copy);

	return 0;
}

int my_strlen(char string[])
{
	int length = 0;
	while (string[length] != '\0')
	{
		length++;
	}
	return length;
}

void my_strcpy(char string[], char target[])
{
	int i;
	for (i = 0; i < my_strlen(string); i++)
	{
		target[i] = string[i];
	}
	target[i] = '\0'; // terminate string
}
