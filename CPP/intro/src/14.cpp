
#include <stdio.h>


// const int s = 3;
// const int x = 3;
int main()
{
    const int i = 3;
    int i1 = 9;

    int *ip = (int *)(&i);
    *ip = 5;
    int *ip1 = (int *)(&i1);
    *ip1 = 5;
   

    printf("%d %d\n", i, *ip);

    return 0;
}
