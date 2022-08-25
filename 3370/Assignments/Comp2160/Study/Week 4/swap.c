#include <stdio.h>

void swap(int *x, int *y);

int main(void)
{
    int x = 34;
    int y = 6;

    int arr[3] = { 10, 55, 21 };

    printf("x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("x=%d, y=%d\n", x, y);

    printf("arr[1]=%d, arr[2]=%d\n", arr[1], arr[2]);
    swap(&arr[1], &arr[2]);
    printf("arr[1]=%d, arr[2]=%d\n", arr[1], arr[2]);

    return 0;
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
