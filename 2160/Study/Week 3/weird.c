#include <stdio.h>

// run this code and see how we can write
// **way** past the end of the arrays, clobber
// each array (write into arrays that are *not* arr3)
// and eventually crash.
int main(void)
{
	char arr1[] = "hello";
	char arr2[3] = {'h', 'i', '\0'};
	char arr3[] = "world";

	int ch = getchar();
	int count = 0;
	while (ch != EOF)
	{
		printf("%s %s %s\n", arr1, arr2, arr3);
		arr3[count++] = ch;
		printf("%d" , count);
		ch = getchar();
	}
	return 0;
}
