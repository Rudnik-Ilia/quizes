
#include <stdio.h>
#include <stdlib.h>

void SortArray(int arr[], size_t size)
{
	int tmp = 0;
	size_t i = 0;
	size_t j = 0;
	
	for(i = 0, j = size - 1; i < j;)
	{
		if(arr[i] != 0 && arr[j] != 1)
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
		if(0 == arr[i])
		{
			++i;
		}
		if(1 == arr[j])
		{
			--j;
		}
	
	}

}





int main()
{
	int arr[] = {1,0,1,0,0,1,0};
	
	SortArray(arr, 7);
	
	

return 0;
}
