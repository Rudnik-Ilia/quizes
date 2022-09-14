


#include <stdio.h>
#include "utils.h"
#include "cbuff.h"



int main()
{	
	size_t i;
	cbuff_t *buff = NULL;
	char arr[] = {'h', 'e', 'l','o'};
	char arr3[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'i', 'o'};	
	char de[4];
	
	buff = CBuffCreate(10);
	printf("%ld\n", CBuffFreeSpace(buff));
	CBuffWrite(buff, arr , 4);
	printf("%ld\n", CBuffFreeSpace(buff));
	
	
	TEST(CBuffRead(buff, de, 3), 3);
	printf("%ld\n", CBuffFreeSpace(buff));
	
	printf("Test for contain: \n");
	for(i=0; i < 3; ++i)
	{
		TEST(de[i], arr[i]);
	}
	CBuffWrite(buff, arr3 , 9);
	printf("%ld\n", CBuffFreeSpace(buff));
	TEST(CBuffIsEmpty(buff), 1);
	
	CBuffRead(buff, de, 3);
	printf("%ld\n", CBuffFreeSpace(buff));
	
	TEST(CBuffWrite(buff, arr3 , 144), 3);
	

	CBuffDestroy(buff);
return 0;
}

