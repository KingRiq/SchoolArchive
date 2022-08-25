#include <stdio.h>
#include<string.h>
int main(void)
{
        char array[] = "elephant";
        char array2[]= "horse";
        char array3[6];
        //where in memory (start address)
        printf("%p\n",&array);
        printf("%s\n", array);
        
		array[8]='s';
        
	printf("%s\n",array);

	array2[2]='B';        
	printf("%s\n",array2);
        
		int cmp;
        cmp = strcmp("e","a");
        printf("strcmp returns %d\n",cmp);
        
		strcpy(array3,array2);
        for(int i=0;i<strlen(array2)+1;i++)
        {
                array3[i]=array2[i];
        }
        printf("%s %s\n",array2,array3);

       /* for (int i = -1; i< 15;i++)
        {
                printf("%d -> %x %c\n", i, array[i], array[i]);
        }*/
        return 0;
}
