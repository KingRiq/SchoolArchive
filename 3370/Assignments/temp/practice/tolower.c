#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int letter;

	letter = getchar();

	while( letter != EOF  ) // while I get input
	{
		putchar( tolower( letter ) );
		letter = getchar();
	}
	return 0;
}
