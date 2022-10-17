#include <stdio.h>
#include <stdlib.h>



void MissingNum(int arr[], int n)
{
	int i = 0;
	int tmp = 0;
	int min_sum = 0;
	int max_sum = 0;
	int sum3 = 0;

	for (i = 0; i < n - 2; ++i)
	{
		min_sum += arr[i];
	}
	for (i = 0; i < n; ++i)
	{
		max_sum += i;
	}
	max_sum += n;
	
	tmp = max_sum - min_sum;
	
	tmp = tmp % 2 == 0 ? tmp / 2 : (tmp + 1) / 2;

	for (i = 1; i < tmp; ++i)
	{
		sum3 += i;
	}

	for (i = 0; i < n - 2; ++i)
	{
		if (arr[i] < tmp)
		{
			sum3 -= arr[i];
		}
	}
	
	tmp = max_sum - min_sum - sum3;
	
	printf("%d %d\n", sum3, tmp);

}

static void TwoMissing2(int *arr, size_t n)
{
	int i = 0;
	int j = 0;
	int *tmp = (int*)malloc(sizeof(int) * n);
	
	for(j = 1; j < (int)n; ++j)
	{
		
		if(j != arr[i])
		{
			printf("%d\n", j);
			++i;
		}
		else
		{
			++i;
		}
	}
}



int main()
{
	int arr[] = {1,2,3,6,7};
	size_t len = sizeof(arr)/sizeof(int);
	
	/*
	MissingNum(arr, len+2);
	
	
	*/
	 TwoMissing2(arr, len);

return 0;
}





