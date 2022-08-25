#include <stdio.h>

int main(void)
{
    int age;
    float money;
    char name[10];
    int ret;

    printf("Enter your age, then money:\n");
    ret = scanf("%d %f %s", &age, &money, name);

    if ( ret < 3 )
    {
        printf("You didn't enter the right format\n");
    }
    else
    {
        printf("You entered:\n");
        printf("\tage: %d\n", age);
        printf("\tmoney: %f\n", money);
        printf("\tname: %s\n", name);
    }

    return 0;
}
