#include <stdio.h>

int main()
{
	int x = 1;
	int y = 2;
	int z = 3;

	int *a, *b;

	printf("this should store the address of y to pointer a\n");
	a = &y;
	printf("%p\n" , a);
	printf("address of y %p \n" ,&y);	
	
	printf("this should store the address of x inside b");
	b = &x;
	printf("%p\n" , b);
	printf("address of x %p \n" ,&x);
	
	printf("this should set the pointer b to point to z\n");
	*b = z;
	
	printf("%d\n", *b);
	printf("this is the value of z %d\n", z);
	
	printf("this should set x to equal whatever *a is pointing to\n");
	x = *a;

	printf("the value of x is %d\n" , x);

	char c = 'A';
	char *cPtr = NULL;

	cPtr = &c;
	printf("%c\n", c);
	*cPtr= 'B';
	printf("%c\n", c);
return 0;
}
