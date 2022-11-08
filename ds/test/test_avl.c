#include <stdio.h>

#include "avl.h"



int Cmp(const void * p1, const void * p2)
{
	return (*(int*)p1 - *(int*)p2);
}

int main()
{
	avl_t *avl = AVLCreate(Cmp);



return 0;
}
