#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Base B;
typedef struct Derived D;

struct Base
{
    int x;
    int y;
};

struct Derived
{
    B b;
    int z;
};


B BCtor(int a, int b)
{
    B this = {.x = a, .y = b};
    return this;
}

D DCtor(int a, int b, int c)
{
    D this = {.b = BCtor(a, b), .z = b};
    return this;
}

B BCopy(B other_)
{
    B this = {.x = other_.x, .y = other_.y};
    return this;
}

D DCopy(D other_)
{
    D this = {.b = other_.b, .z = other_.z};
    return this;
}

B* BAss(B *b)
{
    B* tmp  = malloc(sizeof(B));
    memcpy(b, tmp, sizeof(B));
    return tmp;
}
D* DAss(D *d)
{
    D* tmp  = malloc(sizeof(D));
    memcpy(tmp, d, sizeof(D));
    return tmp;
}




int main()
{


    D d = DCtor(1,2,3);

    D d1 = DCopy(d);

    printf("%d - %d - %d\n", d.b.x, d.b.y, d.z);
    printf("%d - %d - %d\n", d1.b.x, d1.b.y, d1.z);

    D *d2 = DAss(&d1);

    printf("%d - %d - %d\n", d2->b.x, d2->b.y, d2->z);

    return 0;
}