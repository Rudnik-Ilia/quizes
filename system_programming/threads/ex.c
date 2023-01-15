#include <stdio.h>

#include <unistd.h>



void* Example()
{
    size_t x = 500;
    x += 100;

    printf("location of x: %p\n", &x);

    return *(void **)&x;
}
int Example2()
{
    size_t x = 500;
    x += 100;

    printf("location of x: %p\n", &x);

    return x;
}


int main()
{
    size_t b =  (int)Example();
    size_t a = Example2();


    printf("SUMM: %ld  loCation: %p\n", a + b, Example());
    return 0;
}
