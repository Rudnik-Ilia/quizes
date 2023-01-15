#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

void Flip(int* x, int* y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
void Flip2(int** x, int** y)
{
    int *tmp = *x;
    *x = *y;
    *y = tmp;
}
void Flip3(int* x, int* y)
{
    void *tmp = malloc(4);
    memcpy(tmp, x, 4);
    memcpy(x, y, 4);
    memcpy(y, tmp, 4);
    
}

int main()
{
    int a = 10;
    int b = 20;

    int* pa = &a;
    int* pb = &b;

   

    // Flip(&a, &b);
    // Flip2(&pa, &pb);
    Flip3(pa, pb);

    cout<< *pa << ' ' << *pb << endl;



    return 0;
}