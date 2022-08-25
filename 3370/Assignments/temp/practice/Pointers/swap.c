#include<stdio.h>

void swap(int *x, int *y);

int main(void)
{
	int x = 20;
	int y = 30;
	printf("%d %d\n", x,y);
	swap(&x, &y); //
	printf("%d %d\n", x,y);
	return 0;
}

void swap(int *x, int *y)
{
	int tmp = *x; //indirection modifer
	*x = *y; //whatever y is pointing to is now x
	*y = tmp; 
}
