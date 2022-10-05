#include <stdio.h>



char *Add(char *num1, char *num2, char *output, size_t l1, size_t l2, size_t l3)
{
	char sum;
	int memo = 0;
	int len1 = 0;
	int len2 = 0;
	int len3 = l3;
	char *temp = NULL;
	
	output[len3-1] = '\0';
	
	if(l2 > l1)
	{
		len1 = l2;
		len2 = l1;
		temp = num1;
		num1 = num2;
		num2 = temp;
	}
	else
	{
		len2 = l2;
		len1 = l1;
	
	}
	
	while(len2)
	{	
		sum = (num1[len1 - 1] - 48 ) + (num2[len2 - 1] - 48) + memo;
		output[len3 - 2] = (sum % 10 + 48);
		--len1;
		--len2;
		--len3;
		if(sum > 9)
		{
			memo = sum / 10;
		}
		else
		{
			memo = 0;
		}		
	}
	while(len1)
	{
		output[len3 - 2] = num1[len1 - 1];
		--len3;
		--len1;
	}
	return output;	
}

int main()
{
	char output[16] = {0}; 
	
	printf("%s\n", Add("99770", "7894418940" ,output, 5, 10, 11) );
	return 0;
}
