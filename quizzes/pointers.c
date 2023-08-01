#include <stdio.h>


void Swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void Swap3(int **x, int **y)
{
    int tmp = **x;
    *x = *y;
    *y = &tmp;
}


int main()
{

    int a = 10;
    int b = 20;

    int* p_a = NULL;
    int* p_b = NULL;

    p_a = &a;
    p_b = &b;

    printf("%d - %d\n", *p_a, *p_b );
    Swap3(&p_a, &p_b);

    printf("%d - %d\n", *p_a, *p_b );



    return 0;
}