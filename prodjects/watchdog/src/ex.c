#include <stdio.h>
#include <stdlib.h>

void Swap(int **x, int **y)
{
    int tmp = **x;
    *x = *y;
    *y = &tmp;
}


int main()
{
    int a = 10;
    int b = 20;

    int *pa = &a;
    int *pb = &b;

    Swap(&pa, &pb);

    printf("%d - %d\n", *pa, *pb);

return 0;
}