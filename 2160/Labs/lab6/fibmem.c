#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10
long  small[MAX_SIZE];
long fib(int n)
{
  long result;

  if (n==0)
    result = 0;
  else if (n==1 || n==2)
    result = 1;
  else if (n< MAX_SIZE && small[n] != -1)
  {
	result = small[n];	
  }
  else
  {
	small[n] = fib(n-1) + fib(n-2);
	result = small[n];
  }
  return result;
}

int main( int argc, char *argv[] )
{

	for(int i = 0; i < MAX_SIZE; i++)
		small[i] = -1;
  // we really should check the input...
  int fibNum = atoi(argv[1]);

  printf("The %d Fibonacci number is %ld\n", fibNum, fib(fibNum));

  return EXIT_SUCCESS;
}


