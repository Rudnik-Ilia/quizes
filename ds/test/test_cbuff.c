


#include <stdio.h>
#include <stdlib.h> /* malloc */
#include "utils.h"
#include "cbuff.h"



#ifndef NDEBUG
	typedef struct cbuff
	{
		int a;
		int b;
	}fake_cbuff_t;
#endif



int main()
{	
	size_t i;
	cbuff_t *buff = NULL;
	
	char arr[] = {'h', 'e', 'l','o'};
	char arr3[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'i', 'o'};	
	char de[4];
	
	#ifndef NDEBUG
		fake_cbuff_t *fcbuff = NULL;
		fcbuff = (fake_cbuff_t *)malloc(sizeof(fake_cbuff_t));
		fcbuff->a = 100;
		fcbuff->b = 200;
	#endif

	
	buff = CBuffCreate(10);
	printf("Test create new buff: \n");
	TEST_EQUAL(CBuffFreeSpace(buff), 10);
	TEST_EQUAL(CBuffCapacity(buff), 10);
	printf("-----------------------------------------\n");
	
	printf("Test write 4 byte: \n");
	TEST_EQUAL(CBuffWrite(buff, arr , 4), 4);
	TEST_EQUAL(CBuffFreeSpace(buff), 6);
	printf("-----------------------------------------\n");
	
	printf("Test read 3 byte: \n");
	TEST_EQUAL(CBuffRead(buff, de, 3), 3);
	TEST_EQUAL(CBuffFreeSpace(buff), 9);
	printf("-----------------------------------------\n");

	printf("Test for content: \n");
	for(i=0; i < 3; ++i)
	{
		TEST_EQUAL(de[i], arr[i]);
	}
	printf("-----------------------------------------\n");
	
	printf("Test write 9 byte: \n");
	CBuffWrite(buff, arr3 , 9);
	TEST_EQUAL(CBuffFreeSpace(buff), 0);
	TEST_EQUAL(CBuffIsEmpty(buff), 0);
	printf("-----------------------------------------\n");
	
	printf("Test write 33 byte: \n");
	TEST_EQUAL(CBuffRead(buff, de, 3), 3);
	TEST_EQUAL(CBuffFreeSpace(buff), 3);
	printf("-----------------------------------------\n");
	
	printf("Test write 144 byte: \n");
	TEST_EQUAL(CBuffWrite(buff, arr3 , 144), 3);
	printf("-----------------------------------------\n");
	
	#ifndef NDEBUG
		printf("Test for fake: \n");
		TEST_EQUAL(CBuffWrite(fcbuff, arr3, 5), -1);
		TEST_EQUAL(CBuffRead(fcbuff, de, 3), -1);
		free(fcbuff);
	#endif

	CBuffDestroy(buff);
	buff = NULL;
	
return 0;
}

