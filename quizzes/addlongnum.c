#include <stdio.h>



char *Add(char *num1, char *num2, char *output)
{
	int memo = 0;
	int one = 0;
	int two = 0;
	char temp;
	char sum;
	size_t i = 15;
	int len1 = 11;
	int len2 = 5;
	int len3 = 20;
	while(i)
	{	
		one = num1[len1 - 1] - 48;
		two = num2[len2 - 1] - 48;
	
		sum = one + two + memo;
		printf("sum: %d\n",sum);
		temp = sum % 10 + 48;
		printf("temp: %c\n",temp);
		output[len3 - 1] = temp;
		printf("mem: %d\n",memo);
		printf("___________________________________\n");
		--i;
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
	return output;	
}

int main()
{
	char num1[] = "12345678916";
	char num2[] = "70771";
	char output[20]; 
	int i = 0;
	Add(num1, num2, output);
	for( ; i < 20; ++i)
	{
		printf("%c", output[i]);
	}
	return 0;
}
