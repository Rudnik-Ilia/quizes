
#include <stdio.h>
#include <stdlib.h>

int GLOBAL = 300;
static int ST_GLOBAL = 0;

static void func_one(int x)
{
	int a = 100;
	char b = 'b';
	static int c = 0;
	
	long arr[100];
	
	void * ptr = malloc(50);
	
	printf("%d\n", c);
	++c;
	func_one(x);		
}
void func_two(int x)
{
	int a = 100;
	char b = 'b';
	static int c = 0;
	
	long arr[100];
	
	void * ptr = NULL;
	void * ptr2 = NULL;
	int * ptr3 = NULL;
	
	
	
	printf("%d\n", c);
	++c;
	func_two(x);
}



int main()
{
	int one = 1;
	/*
	func_two(one);
	*/
	func_one(one);
	
	

return 0;
}


