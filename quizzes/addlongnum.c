#include <stdio.h>



char *Add(char *num1, char *num2, char *output)
{
	int memo = 0;
	char sum;
	int len1 = 10;
	int len2 = 5;
	int len3 = 16;
	while(len2)
	{	
		sum = (num1[len1 - 1] - 48 ) + (num2[len2 - 1] - 48) + memo;
		output[len3 - 1] = (sum % 10 + 48);
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
		output[len3 - 1] = num1[len1 - 1];
		--len3;
		--len1;
	}
	return output;	
}

int main()
{
	char num1[] = "7894418940";
	char num2[] = "99770";
	char output[19] = {0}; 
	int i = 0;
	Add(num1, num2, output);
	for( ; i < 16; ++i)
	{
		printf("%c", output[i]);
	}
	printf("\n");
	return 0;
}
