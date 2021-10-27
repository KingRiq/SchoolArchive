#include <stdio.h>
#include <assert.h>


#define MAXN 50
#define s binarysearch

typedef int DataType;
int binarysearch(DataType t);
int sorted();
//void test();
int n;
DataType x[MAXN];

int main(void)
{
        int t;
        while(scanf("%d %d" , &n, &t) != EOF)
        {
	int i;
	/* test value of n */
	for(n=0; n<= MAXN; n++)
	{
		printf("n = %d\n", n);
printf("I worked\n");
	}
	
	/* test distinct elements (plus one at the end) */
	for(i=0; i  <= n; i++)
	{
		x[i]= 10*i;
printf("I worked\n");
	}
	for(i=0; i < n; i++)
	{   
		assert(s(10*i) == i);
		assert(s(10*i -5) == -1);
printf("I worked\n");	
	}
	assert(s(10*n -5) ==-1);
	assert(s(10*n) ==-1);
printf("I worked\n");	
	/* test equal elements */
	for(i=0; i<n; i++)
	{	
		x[i]=10;
	}
	if(n==0)
	{
		assert(s(10) == -1);
	}
	else
	{
		assert(0<= s(10) && s(10) < n);
	}
	assert(s(5) == -1);
	assert(s(15) == -1);
printf("doing the real search now\n");
                for(int i=0; i < n; i++)
                {
                        x[i] = 10*i;
                }
                assert(sorted());
		printf(" %d\n", binarysearch(t));
        }
}

/*return any position if t in sorted x[0..n-1] or -1 if t is not present */

int binarysearch(DataType t)
{
        int l, u, m, oldsize, size=0;
        l=0;
        u=n-1;
	size= n+1;
        oldsize = size;
	size = u-1+1;
	assert(size < oldsize);
	while(l<= u)
        {
                m = (l+u)/2;
                if (x[m] < t)
                {
                        l = m+1;
                }
                else if (x[m] == t)
                {
               		assert(x[m] ==t);   
			assert(0 <= m && m < n && x[m] == t);
			return m;
                }
                else
                {
                        u=m-1;
                }
        }

	assert(x[u] < t && x[u+1] > t);
	assert((u < 0 || x[u] <t) && (u+1 >= n || x[u+1] > t));
        return -1;
}

int sorted()
{
	int i;
	for(i=0; i <n-1; i++)
		if(x[i] > x[i+1])
		{
			return 0;
		}
	return 1;
}



