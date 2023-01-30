#include <stdio.h>

struct Point
{
    int m_x;
    int m_y;
};

struct A
{

};

struct B
{
    int x;
    int y;
    struct Point p;
};

struct B BCtor()
{

/*
	struct B b = {.x = 5, .y = 7, .p = {3, 3}};
*/

	struct B b = {5, 7, {3, 3}};
	return b;
}
struct Point PointCtor()
{   
    struct Point this = {.m_x = 0, .m_y = 0};
    // struct Point this = {0,0};
    return this;
}

struct B BCctor(struct B other_)
{
    /*
    
	struct B this = {.x = other_.x, .y = other_.y, .p = other_.p};
    */

	struct B this = {other_.x, other_.y, other_.p};
	return this;
}

void BDtor()
{
    printf("Im desrurctor B");
};

int main()
{
    struct A a;
  
	struct B b = BCtor();

	struct B b2 = BCctor(b);


    printf("%d - %d\n", b.x, b.y);
    printf("%d - %d\n", b.p.m_x, b.p.m_y);


    printf("%d - %d\n", b2.x, b2.y);
    printf("%d - %d\n", b2.p.m_x, b2.p.m_y);


    return 0;
}