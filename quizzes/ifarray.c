#include <stdio.h>



int foo(int *arr, int len, int num)
{
	int i = 0;
	int match = 0;
	for(; i < len; ++i)
	{
		match = match + (arr[i] == num);
	}
	return !!match;
}




int main()
{
	int arr[] = {2,3,5,6,7,8,9,34,22,7,99,11,3,4,98,44};
	int a = 23;
	printf("%d\n", foo(arr, 16, 46));
	printf("%d\n", !a);
	
	

return 0;
}
