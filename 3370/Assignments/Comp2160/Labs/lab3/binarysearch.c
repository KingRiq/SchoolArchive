//-----------------------------------------
// NAME: Eriq Hampton
// STUDENT NUMBER: 7852830
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Prof Saifur
// LAB 3: Exercise 1
//
// REMARKS:This program does a binary search
// 
//-----------------------------------------
#include <stdio.h>
#include <assert.h>
#define MAXN 1000
#define s binarysearch

typedef int DataType;
int binarysearch(DataType t);
int sorted();
void test();
int n;
DataType x[MAXN];

int main(void)
{
        int t;
	test();
        while(scanf("%d %d" , &n, &t) != EOF)
        {
		
                for(int i = 0; i < n; i++)
                {
                        x[i] = 10*i;
                }
                assert(sorted());
		printf("%d\n", binarysearch(t));
        }
}

/*return any position if t in sorted x[0..n-1] or -1 if t is not present */
int binarysearch(DataType t)
{
        int lower, upper, middle, oldsize, size=0;
        lower = 0;
        upper = n-1;
	size = n+1;
        oldsize = size;
	size = upper-1;

	while(lower <= upper)
        {
                middle = (lower + upper)/2;
                if (x[middle] < t)
                {
                        lower = middle+1;
                }
                else if (x[middle] == t)
                {
               		assert(x[middle] ==t);   
			assert(0 <= middle && middle < n && x[middle] == t);
			return middle;
                }
                else
                {
                        upper = middle-1;
                }
        }

	//assert(x[upper] < t && x[upper+1] > t);
	assert((upper < 0 || x[upper] < t) && (upper+1 >= n || x[upper+1] > t));
	assert(size < oldsize);
        return -1;
}

int sorted()
{
	int i;

	for(i = 0; i < n-1; i++)
	{
		if(x[i] > x[i+1])
		{
			return 0;
		}
	}
	return 1;
}

void test()
{

	int i;

	/* test value of n */
	for(n = 0; n <= MAXN; n++)
	{
		printf("n = %d\n", n);
	}
	
	/* test distinct elements (plus one at the end) */
	for(i = 0; i <= n; i++)
	{
		x[i] = 10*i;
	}
	
	for(i = 0; i < n; i++)
	{
		assert(s(10*i) == i);
		assert(s(10*i-5) == -1);
	}
	assert(s(10*n-5) == -1);
	assert(s(10*n) == -1);
	
	/* test equal elements */
	for(i = 0; i < n; i++)
	{	
		x[i] = 10;
	}

	if(n == 0)
	{
		assert(s(10) == -1);
	}

	else
	{
		assert(0 <= s(10) && s(10) < n);
	}

	assert(s(5) == -1);
	assert(s(15) == -1);
}
