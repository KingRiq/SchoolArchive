#include <stdio.h>
int main(void)
{
        char array[] = "zzallstring";
        printf("%p\n",&array);
        for (int i = -1; i< 15;i++)
        {
                printf("%d -> %x %c\n", i, array[i], array[i]);
        }
        return 0;
}
